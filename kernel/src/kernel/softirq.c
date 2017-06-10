/*
 *	linux/kernel/softirq.c
 *
 *	Copyright (C) 1992 Linus Torvalds
 *
 * Fixed a disable_bh()/enable_bh() race (was causing a console lockup)
 * due bh_mask_count not atomic handling. Copyright (C) 1998  Andrea Arcangeli
 *
 * Rewritten. Old one was good in 2.2, but in 2.3 it was immoral. --ANK (990903)
 */

//-------------------------------------------------------------------------------------
// Copyright 2004, Texas Instruments Incorporated
//
// This program has been modified from its original operation by Texas Instruments
// to do the following:
// 
// Voice-Data coexistence scheduling fixes.
//
// THIS MODIFIED SOFTWARE AND DOCUMENTATION ARE PROVIDED
// "AS IS," AND TEXAS INSTRUMENTS MAKES NO REPRESENTATIONS 
// OR WARRENTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED 
// TO, WARRANTIES OF MERCHANTABILITY OR FITNESS FOR ANY 
// PARTICULAR PURPOSE OR THAT THE USE OF THE SOFTWARE OR 
// DOCUMENTATION WILL NOT INFRINGE ANY THIRD PARTY PATENTS, 
// COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS. 
// See The GNU General Public License for more details.
//
// These changes are covered under version 2 of the GNU General Public License, 
// dated June 1991.
//-------------------------------------------------------------------------------------

#include <linux/config.h>
#include <linux/mm.h>
#include <linux/kernel_stat.h>
#include <linux/interrupt.h>
#include <linux/smp_lock.h>
#include <linux/init.h>
#include <linux/tqueue.h>

#include <linux/trace.h>

/*
   - No shared variables, all the data are CPU local.
   - If a softirq needs serialization, let it serialize itself
     by its own spinlocks.
   - Even if softirq is serialized, only local cpu is marked for
     execution. Hence, we get something sort of weak cpu binding.
     Though it is still not clear, will it result in better locality
     or will not.
   - These softirqs are not masked by global cli() and start_bh_atomic()
     (by clear reasons). Hence, old parts of code still using global locks
     MUST NOT use softirqs, but insert interfacing routines acquiring
     global locks. F.e. look at BHs implementation.

   Examples:
   - NET RX softirq. It is multithreaded and does not require
     any global serialization.
   - NET TX softirq. It kicks software netdevice queues, hence
     it is logically serialized per device, but this serialization
     is invisible to common code.
   - Tasklets: serialized wrt itself.
   - Bottom halves: globally serialized, grr...
 */

irq_cpustat_t irq_stat[NR_CPUS];

static struct softirq_action softirq_vec[32] __cacheline_aligned;

#ifdef CONFIG_PREEMPT_TIMES
extern void latency_cause(int,int);
#else
#define latency_cause(a, b)
#endif

extern int gIsVoiceEnabled;

void trigger_softirq(void)
{
    if(softirq_pending(smp_processor_id())) 
	    do_softirq();
}
        
/*
 * we cannot loop indefinitely here to avoid userspace starvation,
 * but we also don't want to introduce a worst case 1/HZ latency
 * to the pending events, so lets the scheduler to balance
 * the softirq load for us.
 */
static inline void wakeup_softirqd(unsigned cpu)
{
	struct task_struct * tsk = ksoftirqd_task(cpu);

	if (tsk && tsk->state != TASK_RUNNING)
		wake_up_process(tsk);
}

/**************************************************************************
 * FUNCTION NAME : do_softirq_from_daemon
 **************************************************************************
 * DESCRIPTION   :
 *  The orignal LINUX 'do_softirq' code. This function was renamed because the
 *  function do_softirq was a generic API interface which gets called from 
 *  many places in the System to execute the bottom halves. With voice 
 *  enabled, we wanted to execute only the Timer BH in IRQ context and the 
 *  rest of the BH's in the context of ksoftirqd. This function is called
 *  only from the ksoftirqd OR if voice is disabled from IRQ context.
 ***************************************************************************/
asmlinkage void do_softirq_from_daemon()
{
	int cpu = smp_processor_id();
	__u32 pending;
	long flags;
	__u32 mask;

	if (in_interrupt())
		return;
	preempt_lock_start(-99);

	local_irq_save(flags);

	pending = softirq_pending(cpu);

	if (pending) {
		struct softirq_action *h;

		mask = ~pending;
		local_bh_disable();
restart:
		/* Reset the pending bitmask before enabling irqs */
		softirq_pending(cpu) = 0;

		local_irq_enable();

		h = softirq_vec;
 
		latency_cause(-100, pending);


		do {
			if (pending & 1) {
		                TRACE_SOFT_IRQ(TRACE_EV_SOFT_IRQ_SOFT_IRQ, (h - softirq_vec));
				h->action(h);
			}
			h++;
			pending >>= 1;
		} while (pending);

		local_irq_disable();

		pending = softirq_pending(cpu);

		if (pending & (mask | ALWAYS_SOFTIRQ)) {
			mask &= ~pending;
			goto restart;
		}
		__local_bh_enable();

		if (pending)
			wakeup_softirqd(cpu);
	}

	local_irq_restore(flags);
#ifdef CONFIG_ILATENCY
	/*
	 * If you have entry.S whacked up to call intr_ret_from_exception
	 * you can remove this call, unfortunately, MIPs and ARM don't
	 * have a simple way to do this for now so we catch them all here . . 
	 */
	intr_ret_from_exception();
#endif 
}

/**************************************************************************
 * FUNCTION NAME : do_softirq_for_voice
 **************************************************************************
 * DESCRIPTION   :
 *  Changing the function for voice-data coexistence. The problem
 *  with the function was that it would rerun all the bottom halves again 
 *  and again if one of the BH's or tasklets took longer than 10msec to 
 *  execute. This seems to happen with VOICE and Heavy DATA passing through. 
 *  The System will have the following BH's running - NET BH, CPMAC Rx 
 *  Tasklet, Voice Timer Tasklet, besides the generic Timer BH. This means 
 *  that if any of the above mentioned components takes a long time to 
 *  execute. The code is stuck in a LOOP executing at higest priority killing 
 *  everything else in the System. Right now my guess is that the Voice Timer 
 *  tasklet is running heavy. If I reran the 100Mbps test with only data I 
 *  can see the tasklet running in the ksoftirq context.
 ***************************************************************************/
asmlinkage void do_softirq_for_voice()
{
	int cpu = smp_processor_id();
	__u32 pending;
	long flags;
	__u32 mask;
    int     counter = 0;

	if (in_interrupt())
		return;
	preempt_lock_start(-99);

	local_irq_save(flags);

	pending = softirq_pending(cpu);

	if (pending & ALWAYS_SOFTIRQ)
    {
		struct softirq_action *h;

		mask = ~(pending & ALWAYS_SOFTIRQ);

		local_bh_disable();

restart:
        /* PANKAJ: TODO: Just a quick hack to clean the TIMER BH pending flag. */
        softirq_pending(cpu) = pending & mask;
        pending = pending & ALWAYS_SOFTIRQ;

		local_irq_enable();

		h = softirq_vec;
 
		latency_cause(-100, pending);

		do 
        {
			if (pending & 1) 
            {
		        TRACE_SOFT_IRQ(TRACE_EV_SOFT_IRQ_SOFT_IRQ, (h - softirq_vec));
				h->action(h);
			}
			h++;
			pending >>= 1;
		} while (pending);

		local_irq_disable();

		pending = softirq_pending(cpu);

        /* Debug Messages. */
        if (counter > 1)
            printk ("DEBUG: Restarting has already been done %d times..\n", counter);

        /* PANKAJ: Check if there are any more pending soft irqs that need to be executed. We have 
         * already executed one iteration of the soft IRQ loop. Anything still pending needs to be
         * handled in the context of ksoftirqd except TIMER BH which needs to be executed immediately. */
		if (pending & ALWAYS_SOFTIRQ)
        {
            /* PANKAJ: Debugging keeping track of the number of times we restart.... */
            counter++;
			goto restart;
		}
		__local_bh_enable();

		if (pending)
			wakeup_softirqd(cpu);
	}
    else
    {
		if (pending)
			wakeup_softirqd(cpu);
    }

	local_irq_restore(flags);
#ifdef CONFIG_ILATENCY
	/*
	 * If you have entry.S whacked up to call intr_ret_from_exception
	 * you can remove this call, unfortunately, MIPs and ARM don't
	 * have a simple way to do this for now so we catch them all here . . 
	 */
	intr_ret_from_exception();
#endif 
}

/**************************************************************************
 * FUNCTION NAME : do_softirq
 **************************************************************************
 * DESCRIPTION   :
 *  The generic well known API to execure BH's. This function gets called 
 *  and can behave in 2 ways depending on the state of the voice call
 *      a) Orignal Implementation if NO Voice call is ACTIVE
 *      b) Else Execute only Timer in BH context and the other BH's later 
 ***************************************************************************/
asmlinkage void do_softirq()
{
    if (gIsVoiceEnabled == 1)
        do_softirq_for_voice();
    else
        do_softirq_from_daemon();
}

/*
 * This function must run with irq disabled!
 */
inline void cpu_raise_softirq(unsigned int cpu, unsigned int nr)
{
	__cpu_raise_softirq(cpu, nr);

	/*
	 * If we're in an interrupt or bh, we're done
	 * (this also catches bh-disabled code). We will
	 * actually run the softirq once we return from
	 * the irq or bh.
	 *
	 * Otherwise we wake up ksoftirqd to make sure we
	 * schedule the softirq soon.
	 */
	if (!(local_irq_count(cpu) | local_bh_count(cpu)))
		wakeup_softirqd(cpu);
}

void raise_softirq(unsigned int nr)
{
	long flags;

	local_irq_save(flags);
	cpu_raise_softirq(smp_processor_id(), nr);
	local_irq_restore(flags);
}

void open_softirq(int nr, void (*action)(struct softirq_action*), void *data)
{
	softirq_vec[nr].data = data;
	softirq_vec[nr].action = action;
}


/* Tasklets */

struct tasklet_head tasklet_vec[NR_CPUS] __cacheline_aligned;
struct tasklet_head tasklet_hi_vec[NR_CPUS] __cacheline_aligned;

void __tasklet_schedule(struct tasklet_struct *t)
{
	int cpu = smp_processor_id();
	unsigned long flags;

	local_irq_save(flags);
	t->next = tasklet_vec[cpu].list;
	tasklet_vec[cpu].list = t;
	cpu_raise_softirq(cpu, TASKLET_SOFTIRQ);
	local_irq_restore(flags);
}

void __tasklet_hi_schedule(struct tasklet_struct *t)
{
	int cpu = smp_processor_id();
	unsigned long flags;

	local_irq_save(flags);
	t->next = tasklet_hi_vec[cpu].list;
	tasklet_hi_vec[cpu].list = t;
	cpu_raise_softirq(cpu, HI_SOFTIRQ);
	local_irq_restore(flags);
}

static void tasklet_action(struct softirq_action *a)
{
	int cpu = smp_processor_id();
	struct tasklet_struct *list;

	local_irq_disable();
	list = tasklet_vec[cpu].list;
	tasklet_vec[cpu].list = NULL;
	local_irq_enable();

	while (list) {
		struct tasklet_struct *t = list;

		list = list->next;

		if (tasklet_trylock(t)) {
			if (!atomic_read(&t->count)) {
				if (!test_and_clear_bit(TASKLET_STATE_SCHED, &t->state))
					BUG();

				TRACE_SOFT_IRQ(TRACE_EV_SOFT_IRQ_TASKLET_ACTION, (unsigned long) (t->func));

				t->func(t->data);
				tasklet_unlock(t);
				continue;
			}
			tasklet_unlock(t);
		}

		local_irq_disable();
		t->next = tasklet_vec[cpu].list;
		tasklet_vec[cpu].list = t;
		__cpu_raise_softirq(cpu, TASKLET_SOFTIRQ);
		local_irq_enable();
	}
}

static void tasklet_hi_action(struct softirq_action *a)
{
	int cpu = smp_processor_id();
	struct tasklet_struct *list;

	local_irq_disable();
	list = tasklet_hi_vec[cpu].list;
	tasklet_hi_vec[cpu].list = NULL;
	local_irq_enable();

	while (list) {
		struct tasklet_struct *t = list;

		list = list->next;

		if (tasklet_trylock(t)) {
			if (!atomic_read(&t->count)) {
				if (!test_and_clear_bit(TASKLET_STATE_SCHED, &t->state))
					BUG();

				TRACE_SOFT_IRQ(TRACE_EV_SOFT_IRQ_TASKLET_HI_ACTION, (unsigned long) (t->func));

				t->func(t->data);
				tasklet_unlock(t);
				continue;
			}
			tasklet_unlock(t);
		}

		local_irq_disable();
		t->next = tasklet_hi_vec[cpu].list;
		tasklet_hi_vec[cpu].list = t;
		__cpu_raise_softirq(cpu, HI_SOFTIRQ);
		local_irq_enable();
	}
}


void tasklet_init(struct tasklet_struct *t,
		  void (*func)(unsigned long), unsigned long data)
{
	t->next = NULL;
	t->state = 0;
	atomic_set(&t->count, 0);
	t->func = func;
	t->data = data;
}

void tasklet_kill(struct tasklet_struct *t)
{
	if (in_interrupt())
		printk("Attempt to kill tasklet from interrupt\n");

	while (test_and_set_bit(TASKLET_STATE_SCHED, &t->state)) {
		current->state = TASK_RUNNING;
		do {
			current->policy |= SCHED_YIELD;
			schedule();
		} while (test_bit(TASKLET_STATE_SCHED, &t->state));
	}
	tasklet_unlock_wait(t);
	clear_bit(TASKLET_STATE_SCHED, &t->state);
}



/* Old style BHs */

static void (*bh_base[32])(void);
struct tasklet_struct bh_task_vec[32];

/* BHs are serialized by spinlock global_bh_lock.

   It is still possible to make synchronize_bh() as
   spin_unlock_wait(&global_bh_lock). This operation is not used
   by kernel now, so that this lock is not made private only
   due to wait_on_irq().

   It can be removed only after auditing all the BHs.
 */
spinlock_t global_bh_lock = SPIN_LOCK_UNLOCKED;

static void bh_action(unsigned long nr)
{
	int cpu = smp_processor_id();

	if (!spin_trylock(&global_bh_lock))
		goto resched;

	if (!hardirq_trylock(cpu))
		goto resched_unlock;

	if (bh_base[nr]){
	        TRACE_SOFT_IRQ(TRACE_EV_SOFT_IRQ_BOTTOM_HALF, (nr));
		bh_base[nr]();
	}

	hardirq_endlock(cpu);
	spin_unlock(&global_bh_lock);
	return;

resched_unlock:
	spin_unlock(&global_bh_lock);
resched:
	mark_bh(nr);
}

void init_bh(int nr, void (*routine)(void))
{
	bh_base[nr] = routine;
	mb();
}

void remove_bh(int nr)
{
	tasklet_kill(bh_task_vec+nr);
	bh_base[nr] = NULL;
}

void __init softirq_init()
{
	int i;

	for (i=0; i<32; i++)
		tasklet_init(bh_task_vec+i, bh_action, i);

	open_softirq(TASKLET_SOFTIRQ, tasklet_action, NULL);
	open_softirq(HI_SOFTIRQ, tasklet_hi_action, NULL);
        open_softirq(RUN_TIMER_LIST,timer_softirq, NULL);
}

void __run_task_queue(task_queue *list)
{
	struct list_head head, *next;
	unsigned long flags;

	spin_lock_irqsave(&tqueue_lock, flags);
	list_add(&head, list);
	list_del_init(list);
	spin_unlock_irqrestore(&tqueue_lock, flags);

	next = head.next;
	while (next != &head) {
		void (*f) (void *);
		struct tq_struct *p;
		void *data;

		p = list_entry(next, struct tq_struct, list);
		next = next->next;
		f = p->routine;
		data = p->data;
		wmb();
		p->sync = 0;
		if (f)
			f(data);
	}
}

static int ksoftirqd(void * __bind_cpu)
{
	int bind_cpu = (int) (long) __bind_cpu;
	int cpu = cpu_logical_map(bind_cpu);

	daemonize();
	current->nice = 19;
	sigfillset(&current->blocked);

	/* Migrate to the right CPU */
	current->cpus_allowed = 1UL << cpu;
	while (smp_processor_id() != cpu)
		schedule();

	sprintf(current->comm, "ksoftirqd_CPU%d", bind_cpu);

	__set_current_state(TASK_INTERRUPTIBLE);
	mb();

	ksoftirqd_task(cpu) = current;

	for (;;) {
		if (!softirq_pending(cpu))
			schedule();

		__set_current_state(TASK_RUNNING);

		while (softirq_pending(cpu)) {
			do_softirq_from_daemon();
			if (current->need_resched)
				schedule();
		}

		__set_current_state(TASK_INTERRUPTIBLE);
	}
}

static __init int spawn_ksoftirqd(void)
{
	int cpu;

	for (cpu = 0; cpu < smp_num_cpus; cpu++) {
		if (kernel_thread(ksoftirqd, (void *) (long) cpu,
				  CLONE_FS | CLONE_FILES | CLONE_SIGNAL) < 0)
			printk("spawn_ksoftirqd() failed for cpu %d\n", cpu);
		else {
			while (!ksoftirqd_task(cpu_logical_map(cpu))) {
				current->policy |= SCHED_YIELD;
				schedule();
			}
		}
	}

	return 0;
}

__initcall(spawn_ksoftirqd);
