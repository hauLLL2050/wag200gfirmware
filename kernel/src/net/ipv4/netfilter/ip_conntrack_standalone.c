/* This file contains all the functions required for the standalone
   ip_conntrack module.

   These are not required by the compatibility layer.
*/

/* (c) 1999 Paul `Rusty' Russell.  Licenced under the GNU General
   Public Licence. */

#include <linux/types.h>
#include <linux/ip.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/proc_fs.h>
#include <linux/version.h>
#include <linux/brlock.h>
#include <net/checksum.h>

#define ASSERT_READ_LOCK(x) MUST_BE_READ_LOCKED(&ip_conntrack_lock)
#define ASSERT_WRITE_LOCK(x) MUST_BE_WRITE_LOCKED(&ip_conntrack_lock)

#include <linux/netfilter_ipv4/ip_conntrack.h>
#include <linux/netfilter_ipv4/ip_conntrack_protocol.h>
#include <linux/netfilter_ipv4/ip_conntrack_core.h>
#include <linux/netfilter_ipv4/ip_conntrack_helper.h>
#include <linux/netfilter_ipv4/listhelp.h>

#if 0
#define DEBUGP printk
#else
#define DEBUGP(format, args...)
#endif

#ifndef CONFIG_SERCOMM_CODE
#define CONFIG_SERCOMM_CODE 1
#endif

struct module *ip_conntrack_module = THIS_MODULE;
MODULE_LICENSE("GPL");

static int kill_proto(const struct ip_conntrack *i, void *data)
{
	return (i->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.protonum == 
			*((u_int8_t *) data));
}

static unsigned int
print_tuple(char *buffer, const struct ip_conntrack_tuple *tuple,
	    struct ip_conntrack_protocol *proto)
{
	int len;

	len = sprintf(buffer, "src=%u.%u.%u.%u dst=%u.%u.%u.%u ",
		      NIPQUAD(tuple->src.ip), NIPQUAD(tuple->dst.ip));

	len += proto->print_tuple(buffer + len, tuple);

	return len;
}

/* FIXME: Don't print source proto part. --RR */
static unsigned int
print_expect(char *buffer, const struct ip_conntrack_expect *expect)
{
	unsigned int len;

	len = sprintf(buffer, "EXPECTING: proto=%u ",
		      expect->tuple.dst.protonum);
	len += print_tuple(buffer + len, &expect->tuple,
			   __find_proto(expect->tuple.dst.protonum));
	len += sprintf(buffer + len, "\n");
	return len;
}

static unsigned int
print_conntrack(char *buffer, struct ip_conntrack *conntrack)
{
	unsigned int len;
	struct ip_conntrack_protocol *proto
		= __find_proto(conntrack->tuplehash[IP_CT_DIR_ORIGINAL]
			       .tuple.dst.protonum);

	len = sprintf(buffer, "%-8s %u %lu ",
		      proto->name,
		      conntrack->tuplehash[IP_CT_DIR_ORIGINAL]
		      .tuple.dst.protonum,
		      timer_pending(&conntrack->timeout)
		      ? (conntrack->timeout.expires - jiffies)/HZ : 0);

	len += proto->print_conntrack(buffer + len, conntrack);
	len += print_tuple(buffer + len,
			   &conntrack->tuplehash[IP_CT_DIR_ORIGINAL].tuple,
			   proto);
	if (!(test_bit(IPS_SEEN_REPLY_BIT, &conntrack->status)))
		len += sprintf(buffer + len, "[UNREPLIED] ");
	len += print_tuple(buffer + len,
			   &conntrack->tuplehash[IP_CT_DIR_REPLY].tuple,
			   proto);
	if (test_bit(IPS_ASSURED_BIT, &conntrack->status))
		len += sprintf(buffer + len, "[ASSURED] ");
	len += sprintf(buffer + len, "use=%u ",
		       atomic_read(&conntrack->ct_general.use));

	#if defined(CONFIG_IP_NF_MATCH_LAYER7) || defined(CONFIG_IP_NF_MATCH_LAYER7_MODULE)
	if(conntrack->layer7.app_proto)
		len += sprintf(buffer + len, "l7proto=%s ",
				conntrack->layer7.app_proto); 
	#endif

	len += sprintf(buffer + len, "\n");

	return len;
}
#if defined(CONFIG_SERCOMM_CODE)
static unsigned int print_conntrack_my(char *buffer, 
	const struct ip_conntrack *conntrack , int mode)
{
	unsigned int len;
	struct ip_conntrack_protocol *proto
		= __find_proto(conntrack->tuplehash[IP_CT_DIR_ORIGINAL]
			       .tuple.dst.protonum);

	const struct ip_conntrack_tuple *tuple_ORIGINAL;
	const struct ip_conntrack_tuple *tuple_REPLY;
	u_int16_t protonum = conntrack->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.protonum;	
	u_int16_t sport =0;	
	u_int16_t dport =0;	
	u_int16_t sport2 =0;	
	u_int16_t dport2 =0;	


	// host ip
	tuple_ORIGINAL = &conntrack->tuplehash[IP_CT_DIR_ORIGINAL].tuple;
	tuple_REPLY = &conntrack->tuplehash[IP_CT_DIR_REPLY].tuple;

	len =0;
	
	
	// protocol name (tcp, udp, ...)
	switch ( protonum )
	{
		case IPPROTO_TCP:
			len += sprintf(buffer +len, "TCP  ");
			sport = ntohs(tuple_ORIGINAL->src.u.tcp.port);
			dport = ntohs(tuple_ORIGINAL->dst.u.tcp.port);
			break;
		case IPPROTO_UDP:			
			len += sprintf(buffer +len , "UDP  ");
			sport = ntohs(tuple_ORIGINAL->src.u.udp.port);
			dport = ntohs(tuple_ORIGINAL->dst.u.udp.port);

			break;
		case IPPROTO_IGMP:			
			len += sprintf(buffer +len , "IGMP ");
			break;
			
		default:
			len += sprintf(buffer +len, "protocol=%d  ", protonum );
			break;
	}

	// timeout
	len += sprintf(buffer +len, "T=%lu  ", 
		timer_pending(&conntrack->timeout)? (conntrack->timeout.expires - jiffies)/HZ : 0 );

	
	// ip
	len += sprintf(buffer+len, "%u.%u.%u.%u: %hu  => %u.%u.%u.%u: %hu  ",
		      NIPQUAD(tuple_ORIGINAL->src.ip), sport,
		      NIPQUAD(tuple_ORIGINAL->dst.ip), dport);



	// ct state
	if ((conntrack->status & IPS_EXPECTED_BIT))
		len += sprintf(buffer + len, "[E] ");

	if (!(conntrack->status & IPS_SEEN_REPLY))
		len += sprintf(buffer + len, "[U] ");

	if (conntrack->status & IPS_ASSURED)
		len += sprintf(buffer + len, "[A] ");

	if (conntrack->reserve.mask == IPS_RESERVE)
		len += sprintf(buffer + len, "[R] ");

	len += sprintf(buffer + len, "\n");


	if( protonum != IPPROTO_TCP && protonum != IPPROTO_UDP)
	{
		len += sprintf(buffer + len, "\n");
		return len;
	}

	len += sprintf(buffer + len, "    REPLY: ");

	// ip
	//len += print_tuple(buffer + len, tuple_REPLY, proto);
	switch ( protonum )
	{
		case IPPROTO_TCP:
			sport2 = ntohs(tuple_REPLY->src.u.tcp.port);
			dport2 = ntohs(tuple_REPLY->dst.u.tcp.port);
			break;
		case IPPROTO_UDP:			
			sport2 = ntohs(tuple_REPLY->src.u.udp.port);
			dport2 = ntohs(tuple_REPLY->dst.u.udp.port);
			break;
			
		default:
			break;
	}

	if( 	tuple_ORIGINAL->src.ip != tuple_REPLY->dst.ip ||
		tuple_ORIGINAL->dst.ip != tuple_REPLY->src.ip ||
		sport != dport2 ||
		dport != sport2)
	{
		len += sprintf(buffer+len, "%u.%u.%u.%u: %hu  => %u.%u.%u.%u: %hu  ",
		      NIPQUAD(tuple_REPLY->src.ip), sport2,
		      NIPQUAD(tuple_REPLY->dst.ip), dport2);

	}


/*
	len += sprintf(buffer+len , "s=%u.%u.%u.%u  d=%u.%u.%u.%u  ",
		      NIPQUAD(tuple_ORIGINAL->src.ip), 
		      NIPQUAD(tuple_ORIGINAL->dst.ip) );
*/


/*
	// CMAX
	len += sprintf(buffer + len, "G=%d ", conntrack->CMAX.mask_grp);
*/
/*
	// ipp2p
	len += sprintf(buffer + len, "P=%d ", conntrack->ipp2p.mask);
*/

	// use
	len += sprintf(buffer + len, "U=%u ",
		       atomic_read(&conntrack->ct_general.use));


/*
	if( tuple_ORIGINAL->dst.ip != tuple_REPLY->src.ip )
		len += sprintf(buffer+len , "rs=%u.%u.%u.%u  ", NIPQUAD(tuple_REPLY->src.ip) );

	if( tuple_ORIGINAL->src.ip != tuple_REPLY->dst.ip )
		len += sprintf(buffer+len , "rd=%u.%u.%u.%u  ", NIPQUAD(tuple_REPLY->dst.ip) );
*/
	// TCP state
	len += proto->print_conntrack(buffer + len, conntrack);


	len += sprintf(buffer + len, "\n\n");

	return len;
}

#endif

/* Returns true when finished. */
static inline int
conntrack_iterate(const struct ip_conntrack_tuple_hash *hash,
		  char *buffer, off_t offset, off_t *upto,
		  unsigned int *len, unsigned int maxlen)
{
	unsigned int newlen;
	IP_NF_ASSERT(hash->ctrack);

	MUST_BE_READ_LOCKED(&ip_conntrack_lock);

	/* Only count originals */
	if (DIRECTION(hash))
		return 0;

	if ((*upto)++ < offset)
		return 0;

	newlen = print_conntrack(buffer + *len, hash->ctrack);
	if (*len + newlen > maxlen)
		return 1;
	else *len += newlen;

	return 0;
}
#if defined(CONFIG_SERCOMM_CODE)
/* Returns true when finished. */
static inline int conntrack_iterate2(const struct ip_conntrack_tuple_hash *hash,
		  char *buffer, off_t offset, off_t *upto,
		  unsigned int *len, unsigned int maxlen , int mode)
{
	unsigned int newlen =0;
	IP_NF_ASSERT(hash->ctrack);

	MUST_BE_READ_LOCKED(&ip_conntrack_lock);

	/* Only count originals */
	if (DIRECTION(hash))
		return 0;

	if ((*upto)++ < offset)
		return 0;

	switch ( mode)
	{
/*
		case 2: // print non p2p ct only
			if (  hash->ctrack->ipp2p.mask == 0)	
				newlen = print_conntrack_my(buffer + *len, hash->ctrack , mode);
			break;
*/			
		default:
			newlen = print_conntrack_my(buffer + *len, hash->ctrack , mode);
	}
	
	if (*len + newlen > maxlen)
		return 1;
	else *len += newlen;

	return 0;
}
#endif

static int
list_conntracks(char *buffer, char **start, off_t offset, int length)
{
	unsigned int i;
	unsigned int len = 0;
	off_t upto = 0;
	struct list_head *e;

	READ_LOCK(&ip_conntrack_lock);
	/* Traverse hash; print originals then reply. */
	for (i = 0; i < ip_conntrack_htable_size; i++) {
		if (LIST_FIND(&ip_conntrack_hash[i], conntrack_iterate,
			      struct ip_conntrack_tuple_hash *,
			      buffer, offset, &upto, &len, length))
			goto finished;
	}

	/* Now iterate through expecteds. */
	for (e = expect_list.next; e != &expect_list; e = e->next) {
		unsigned int last_len;
		struct ip_conntrack_expect *expect
			= (struct ip_conntrack_expect *)e;
		if (upto++ < offset) continue;

		last_len = len;
		len += print_expect(buffer + len, expect);
		if (len > length) {
			len = last_len;
			goto finished;
		}
	}

 finished:
	READ_UNLOCK(&ip_conntrack_lock);

	/* `start' hack - see fs/proc/generic.c line ~165 */
	*start = (char *)((unsigned int)upto - offset);
	return len;
}
#if defined(CONFIG_SERCOMM_CODE)
static int
list_conntracks_1(char *buffer, char **start, off_t offset, int length)
{
	unsigned int i;
	unsigned int len = 0;
	off_t upto = 0;

	READ_LOCK(&ip_conntrack_lock);
	/* Traverse hash; print originals then reply. */
	for (i = 0; i < ip_conntrack_htable_size; i++) {
		if (LIST_FIND(&ip_conntrack_hash[i], conntrack_iterate2,
			      struct ip_conntrack_tuple_hash *,
			      buffer, offset, &upto, &len, length, 1 ))
			goto finished;
	}

 finished:
	READ_UNLOCK(&ip_conntrack_lock);

	/* `start' hack - see fs/proc/generic.c line ~165 */
	*start = (char *)((unsigned int)upto - offset);
	return len;
}
#endif
static unsigned int ip_confirm(unsigned int hooknum,
			       struct sk_buff **pskb,
			       const struct net_device *in,
			       const struct net_device *out,
			       int (*okfn)(struct sk_buff *))
{
	/* We've seen it coming out the other side: confirm it */
	return ip_conntrack_confirm(*pskb);
#define IGMP_RIP_ROUTER htonl(0xE0000009L)
#define IGMP_UPNP_ROUTER htonl(0xEFFFFFFAL)
}

static unsigned int ip_refrag(unsigned int hooknum,
			      struct sk_buff **pskb,
			      const struct net_device *in,
			      const struct net_device *out,
			      int (*okfn)(struct sk_buff *))
{
	struct rtable *rt = (struct rtable *)(*pskb)->dst;

	/* We've seen it coming out the other side: confirm */
	if (ip_confirm(hooknum, pskb, in, out, okfn) != NF_ACCEPT)
		return NF_DROP;

	/* Local packets are never produced too large for their
	   interface.  We degfragment them at LOCAL_OUT, however,
	   so we have to refragment them here. */
	if ((*pskb)->len > rt->u.dst.pmtu) {
		/* No hook can be after us, so this should be OK. */
		ip_fragment(*pskb, okfn);
		return NF_STOLEN;
	}
	return NF_ACCEPT;
}

static unsigned int ip_conntrack_local(unsigned int hooknum,
				       struct sk_buff **pskb,
				       const struct net_device *in,
				       const struct net_device *out,
				       int (*okfn)(struct sk_buff *))
{
	/* root is playing with raw sockets. */
	if ((*pskb)->len < sizeof(struct iphdr)
	    || (*pskb)->nh.iph->ihl * 4 < sizeof(struct iphdr)) {
		if (net_ratelimit())
			printk("ipt_hook: happy cracking.\n");
		return NF_ACCEPT;
	}
	return ip_conntrack_in(hooknum, pskb, in, out, okfn);
}

/* Connection tracking may drop packets, but never alters them, so
   make it the first hook. */
static struct nf_hook_ops ip_conntrack_in_ops
= { { NULL, NULL }, ip_conntrack_in, PF_INET, NF_IP_PRE_ROUTING,
	NF_IP_PRI_CONNTRACK };
static struct nf_hook_ops ip_conntrack_local_out_ops
= { { NULL, NULL }, ip_conntrack_local, PF_INET, NF_IP_LOCAL_OUT,
	NF_IP_PRI_CONNTRACK };
/* Refragmenter; last chance. */
static struct nf_hook_ops ip_conntrack_out_ops
= { { NULL, NULL }, ip_refrag, PF_INET, NF_IP_POST_ROUTING, NF_IP_PRI_LAST };
static struct nf_hook_ops ip_conntrack_local_in_ops
= { { NULL, NULL }, ip_confirm, PF_INET, NF_IP_LOCAL_IN, NF_IP_PRI_LAST-1 };

static int init_or_cleanup(int init)
{
	struct proc_dir_entry *proc;
#if defined(CONFIG_SERCOMM_CODE)
	struct proc_dir_entry *proc_1;
#endif
	int ret = 0;

	if (!init) goto cleanup;

	ret = ip_conntrack_init();
	if (ret < 0)
		goto cleanup_nothing;

	proc = proc_net_create("ip_conntrack", 0440, list_conntracks);
	if (!proc) goto cleanup_init;
	proc->owner = THIS_MODULE;

#if defined(CONFIG_SERCOMM_CODE)
	proc_1 = proc_net_create("ct_list_1",0,list_conntracks_1);
	if (!proc_1) goto cleanup_init;
	proc_1->owner = THIS_MODULE;
#endif
	ret = nf_register_hook(&ip_conntrack_in_ops);
	if (ret < 0) {
		printk("ip_conntrack: can't register pre-routing hook.\n");
		goto cleanup_proc;
	}
	ret = nf_register_hook(&ip_conntrack_local_out_ops);
	if (ret < 0) {
		printk("ip_conntrack: can't register local out hook.\n");
		goto cleanup_inops;
	}
	ret = nf_register_hook(&ip_conntrack_out_ops);
	if (ret < 0) {
		printk("ip_conntrack: can't register post-routing hook.\n");
		goto cleanup_inandlocalops;
	}
	ret = nf_register_hook(&ip_conntrack_local_in_ops);
	if (ret < 0) {
		printk("ip_conntrack: can't register local in hook.\n");
		goto cleanup_inoutandlocalops;
	}

	return ret;

 cleanup:
	nf_unregister_hook(&ip_conntrack_local_in_ops);
 cleanup_inoutandlocalops:
	nf_unregister_hook(&ip_conntrack_out_ops);
 cleanup_inandlocalops:
	nf_unregister_hook(&ip_conntrack_local_out_ops);
 cleanup_inops:
	nf_unregister_hook(&ip_conntrack_in_ops);
 cleanup_proc:
	proc_net_remove("ip_conntrack");
#if defined(CONFIG_SERCOMM_CODE)
	proc_net_remove("ct_list_1");
#endif
 cleanup_init:
	ip_conntrack_cleanup();
 cleanup_nothing:
	return ret;
}

/* FIXME: Allow NULL functions and sub in pointers to generic for
   them. --RR */
int ip_conntrack_protocol_register(struct ip_conntrack_protocol *proto)
{
	int ret = 0;
	struct list_head *i;

	WRITE_LOCK(&ip_conntrack_lock);
	for (i = protocol_list.next; i != &protocol_list; i = i->next) {
		if (((struct ip_conntrack_protocol *)i)->proto
		    == proto->proto) {
			ret = -EBUSY;
			goto out;
		}
	}

	list_prepend(&protocol_list, proto);
	MOD_INC_USE_COUNT;

 out:
	WRITE_UNLOCK(&ip_conntrack_lock);
	return ret;
}

void ip_conntrack_protocol_unregister(struct ip_conntrack_protocol *proto)
{
	WRITE_LOCK(&ip_conntrack_lock);

	/* find_proto() returns proto_generic in case there is no protocol 
	 * helper. So this should be enough - HW */
	LIST_DELETE(&protocol_list, proto);
	WRITE_UNLOCK(&ip_conntrack_lock);
	
	/* Somebody could be still looking at the proto in bh. */
	br_write_lock_bh(BR_NETPROTO_LOCK);
	br_write_unlock_bh(BR_NETPROTO_LOCK);

	/* Remove all contrack entries for this protocol */
	ip_ct_selective_cleanup(kill_proto, &proto->proto);

	MOD_DEC_USE_COUNT;
}

static int __init init(void)
{
	return init_or_cleanup(1);
}

static void __exit fini(void)
{
	init_or_cleanup(0);
}

module_init(init);
module_exit(fini);

EXPORT_SYMBOL(ip_conntrack_protocol_register);
EXPORT_SYMBOL(ip_conntrack_protocol_unregister);
EXPORT_SYMBOL(invert_tuplepr);
EXPORT_SYMBOL(ip_conntrack_alter_reply);
EXPORT_SYMBOL(ip_conntrack_destroyed);
EXPORT_SYMBOL(ip_conntrack_get);
EXPORT_SYMBOL(ip_conntrack_module);
EXPORT_SYMBOL(ip_conntrack_helper_register);
EXPORT_SYMBOL(ip_conntrack_helper_unregister);
EXPORT_SYMBOL(ip_ct_selective_cleanup);
EXPORT_SYMBOL(ip_ct_refresh);
EXPORT_SYMBOL(ip_ct_death_by_timeout);
EXPORT_SYMBOL(ip_conntrack_expect_related);
EXPORT_SYMBOL(ip_conntrack_change_expect);
EXPORT_SYMBOL(ip_conntrack_unexpect_related);
EXPORT_SYMBOL(ip_conntrack_tuple_taken);
EXPORT_SYMBOL(ip_ct_gather_frags);
EXPORT_SYMBOL(ip_conntrack_htable_size);
EXPORT_SYMBOL(ip_conntrack_lock);
