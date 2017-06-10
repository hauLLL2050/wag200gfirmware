/* iptables match extension to limit the number of packets per second
 * seperately for each destination.
 *
 * (C) 2003 by Harald Welte <laforge@netfilter.org>
 *
 * ipt_dstlimit.c,v 1.3 2004/02/23 00:15:44 laforge Exp
 *
 * Development of this code was funded by Astaro AG, http://www.astaro.com/
 *
 * based on ipt_limit.c by:
 * J�r�me de Vivie	<devivie@info.enserb.u-bordeaux.fr>
 * Herv� Eychenne	<eychenne@info.enserb.u-bordeaux.fr>
 * Rusty Russell	<rusty@rustcorp.com.au>
 *
 * The general idea is to create a hash table for every dstip and have a
 * seperate limit counter per tuple.  This way you can do something like 'limit
 * the number of syn packets for each of my internal addresses.
 *
 * Ideally this would just be implemented as a general 'hash' match, which would
 * allow us to attach any iptables target to it's hash buckets.  But this is
 * not possible in the current iptables architecture.  As always, pkttables for
 * 2.7.x will help ;)
 */
#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/spinlock.h>
#include <linux/random.h>
#include <linux/jhash.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#define ASSERT_READ_LOCK(x) 
#define ASSERT_WRITE_LOCK(x) 
#include <linux/netfilter_ipv4/lockhelp.h>
#include <linux/netfilter_ipv4/listhelp.h>

#include <linux/netfilter_ipv4/ip_tables.h>
#include <linux/netfilter_ipv4/ipt_dstlimit.h>

/* FIXME: this is just for IP_NF_ASSERRT */
#include <linux/netfilter_ipv4/ip_conntrack.h>

#define MS2JIFFIES(x) ((x*HZ)/1000)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Harald Welte <laforge@netfilter.org>");
MODULE_DESCRIPTION("iptables match for limiting per destination");

/* need to declare this at the top */
static struct proc_dir_entry *dstlimit_procdir;
static struct file_operations dl_file_ops;

/* hash table crap */

struct dsthash_dst {
	u_int32_t src_ip;
	u_int32_t dst_ip;
	u_int16_t port;
};

struct dsthash_ent {
	/* static / read-only parts in the beginning */
	struct list_head list;
	struct dsthash_dst dst;

	/* modified structure members in the end */
	unsigned long expires;		/* precalculated expiry time */
	struct {
		unsigned long prev;	/* last modification */
		u_int32_t credit;
		u_int32_t credit_cap, cost;
	} rateinfo;
};

struct ipt_dstlimit_htable {
	struct list_head list;		/* global list of all htables */
	atomic_t use;

	struct dstlimit_cfg cfg;	/* config */

	/* used internally */
	spinlock_t lock;		/* lock for list_head */
	u_int32_t rnd;			/* random seed for hash */
	struct timer_list timer;	/* timer for gc */
	atomic_t count;			/* number entries in table */

	/* seq_file stuff */
	struct proc_dir_entry *pde;

	struct list_head hash[0];	/* hashtable itself */
};

DECLARE_RWLOCK(dstlimit_lock);		/* protects htables list */
static LIST_HEAD(dstlimit_htables);
static kmem_cache_t *dstlimit_cachep;

static inline int dst_cmp(const struct dsthash_ent *ent, struct dsthash_dst *b)
{
	return (ent->dst.dst_ip == b->dst_ip 
		&& ent->dst.port == b->port
		&& ent->dst.src_ip == b->src_ip);
}

static inline u_int32_t
hash_dst(const struct ipt_dstlimit_htable *ht, const struct dsthash_dst *dst)
{
	return (jhash_3words(dst->dst_ip, dst->port, 
			     dst->src_ip, ht->rnd) % ht->cfg.size);
}

static inline struct dsthash_ent *
__dsthash_find(const struct ipt_dstlimit_htable *ht, struct dsthash_dst *dst)
{
	struct dsthash_ent *ent;
	u_int32_t hash = hash_dst(ht, dst);
	MUST_BE_LOCKED(&ht->lock);
	ent = LIST_FIND(&ht->hash[hash], dst_cmp, struct dsthash_ent *, dst);
	return ent;
}

/* allocate dsthash_ent, initialize dst, put in htable and lock it */
static struct dsthash_ent *
__dsthash_alloc_init(struct ipt_dstlimit_htable *ht, struct dsthash_dst *dst)
{
	struct dsthash_ent *ent;

	/* initialize hash with random val at the time we allocate
	 * the first hashtable entry */
	if (!ht->rnd)
		get_random_bytes(&ht->rnd, 4);

	if (ht->cfg.max &&
	    atomic_read(&ht->count) >= ht->cfg.max) {
		/* FIXME: do something. question is what.. */
		if (net_ratelimit())
			printk(KERN_WARNING 
				"ipt_dstlimit: max count of %u reached\n", 
				ht->cfg.max);
		return NULL;
	}

	ent = kmem_cache_alloc(dstlimit_cachep, GFP_ATOMIC);
	if (!ent) {
		if (net_ratelimit())
			printk(KERN_ERR 
				"ipt_dstlimit: can't allocate dsthash_ent\n");
		return NULL;
	}

	atomic_inc(&ht->count);

	ent->dst.dst_ip = dst->dst_ip;
	ent->dst.port = dst->port;
	ent->dst.src_ip = dst->src_ip;

	list_add(&ent->list, &ht->hash[hash_dst(ht, dst)]);

	return ent;
}

static inline void 
__dsthash_free(struct ipt_dstlimit_htable *ht, struct dsthash_ent *ent)
{
	MUST_BE_LOCKED(&ht->lock);

	list_del(&ent->list);
	kmem_cache_free(dstlimit_cachep, ent);
	atomic_dec(&ht->count);
}
static void htable_gc(unsigned long htlong);

static int htable_create(struct ipt_dstlimit_info *minfo)
{
	int i;
	unsigned int size;
	struct ipt_dstlimit_htable *hinfo;

	if (minfo->cfg.size)
		size = minfo->cfg.size;
	else {
		size = (((num_physpages << PAGE_SHIFT) / 16384)
			 / sizeof(struct list_head));
		if (num_physpages > (1024 * 1024 * 1024 / PAGE_SIZE))
			size = 8192;
		if (size < 16)
			size = 16;
	}
	/* FIXME: don't use vmalloc() here or anywhere else -HW */
	hinfo = vmalloc(sizeof(struct ipt_dstlimit_htable)
			+ (sizeof(struct list_head) * size));
	if (!hinfo) {
		printk(KERN_ERR "ipt_dstlimit: Unable to create hashtable\n");
		return -1;
	}
	minfo->hinfo = hinfo;

	/* copy match config into hashtable config */
	memcpy(&hinfo->cfg, &minfo->cfg, sizeof(hinfo->cfg));
	hinfo->cfg.size = size;
	if (!hinfo->cfg.max)
		hinfo->cfg.max = 8 * hinfo->cfg.size;
	else if (hinfo->cfg.max < hinfo->cfg.size)
		hinfo->cfg.max = hinfo->cfg.size;

	for (i = 0; i < hinfo->cfg.size; i++)
		INIT_LIST_HEAD(&hinfo->hash[i]);

	atomic_set(&hinfo->count, 0);
	atomic_set(&hinfo->use, 1);
	hinfo->rnd = 0;
	hinfo->lock = SPIN_LOCK_UNLOCKED;
	hinfo->pde = create_proc_entry(minfo->name, 0, dstlimit_procdir);
	if (!hinfo->pde) {
		vfree(hinfo);
		return -1;
	}
	hinfo->pde->proc_fops = &dl_file_ops;
	hinfo->pde->data = hinfo;

	init_timer(&hinfo->timer);
	hinfo->timer.expires = jiffies + MS2JIFFIES(hinfo->cfg.gc_interval);
	hinfo->timer.data = (unsigned long )hinfo;
	hinfo->timer.function = htable_gc;
	add_timer(&hinfo->timer);

	WRITE_LOCK(&dstlimit_lock);
	list_add(&hinfo->list, &dstlimit_htables);
	WRITE_UNLOCK(&dstlimit_lock);

	return 0;
}

static int select_all(struct ipt_dstlimit_htable *ht, struct dsthash_ent *he)
{
	return 1;
}

static int select_gc(struct ipt_dstlimit_htable *ht, struct dsthash_ent *he)
{
	return (jiffies >= he->expires);
}

static void htable_selective_cleanup(struct ipt_dstlimit_htable *ht,
		 		int (*select)(struct ipt_dstlimit_htable *ht, 
					      struct dsthash_ent *he))
{
	int i;

	IP_NF_ASSERT(ht->cfg.size && ht->cfg.max);

	/* lock hash table and iterate over it */
	LOCK_BH(&ht->lock);
	for (i = 0; i < ht->cfg.size; i++) {
		struct dsthash_ent *dh, *n;
		list_for_each_entry_safe(dh, n, &ht->hash[i], list) {
			if ((*select)(ht, dh))
				__dsthash_free(ht, dh);
		}
	}
	UNLOCK_BH(&ht->lock);
}

/* hash table garbage collector, run by timer */
static void htable_gc(unsigned long htlong)
{
	struct ipt_dstlimit_htable *ht = (struct ipt_dstlimit_htable *)htlong;

	htable_selective_cleanup(ht, select_gc);

	/* re-add the timer accordingly */
	ht->timer.expires = jiffies + MS2JIFFIES(ht->cfg.gc_interval);
	add_timer(&ht->timer);
}

static void htable_destroy(struct ipt_dstlimit_htable *hinfo)
{
	/* remove timer, if it is pending */
	if (timer_pending(&hinfo->timer))
		del_timer(&hinfo->timer);

	/* remove proc entry */
	remove_proc_entry(hinfo->pde->name, dstlimit_procdir);

	htable_selective_cleanup(hinfo, select_all);
	vfree(hinfo);
}

static struct ipt_dstlimit_htable *htable_find_get(char *name)
{
	struct ipt_dstlimit_htable *hinfo;

	READ_LOCK(&dstlimit_lock);
	list_for_each_entry(hinfo, &dstlimit_htables, list) {
		if (!strcmp(name, hinfo->pde->name)) {
			atomic_inc(&hinfo->use);
			READ_UNLOCK(&dstlimit_lock);
			return hinfo;
		}
	}
	READ_UNLOCK(&dstlimit_lock);

	return NULL;
}

static void htable_put(struct ipt_dstlimit_htable *hinfo)
{
	if (atomic_dec_and_test(&hinfo->use)) {
		WRITE_LOCK(&dstlimit_lock);
		list_del(&hinfo->list);
		WRITE_UNLOCK(&dstlimit_lock);
		htable_destroy(hinfo);
	}
}


/* The algorithm used is the Simple Token Bucket Filter (TBF)
 * see net/sched/sch_tbf.c in the linux source tree
 */

/* Rusty: This is my (non-mathematically-inclined) understanding of
   this algorithm.  The `average rate' in jiffies becomes your initial
   amount of credit `credit' and the most credit you can ever have
   `credit_cap'.  The `peak rate' becomes the cost of passing the
   test, `cost'.

   `prev' tracks the last packet hit: you gain one credit per jiffy.
   If you get credit balance more than this, the extra credit is
   discarded.  Every time the match passes, you lose `cost' credits;
   if you don't have that many, the test fails.

   See Alexey's formal explanation in net/sched/sch_tbf.c.

   To get the maximum range, we multiply by this factor (ie. you get N
   credits per jiffy).  We want to allow a rate as low as 1 per day
   (slowest userspace tool allows), which means
   CREDITS_PER_JIFFY*HZ*60*60*24 < 2^32 ie.
*/
#define MAX_CPJ (0xFFFFFFFF / (HZ*60*60*24))

/* Repeated shift and or gives us all 1s, final shift and add 1 gives
 * us the power of 2 below the theoretical max, so GCC simply does a
 * shift. */
#define _POW2_BELOW2(x) ((x)|((x)>>1))
#define _POW2_BELOW4(x) (_POW2_BELOW2(x)|_POW2_BELOW2((x)>>2))
#define _POW2_BELOW8(x) (_POW2_BELOW4(x)|_POW2_BELOW4((x)>>4))
#define _POW2_BELOW16(x) (_POW2_BELOW8(x)|_POW2_BELOW8((x)>>8))
#define _POW2_BELOW32(x) (_POW2_BELOW16(x)|_POW2_BELOW16((x)>>16))
#define POW2_BELOW32(x) ((_POW2_BELOW32(x)>>1) + 1)

#define CREDITS_PER_JIFFY POW2_BELOW32(MAX_CPJ)

/* Precision saver. */
static inline u_int32_t
user2credits(u_int32_t user)
{
	/* If multiplying would overflow... */
	if (user > 0xFFFFFFFF / (HZ*CREDITS_PER_JIFFY))
		/* Divide first. */
		return (user / IPT_DSTLIMIT_SCALE) * HZ * CREDITS_PER_JIFFY;

	return (user * HZ * CREDITS_PER_JIFFY) / IPT_DSTLIMIT_SCALE;
}

static inline void rateinfo_recalc(struct dsthash_ent *dh, unsigned long now)
{
	dh->rateinfo.credit += (now - xchg(&dh->rateinfo.prev, now)) 
					* CREDITS_PER_JIFFY;
	if (dh->rateinfo.credit > dh->rateinfo.credit_cap)
		dh->rateinfo.credit = dh->rateinfo.credit_cap;
}

static int
dstlimit_match(const struct sk_buff *skb,
		const struct net_device *in,
		const struct net_device *out,
		const void *matchinfo,
		int offset,
		const void *hdr,
		u_int16_t datalen,
		int *hotdrop)
{
	struct ipt_dstlimit_info *r = 
		((struct ipt_dstlimit_info *)matchinfo)->u.master;
	struct ipt_dstlimit_htable *hinfo = r->hinfo;
	unsigned long now = jiffies;
	struct dsthash_ent *dh;
	struct dsthash_dst dst;

	memset(&dst, 0, sizeof(dst));

	/* dest ip is always in hash */
	dst.dst_ip = skb->nh.iph->daddr;

	/* source ip only if respective hashmode, otherwise set to
	 * zero */
	if (hinfo->cfg.mode & IPT_DSTLIMIT_HASH_SIP)
		dst.src_ip = skb->nh.iph->saddr;

	/* dest port only if respective mode */
	if (hinfo->cfg.mode & IPT_DSTLIMIT_HASH_DPT) {
		switch (skb->nh.iph->protocol) {
			struct tcphdr *th;
			struct udphdr *uh;
		case IPPROTO_TCP:
			th = (void *)skb->nh.iph+skb->nh.iph->ihl*4;
			dst.port = th->dest;
			break;
		case IPPROTO_UDP:
			uh = (void *)skb->nh.iph+skb->nh.iph->ihl*4;
			dst.port = uh->dest;
			break;
		default:
			break;
		}
	} 

	LOCK_BH(&hinfo->lock);
	dh = __dsthash_find(hinfo, &dst);
	if (!dh) {
		dh = __dsthash_alloc_init(hinfo, &dst);

		if (!dh) {
			/* enomem... don't match == DROP */
			if (net_ratelimit())
				printk(KERN_ERR "%s: ENOMEM\n", __FUNCTION__);
			UNLOCK_BH(&hinfo->lock);
			return 0;
		}

		dh->expires = jiffies + MS2JIFFIES(hinfo->cfg.expire);

		dh->rateinfo.prev = jiffies;
		dh->rateinfo.credit = user2credits(hinfo->cfg.avg * 
							hinfo->cfg.burst);
		dh->rateinfo.credit_cap = user2credits(hinfo->cfg.avg * 
							hinfo->cfg.burst);
		dh->rateinfo.cost = user2credits(hinfo->cfg.avg);

		UNLOCK_BH(&hinfo->lock);
		return 1;
	}

	/* update expiration timeout */
	dh->expires = now + MS2JIFFIES(hinfo->cfg.expire);

	rateinfo_recalc(dh, now);
	if (dh->rateinfo.credit >= dh->rateinfo.cost) {
		/* We're underlimit. */
		dh->rateinfo.credit -= dh->rateinfo.cost;
		UNLOCK_BH(&hinfo->lock);
		return 1;
	}

       	UNLOCK_BH(&hinfo->lock);

	/* default case: we're overlimit, thus don't match */
	return 0;
}

static int
dstlimit_checkentry(const char *tablename,
		     const struct ipt_ip *ip,
		     void *matchinfo,
		     unsigned int matchsize,
		     unsigned int hook_mask)
{
	struct ipt_dstlimit_info *r = matchinfo;

	if (matchsize != IPT_ALIGN(sizeof(struct ipt_dstlimit_info)))
		return 0;

	/* Check for overflow. */
	if (r->cfg.burst == 0
	    || user2credits(r->cfg.avg * r->cfg.burst) < 
	    				user2credits(r->cfg.avg)) {
		printk(KERN_ERR "ipt_dstlimit: Overflow, try lower: %u/%u\n",
		       r->cfg.avg, r->cfg.burst);
		return 0;
	}

	if (r->cfg.mode == 0 
	    || r->cfg.mode > (IPT_DSTLIMIT_HASH_DPT
		          |IPT_DSTLIMIT_HASH_DIP
			  |IPT_DSTLIMIT_HASH_SIP))
		return 0;

	if (!r->cfg.gc_interval)
		return 0;
	
	if (!r->cfg.expire)
		return 0;

	r->hinfo = htable_find_get(r->name);
	if (!r->hinfo && (htable_create(r) != 0)) {
		return 0;
	}

	/* Ugly hack: For SMP, we only want to use one set */
	r->u.master = r;

	return 1;
}

static void
dstlimit_destroy(void *matchinfo, unsigned int matchsize)
{
	struct ipt_dstlimit_info *r = (struct ipt_dstlimit_info *) matchinfo;

	htable_put(r->hinfo);
}

static struct ipt_match ipt_dstlimit = { 
	.list = { .prev = NULL, .next = NULL }, 
	.name = "dstlimit", 
	.match = dstlimit_match, 
	.checkentry = dstlimit_checkentry, 
	.destroy = dstlimit_destroy,
	.me = THIS_MODULE 
};

/* PROC stuff */

static void *dl_seq_start(struct seq_file *s, loff_t *pos)
{
	struct proc_dir_entry *pde = s->private;
	struct ipt_dstlimit_htable *htable = pde->data;
	unsigned int *bucket;

	LOCK_BH(&htable->lock);
	if (*pos >= htable->cfg.size)
		return NULL;

	bucket = kmalloc(sizeof(unsigned int), GFP_KERNEL);
	if (!bucket)
		return ERR_PTR(-ENOMEM);

	*bucket = *pos;
	return bucket;
}

static void *dl_seq_next(struct seq_file *s, void *v, loff_t *pos)
{
	struct proc_dir_entry *pde = s->private;
	struct ipt_dstlimit_htable *htable = pde->data;
	unsigned int *bucket = (unsigned int *)v;

	*pos = ++(*bucket);
	if (*pos >= htable->cfg.size) {
		kfree(v);
		return NULL;
	}
	return bucket;
}

static void dl_seq_stop(struct seq_file *s, void *v)
{
	struct proc_dir_entry *pde = s->private;
	struct ipt_dstlimit_htable *htable = pde->data;
	unsigned int *bucket = (unsigned int *)v;

	kfree(bucket);

	UNLOCK_BH(&htable->lock);
}

static inline int dl_seq_real_show(struct dsthash_ent *ent, struct seq_file *s)
{
	/* recalculate to show accurate numbers */
	rateinfo_recalc(ent, jiffies);

	return seq_printf(s, "%ld %u.%u.%u.%u->%u.%u.%u.%u:%u %u %u %u\n",
			(ent->expires - jiffies)/HZ,
			NIPQUAD(ent->dst.src_ip),
			NIPQUAD(ent->dst.dst_ip), ntohs(ent->dst.port),
			ent->rateinfo.credit, ent->rateinfo.credit_cap,
			ent->rateinfo.cost);
}

static int dl_seq_show(struct seq_file *s, void *v)
{
	struct proc_dir_entry *pde = s->private;
	struct ipt_dstlimit_htable *htable = pde->data;
	unsigned int *bucket = (unsigned int *)v;

	if (LIST_FIND_W(&htable->hash[*bucket], dl_seq_real_show,
		      struct dsthash_ent *, s)) {
		/* buffer was filled and unable to print that tuple */
		return 1;
	}
	return 0;
}

static struct seq_operations dl_seq_ops = {
	.start = dl_seq_start,
	.next  = dl_seq_next,
	.stop  = dl_seq_stop,
	.show  = dl_seq_show
};

//#if LINUX_VERSION_CODE < 0x020500
//static inline struct proc_dir_entry *PDE(const struct inode *inode)
//{
//        return inode->u.generic_ip;
//}
//#endif


static int dl_proc_open(struct inode *inode, struct file *file)
{
	int ret = seq_open(file, &dl_seq_ops);

	if (!ret) {
		struct seq_file *sf = file->private_data;
		sf->private = PDE(inode);
	}
	return ret;
}

static struct file_operations dl_file_ops = {
	.owner   = THIS_MODULE,
	.open    = dl_proc_open,
	.read    = seq_read,
	.llseek  = seq_lseek,
	.release = seq_release
};

static int init_or_fini(int fini)
{
	int ret = 0;

	if (fini)
		goto cleanup;

	if (ipt_register_match(&ipt_dstlimit)) {
		ret = -EINVAL;
		goto cleanup_nothing;
	}

	/* FIXME: do we really want HWCACHE_ALIGN since our objects are
	 * quite small ? */
	dstlimit_cachep = kmem_cache_create("ipt_dstlimit",
					    sizeof(struct dsthash_ent), 0,
					    SLAB_HWCACHE_ALIGN, NULL, NULL);
	if (!dstlimit_cachep) {
		printk(KERN_ERR "Unable to create ipt_dstlimit slab cache\n");
		ret = -ENOMEM;
		goto cleanup_unreg_match;
	}

	dstlimit_procdir = proc_mkdir("ipt_dstlimit", proc_net);
	if (!dstlimit_procdir) {
		printk(KERN_ERR "Unable to create proc dir entry\n");
		ret = -ENOMEM;
		goto cleanup_free_slab;
	}

	return ret;

cleanup:
	remove_proc_entry("ipt_dstlimit", proc_net);
cleanup_free_slab:
	kmem_cache_destroy(dstlimit_cachep);
cleanup_unreg_match:
	ipt_unregister_match(&ipt_dstlimit);
cleanup_nothing:
	return ret;
	
}

static int __init init(void)
{
	return init_or_fini(0);
}

static void __exit fini(void)
{
	init_or_fini(1);
}

module_init(init);
module_exit(fini);
