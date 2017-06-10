#ifndef _IP_CONNTRACK_H
#define _IP_CONNTRACK_H
/* Connection state tracking for netfilter.  This is separated from,
   but required by, the NAT layer; it can also be used by an iptables
   extension. */

#include <linux/config.h>
#include <linux/netfilter_ipv4/ip_conntrack_tuple.h>
#include <linux/bitops.h>
#include <asm/atomic.h>

#define CONFIG_IP_NF_FTP

#ifndef CONFIG_SERCOMM_CODE
#define CONFIG_SERCOMM_CODE 1
#endif

enum ip_conntrack_info
{
	/* Part of an established connection (either direction). */
	IP_CT_ESTABLISHED,

	/* Like NEW, but related to an existing connection, or ICMP error
	   (in either direction). */
	IP_CT_RELATED,

	/* Started a new connection to track (only
           IP_CT_DIR_ORIGINAL); may be a retransmission. */
	IP_CT_NEW,

	/* >= this indicates reply direction */
	IP_CT_IS_REPLY,

	/* Number of distinct IP_CT types (no NEW in reply dirn). */
	IP_CT_NUMBER = IP_CT_IS_REPLY * 2 - 1
};

#ifdef __KERNEL__

#include <linux/types.h>
#include <linux/skbuff.h>
#include <linux/netfilter_ipv4/ip_conntrack_tcp.h>
#include <linux/netfilter_ipv4/ip_conntrack_icmp.h>
#include <linux/netfilter_ipv4/ip_conntrack_pptp.h>
#include <linux/netfilter_ipv4/ip_conntrack_ipsec.h>
#include <linux/netfilter_ipv4/ip_conntrack_esp.h>

#ifdef CONFIG_NF_DEBUG
#define IP_NF_ASSERT(x)							\
do {									\
	if (!(x))							\
		/* Wooah!  I'm tripping my conntrack in a frenzy of	\
		   netplay... */					\
		printk("NF_IP_ASSERT: %s:%i(%s)\n",			\
		       __FILE__, __LINE__, __FUNCTION__);		\
} while(0)
#else
#define IP_NF_ASSERT(x)
#endif

/* Bitset representing status of connection. */
enum ip_conntrack_status {
	/* It's an expected connection: bit 0 set.  This bit never changed */
	IPS_EXPECTED_BIT = 0,
	IPS_EXPECTED = (1 << IPS_EXPECTED_BIT),

	/* We've seen packets both ways: bit 1 set.  Can be set, not unset. */
	IPS_SEEN_REPLY_BIT = 1,
	IPS_SEEN_REPLY = (1 << IPS_SEEN_REPLY_BIT),

	/* Conntrack should never be early-expired. */
	IPS_ASSURED_BIT = 2,
	IPS_ASSURED = (1 << IPS_ASSURED_BIT),

	/* Connection is confirmed: originating packet has left box */
	IPS_CONFIRMED_BIT = 3,
	IPS_CONFIRMED = (1 << IPS_CONFIRMED_BIT),
};

#ifdef CONFIG_IP_NF_NAT_NEEDED
	#include <linux/netfilter_ipv4/ip_nat.h>
#endif

/* Add protocol helper include file here */

#if defined(CONFIG_IP_NF_FTP) || defined(CONFIG_IP_NF_FTP_MODULE)
	#include <linux/netfilter_ipv4/ip_conntrack_ftp.h>
#endif

#if defined(CONFIG_IP_NF_IRC) || defined(CONFIG_IP_NF_IRC_MODULE)
	#include <linux/netfilter_ipv4/ip_conntrack_irc.h>
#endif

#if defined(CONFIG_IP_NF_RTSP) || defined(CONFIG_IP_NF_RTSP_MODULE)
	#include <linux/netfilter_ipv4/ip_conntrack_rtsp.h>
#endif

#if defined(CONFIG_IP_NF_TALK) || defined(CONFIG_IP_NF_TALK_MODULE)
	#include <linux/netfilter_ipv4/ip_conntrack_talk.h>
#endif

#if defined(CONFIG_IP_NF_H323) || defined(CONFIG_IP_NF_H323_MODULE)
	#include <linux/netfilter_ipv4/ip_conntrack_h323.h>
#endif

#if defined(CONFIG_IP_NF_PPTP) || defined(CONFIG_IP_NF_PPTP_MODULE)
	#include <linux/netfilter_ipv4/ip_conntrack_pptp.h>
#endif

#ifdef CONFIG_IP_NF_NAT_NEEDED
	#include <linux/netfilter_ipv4/ip_nat_pptp.h>
	#include <linux/netfilter_ipv4/ip_nat_ipsec.h>
	#include <linux/netfilter_ipv4/ip_nat_rtsp.h>
	#include <linux/netfilter_ipv4/ip_nat_esp.h>
#endif

struct ip_conntrack_expect
{
	/* Internal linked list (global expectation list) */
	struct list_head list;

	/* expectation list for this master */
	struct list_head expected_list;

	/* The conntrack of the master connection */
	struct ip_conntrack *expectant;

	/* The conntrack of the sibling connection, set after
	 * expectation arrived */
	struct ip_conntrack *sibling;

	/* Tuple saved for conntrack */
	struct ip_conntrack_tuple ct_tuple;

	/* Data filled out by the conntrack helpers follow: */
	
	/* We expect this tuple, with the following mask */
	struct ip_conntrack_tuple tuple, mask;

	/* Function to call after setup and insertion */
	int (*expectfn)(struct ip_conntrack *new);

	/* At which sequence number did this expectation occur */
	u_int32_t seq;

	union {
		/* insert conntrack helper private data (expect) here */
#if defined(CONFIG_IP_NF_FTP) || defined(CONFIG_IP_NF_FTP_MODULE)
		struct ip_ct_ftp_expect exp_ftp_info;
#endif

#if defined(CONFIG_IP_NF_IRC) || defined(CONFIG_IP_NF_IRC_MODULE)
                struct ip_ct_irc_expect exp_irc_info;
#endif

#if defined(CONFIG_IP_NF_RTSP) || defined(CONFIG_IP_NF_RTSP_MODULE)
                struct ip_ct_rtsp_expect exp_rtsp_info;
#endif

#if defined(CONFIG_IP_NF_TALK) || defined(CONFIG_IP_NF_TALK_MODULE)
		struct ip_ct_talk_expect exp_talk_info;
#endif

#if defined(CONFIG_IP_NF_H323) || defined(CONFIG_IP_NF_H323_MODULE)
                struct ip_ct_h225_expect exp_h225_info;
#endif

#if defined(CONFIG_IP_NF_PPTP) || defined(CONFIG_IP_NF_PPTP_MODULE)
                struct ip_ct_pptp_expect exp_pptp_info;
#endif

#ifdef CONFIG_IP_NF_NAT_NEEDED
		union {
			/* insert nat helper private data here */
		} nat;
#endif
	} help;
};

#define IP_CONNTRACK_EXPECT_SIZEOF_HEAD \
	(2*sizeof(struct list_head) \
	+ 2*sizeof(struct ip_conntrack *) \
	+ 3*sizeof(struct ip_conntrack_tuple))
#define IP_CONNTRACK_EXPECT_SIZEOF_DATA \
	(sizeof(struct ip_conntrack_expect) \
	- IP_CONNTRACK_EXPECT_SIZEOF_HEAD)


#define IPS_RESERVE 0x01
struct ip_conntrack
{
	/* Usage count in here is 1 for hash table/destruct timer, 1 per skb,
           plus 1 for any connection(s) we are `master' for */
	struct nf_conntrack ct_general;

	/* These are my tuples; original and reply */
	struct ip_conntrack_tuple_hash tuplehash[IP_CT_DIR_MAX];

	/* Have we seen traffic both ways yet? (bitset) */
	unsigned long status;

	/* Timer function; drops refcnt when it goes off. */
	struct timer_list timeout;

	/* If we're expecting another related connection, this will be
           in expected linked list */
	struct list_head sibling_list;
	
	/* Current number of expected connections */
	unsigned int expecting;

	/* If we were expected by an expectation, this will be it */
	struct ip_conntrack_expect *master;

	/* Helper, if any. */
	struct ip_conntrack_helper *helper;

	/* Our various nf_ct_info structs specify *what* relation this
           packet has to the conntrack */
	struct nf_ct_info infos[IP_CT_NUMBER];

	/* Storage reserved for other modules: */

	union {
		struct ip_ct_tcp tcp;
		struct ip_ct_icmp icmp;
	} proto;

	union {
               /* insert conntrack helper private data (master) here */
#if defined(CONFIG_IP_NF_FTP) || defined(CONFIG_IP_NF_FTP_MODULE)
                struct ip_ct_ftp_master ct_ftp_info;
#endif

#if defined(CONFIG_IP_NF_IRC) || defined(CONFIG_IP_NF_IRC_MODULE)
                struct ip_ct_irc_master ct_irc_info;
#endif

#if defined(CONFIG_IP_NF_RTSP) || defined(CONFIG_IP_NF_RTSP_MODULE)
                struct ip_ct_rtsp_master ct_rtsp_info;
#endif

#if defined(CONFIG_IP_NF_TALK) || defined(CONFIG_IP_NF_TALK_MODULE)
                struct ip_ct_talk_master ct_talk_info;
#endif

#if defined(CONFIG_IP_NF_H323) || defined(CONFIG_IP_NF_H323_MODULE)
                struct ip_ct_h225_master ct_h225_info;
#endif

#if defined(CONFIG_IP_NF_PPTP) || defined(CONFIG_IP_NF_PPTP_MODULE)
              	struct ip_ct_pptp_master ct_pptp_info;
#endif

#if defined(CONFIG_IP_NF_IPSEC) || defined(CONFIG_IP_NF_IPSEC_MODULE)
		struct ip_ct_esp_master   ct_esp_info;
#endif
		struct ip_ct_ipsec_master ct_ipsec_info;

	} help;

#ifdef CONFIG_IP_NF_NAT_NEEDED
	struct {
		struct ip_nat_info info;
		union {
			/* insert nat helper private data here */
#if defined(CONFIG_IP_NF_PPTP) || defined(CONFIG_IP_NF_PPTP_MODULE)
                      struct ip_nat_pptp_info pptp_info;
#endif

#if defined(CONFIG_IP_NF_IPSEC) || defined(CONFIG_IP_NF_IPSEC_MODULE)
                      struct ip_nat_esp_info   esp_info;
#endif
                      struct ip_nat_ipsec_info ipsec_info;
		} help;
#if defined(CONFIG_IP_NF_TARGET_MASQUERADE) || \
	defined(CONFIG_IP_NF_TARGET_MASQUERADE_MODULE)
		int masq_index;
#endif



#if defined(CONFIG_IP_NF_RTSP) || defined(CONFIG_IP_NF_RTSP_MODULE)
                struct ip_nat_rtsp_info rtsp_info;
#endif
	} nat;
#endif /* CONFIG_IP_NF_NAT_NEEDED */

#if defined(CONFIG_SERCOMM_CODE)
	struct {
		int mask;
	}reserve;
#endif

#if defined(CONFIG_IP_NF_MATCH_LAYER7) || defined(CONFIG_IP_NF_MATCH_LAYER7_MODULE)
	struct {
		unsigned int numpackets; /* surely this is kept track of somewhere else, right? I can't find it... */
		char * app_proto; /* "http", "ftp", etc.  NULL if unclassifed */
		
		/* the application layer data so far.  NULL if ->numpackets > numpackets */
		char * app_data; 

		unsigned int app_data_len;
	} layer7;
#endif
};

/* get master conntrack via master expectation */
#define master_ct(conntr) (conntr->master ? conntr->master->expectant : NULL)

/* Alter reply tuple (maybe alter helper).  If it's already taken,
   return 0 and don't do alteration. */
extern int
ip_conntrack_alter_reply(struct ip_conntrack *conntrack,
			 const struct ip_conntrack_tuple *newreply);

/* Is this tuple taken? (ignoring any belonging to the given
   conntrack). */
extern int
ip_conntrack_tuple_taken(const struct ip_conntrack_tuple *tuple,
			 const struct ip_conntrack *ignored_conntrack);

/* Return conntrack_info and tuple hash for given skb. */
extern struct ip_conntrack *
ip_conntrack_get(struct sk_buff *skb, enum ip_conntrack_info *ctinfo);

extern struct module *ip_conntrack_module;

extern int invert_tuplepr(struct ip_conntrack_tuple *inverse,
			  const struct ip_conntrack_tuple *orig);

/* Refresh conntrack for this many jiffies */
extern void ip_ct_refresh(struct ip_conntrack *ct,
			  unsigned long extra_jiffies);

/* Kill conntrack */
extern void ip_ct_death_by_timeout(unsigned long ul_conntrack);

/* These are for NAT.  Icky. */
/* Call me when a conntrack is destroyed. */
extern void (*ip_conntrack_destroyed)(struct ip_conntrack *conntrack);

/* Returns new sk_buff, or NULL */
struct sk_buff *
ip_ct_gather_frags(struct sk_buff *skb);

/* Delete all conntracks which match. */
extern void
ip_ct_selective_cleanup(int (*kill)(const struct ip_conntrack *i, void *data),
			void *data);

/* It's confirmed if it is, or has been in the hash table. */
static inline int is_confirmed(struct ip_conntrack *ct)
{
	return test_bit(IPS_CONFIRMED_BIT, &ct->status);
}

extern unsigned int ip_conntrack_htable_size;
#endif /* __KERNEL__ */
#endif /* _IP_CONNTRACK_H */
