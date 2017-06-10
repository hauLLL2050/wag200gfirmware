/****************************************************************************
        TNETD73xx Software Support
        Copyright(c) 2000, Texas Instruments Incorporated. All Rights Reserved.

        FILE: cpmac_reg.h   Register definitions for the CPMAC module

         DESCRIPTION:
                This include file contains register definitions for the
                CPMAC module.

         HISTORY:
              15Nov00 BEGR Original version written
              30May02 MICK Added bits for Int Vector
              19Sep02 MICK Added INT_ACK per Channel
              08Nov02 GDUN Updated to use base
              12Nov02 MICK Incorporated into CPHAL 
*****************************************************************************/
#ifndef _INC_CPMAC_REG
#define _INC_CPMAC_REG

#ifndef MEM_PTR
#define MEM_PTR volatile bit32u *
#endif

/***************************************************************************
 *                                                                         
 *         C P M A C  M E M O R Y  M A P 
 *                                                                         
 **************************************************************************/

#define pCPMAC_TX_IDVER(base)                 ((MEM_PTR)(base+0x000))
#define  CPMAC_TX_IDVER(base)                 (*pCPMAC_TX_IDVER(base))
#define pCPMAC_TX_CONTROL(base)               ((MEM_PTR)(base+0x004))
#define  CPMAC_TX_CONTROL(base)               (*pCPMAC_TX_CONTROL(base))
#define pCPMAC_TX_TEARDOWN(base)              ((MEM_PTR)(base+0x008))
#define  CPMAC_TX_TEARDOWN(base)              (*pCPMAC_TX_TEARDOWN(base))
#define pCPMAC_RX_IDVER(base)                 ((MEM_PTR)(base+0x010))
#define  CPMAC_RX_IDVER(base)                 (*pCPMAC_RX_IDVER(base))
#define pCPMAC_RX_CONTROL(base)               ((MEM_PTR)(base+0x014))
#define  CPMAC_RX_CONTROL(base)               (*pCPMAC_RX_CONTROL(base))
#define pCPMAC_RX_TEARDOWN(base)              ((MEM_PTR)(base+0x018))
#define  CPMAC_RX_TEARDOWN(base)              (*pCPMAC_RX_TEARDOWN(base))
#define pCPMAC_RX_MBP_ENABLE(base)            ((MEM_PTR)(base+0x100))
#define  CPMAC_RX_MBP_ENABLE(base)            (*pCPMAC_RX_MBP_ENABLE(base))
#define pCPMAC_RX_UNICAST_SET(base)           ((MEM_PTR)(base+0x104))
#define  CPMAC_RX_UNICAST_SET(base)           (*pCPMAC_RX_UNICAST_SET(base))
#define pCPMAC_RX_UNICAST_CLEAR(base)         ((MEM_PTR)(base+0x108))
#define  CPMAC_RX_UNICAST_CLEAR(base)         (*pCPMAC_RX_UNICAST_CLEAR(base))
#define pCPMAC_RX_MAXLEN(base)                ((MEM_PTR)(base+0x10C))
#define  CPMAC_RX_MAXLEN(base)                (*pCPMAC_RX_MAXLEN(base))
#define pCPMAC_RX_BUFFER_OFFSET(base)         ((MEM_PTR)(base+0x110))
#define  CPMAC_RX_BUFFER_OFFSET(base)         (*pCPMAC_RX_BUFFER_OFFSET(base))
#define pCPMAC_RX_FILTERLOWTHRESH(base)       ((MEM_PTR)(base+0x114))
#define  CPMAC_RX_FILTERLOWTHRESH(base)       (*pCPMAC_RX_FILTERLOWTHRESH(base))
#define pCPMAC_RX0_FLOWTHRESH(base)           ((MEM_PTR)(base+0x120))
#define  CPMAC_RX0_FLOWTHRESH(base)           (*pCPMAC_RX0_FLOWTHRESH(base))
#define pCPMAC_RX1_FLOWTHRESH(base)           ((MEM_PTR)(base+0x124))
#define  CPMAC_RX1_FLOWTHRESH(base)           (*pCPMAC_RX1_FLOWTHRESH(base))
#define pCPMAC_RX2_FLOWTHRESH(base)           ((MEM_PTR)(base+0x128))
#define  CPMAC_RX2_FLOWTHRESH(base)           (*pCPMAC_RX2_FLOWTHRESH(base))
#define pCPMAC_RX3_FLOWTHRESH(base)           ((MEM_PTR)(base+0x12C))
#define  CPMAC_RX3_FLOWTHRESH(base)           (*pCPMAC_RX3_FLOWTHRESH(base))
#define pCPMAC_RX4_FLOWTHRESH(base)           ((MEM_PTR)(base+0x130))
#define  CPMAC_RX4_FLOWTHRESH(base)           (*pCPMAC_RX4_FLOWTHRESH(base))
#define pCPMAC_RX5_FLOWTHRESH(base)           ((MEM_PTR)(base+0x134))
#define  CPMAC_RX5_FLOWTHRESH(base)           (*pCPMAC_RX5_FLOWTHRESH(base))
#define pCPMAC_RX6_FLOWTHRESH(base)           ((MEM_PTR)(base+0x138))
#define  CPMAC_RX6_FLOWTHRESH(base)           (*pCPMAC_RX6_FLOWTHRESH(base))
#define pCPMAC_RX7_FLOWTHRESH(base)           ((MEM_PTR)(base+0x13C))
#define  CPMAC_RX7_FLOWTHRESH(base)           (*pCPMAC_RX7_FLOWTHRESH(base))
#define pCPMAC_RX0_FREEBUFFER(base)           ((MEM_PTR)(base+0x140))
#define  CPMAC_RX0_FREEBUFFER(base)           (*pCPMAC_RX0_FREEBUFFER(base))
#define pCPMAC_RX1_FREEBUFFER(base)           ((MEM_PTR)(base+0x144))
#define  CPMAC_RX1_FREEBUFFER(base)           (*pCPMAC_RX1_FREEBUFFER(base))
#define pCPMAC_RX2_FREEBUFFER(base)           ((MEM_PTR)(base+0x148))
#define  CPMAC_RX2_FREEBUFFER(base)           (*pCPMAC_RX2_FREEBUFFER(base))
#define pCPMAC_RX3_FREEBUFFER(base)           ((MEM_PTR)(base+0x14C))
#define  CPMAC_RX3_FREEBUFFER(base)           (*pCPMAC_RX3_FREEBUFFER(base))
#define pCPMAC_RX4_FREEBUFFER(base)           ((MEM_PTR)(base+0x150))
#define  CPMAC_RX4_FREEBUFFER(base)           (*pCPMAC_RX4_FREEBUFFER(base))
#define pCPMAC_RX5_FREEBUFFER(base)           ((MEM_PTR)(base+0x154))
#define  CPMAC_RX5_FREEBUFFER(base)           (*pCPMAC_RX5_FREEBUFFER(base))
#define pCPMAC_RX6_FREEBUFFER(base)           ((MEM_PTR)(base+0x158))
#define  CPMAC_RX6_FREEBUFFER(base)           (*pCPMAC_RX6_FREEBUFFER(base))
#define pCPMAC_RX7_FREEBUFFER(base)           ((MEM_PTR)(base+0x15C))
#define  CPMAC_RX7_FREEBUFFER(base)           (*pCPMAC_RX7_FREEBUFFER(base))
#define pCPMAC_MACCONTROL(base)               ((MEM_PTR)(base+0x160))
#define  CPMAC_MACCONTROL(base)               (*pCPMAC_MACCONTROL(base))
#define pCPMAC_MACSTATUS(base)                ((MEM_PTR)(base+0x164))
#define  CPMAC_MACSTATUS(base)                (*pCPMAC_MACSTATUS(base))
#define pCPMAC_EMCONTROL(base)                ((MEM_PTR)(base+0x168))
#define  CPMAC_EMCONTROL(base)                (*pCPMAC_EMCONTROL(base))
#define pCPMAC_TX_INTSTAT_RAW(base)           ((MEM_PTR)(base+0x170))
#define  CPMAC_TX_INTSTAT_RAW(base)           (*pCPMAC_TX_INTSTAT_RAW(base))
#define pCPMAC_TX_INTSTAT_MASKED(base)        ((MEM_PTR)(base+0x174))
#define  CPMAC_TX_INTSTAT_MASKED(base)        (*pCPMAC_TX_INTSTAT_MASKED(base))
#define pCPMAC_TX_INTMASK_SET(base)           ((MEM_PTR)(base+0x178))
#define  CPMAC_TX_INTMASK_SET(base)           (*pCPMAC_TX_INTMASK_SET(base))
#define pCPMAC_TX_INTMASK_CLEAR(base)         ((MEM_PTR)(base+0x17C))
#define  CPMAC_TX_INTMASK_CLEAR(base)         (*pCPMAC_TX_INTMASK_CLEAR(base))
#define pCPMAC_MAC_IN_VECTOR(base)            ((MEM_PTR)(base+0x180))
#define  CPMAC_MAC_IN_VECTOR(base)            (*pCPMAC_MAC_IN_VECTOR(base))
#define pCPMAC_MAC_EOI_VECTOR(base)           ((MEM_PTR)(base+0x184))
#define  CPMAC_MAC_EOI_VECTOR(base)           (*pCPMAC_MAC_EOI_VECTOR(base))
#define pCPMAC_RX_INTSTAT_RAW(base)           ((MEM_PTR)(base+0x190))
#define  CPMAC_RX_INTSTAT_RAW(base)           (*pCPMAC_RX_INTSTAT_RAW(base))
#define pCPMAC_RX_INTSTAT_MASKED(base)        ((MEM_PTR)(base+0x194))
#define  CPMAC_RX_INTSTAT_MASKED(base)        (*pCPMAC_RX_INTSTAT_MASKED(base))
#define pCPMAC_RX_INTMASK_SET(base)           ((MEM_PTR)(base+0x198))
#define  CPMAC_RX_INTMASK_SET(base)           (*pCPMAC_RX_INTMASK_SET(base))
#define pCPMAC_RX_INTMASK_CLEAR(base)         ((MEM_PTR)(base+0x19C))
#define  CPMAC_RX_INTMASK_CLEAR(base)         (*pCPMAC_RX_INTMASK_CLEAR(base))
#define pCPMAC_MAC_INTSTAT_RAW(base)          ((MEM_PTR)(base+0x1A0))
#define  CPMAC_MAC_INTSTAT_RAW(base)          (*pCPMAC_MAC_INTSTAT_RAW(base))
#define pCPMAC_MAC_INTSTAT_MASKED(base)       ((MEM_PTR)(base+0x1A4))
#define  CPMAC_MAC_INTSTAT_MASKED(base)       (*pCPMAC_MAC_INTSTAT_MASKED(base))
#define pCPMAC_MAC_INTMASK_SET(base)          ((MEM_PTR)(base+0x1A8))
#define  CPMAC_MAC_INTMASK_SET(base)          (*pCPMAC_MAC_INTMASK_SET(base))
#define pCPMAC_MAC_INTMASK_CLEAR(base)        ((MEM_PTR)(base+0x1AC))
#define  CPMAC_MAC_INTMASK_CLEAR(base)        (*pCPMAC_MAC_INTMASK_CLEAR(base))
#define pCPMAC_MACADDRLO_0(base)              ((MEM_PTR)(base+0x1B0))
#define  CPMAC_MACADDRLO_0(base)              (*pCPMAC_MACADDRLO_0(base))
#define pCPMAC_MACADDRLO_1(base)              ((MEM_PTR)(base+0x1B4))
#define  CPMAC_MACADDRLO_1(base)              (*pCPMAC_MACADDRLO_1(base))
#define pCPMAC_MACADDRLO_2(base)              ((MEM_PTR)(base+0x1B8))
#define  CPMAC_MACADDRLO_2(base)              (*pCPMAC_MACADDRLO_2(base))
#define pCPMAC_MACADDRLO_3(base)              ((MEM_PTR)(base+0x1BC))
#define  CPMAC_MACADDRLO_3(base)              (*pCPMAC_MACADDRLO_3(base))
#define pCPMAC_MACADDRLO_4(base)              ((MEM_PTR)(base+0x1C0))
#define  CPMAC_MACADDRLO_4(base)              (*pCPMAC_MACADDRLO_4(base))
#define pCPMAC_MACADDRLO_5(base)              ((MEM_PTR)(base+0x1C4))
#define  CPMAC_MACADDRLO_5(base)              (*pCPMAC_MACADDRLO_5(base))
#define pCPMAC_MACADDRLO_6(base)              ((MEM_PTR)(base+0x1C8))
#define  CPMAC_MACADDRLO_6(base)              (*pCPMAC_MACADDRLO_6(base))
#define pCPMAC_MACADDRLO_7(base)              ((MEM_PTR)(base+0x1CC))
#define  CPMAC_MACADDRLO_7(base)              (*pCPMAC_MACADDRLO_7(base))
#define pCPMAC_MACADDRMID(base)               ((MEM_PTR)(base+0x1D0))
#define  CPMAC_MACADDRMID(base)               (*pCPMAC_MACADDRMID(base))
#define pCPMAC_MACADDRHI(base)                ((MEM_PTR)(base+0x1D4))
#define  CPMAC_MACADDRHI(base)                (*pCPMAC_MACADDRHI(base))
#define pCPMAC_MACHASH1(base)                 ((MEM_PTR)(base+0x1D8))
#define  CPMAC_MACHASH1(base)                 (*pCPMAC_MACHASH1(base))
#define pCPMAC_MACHASH2(base)                 ((MEM_PTR)(base+0x1DC))
#define  CPMAC_MACHASH2(base)                 (*pCPMAC_MACHASH2(base))
#define pCPMAC_BOFFTEST(base)                 ((MEM_PTR)(base+0x1E0))
#define  CPMAC_BOFFTEST(base)                 (*pCPMAC_BOFFTEST(base))
#define pCPMAC_PACTEST(base)                  ((MEM_PTR)(base+0x1E4))
#define  CPMAC_PACTEST(base)                  (*pCPMAC_PACTEST(base))
#define pCPMAC_RXPAUSE(base)                  ((MEM_PTR)(base+0x1E8))
#define  CPMAC_RXPAUSE(base)                  (*pCPMAC_RXPAUSE(base))
#define pCPMAC_TXPAUSE(base)                  ((MEM_PTR)(base+0x1EC))
#define  CPMAC_TXPAUSE(base)                  (*pCPMAC_TXPAUSE(base))
/* STATISTICS */
#define pCPMAC_RXGOODFRAMES(base)             ((MEM_PTR)(base+0x200))
#define  CPMAC_RXGOODFRAMES(base)             (*pCPMAC_RXGOODFRAMES(base))
#define pCPMAC_RXBROADCASTFRAMES(base)        ((MEM_PTR)(base+0x204))
#define  CPMAC_RXBROADCASTFRAMES(base)        (*pCPMAC_RXBROADCASTFRAMES(base))
#define pCPMAC_RXMULTICASTFRAMES(base)        ((MEM_PTR)(base+0x208))
#define  CPMAC_RXMULTICASTFRAMES(base)        (*pCPMAC_RXMULTICASTFRAMES(base))
#define pCPMAC_RXPAUSEFRAMES(base)            ((MEM_PTR)(base+0x20C))
#define   CPMAC_RXPAUSEFRAMES(base)           (*pCPMAC_RXPAUSEFRAMES(base))
#define pCPMAC_RXCRCERRORS(base)              ((MEM_PTR)(base+0x210))
#define   CPMAC_RXCRCERRORS(base)             (*pCPMAC_RXCRCERRORS(base))
#define pCPMAC_RXALIGNCODEERRORS(base)        ((MEM_PTR)(base+0x214))
#define   CPMAC_RXALIGNCODEERRORS(base)       (*pCPMAC_RXALIGNCODEERRORS(base))
#define pCPMAC_RXOVERSIZEDFRAMES(base)        ((MEM_PTR)(base+0x218))
#define   CPMAC_RXOVERSIZEDFRAMES(base)       (*pCPMAC_RXOVERSIZEDFRAMES(base))
#define pCPMAC_RXJABBERFRAMES(base)           ((MEM_PTR)(base+0x21C))
#define  CPMAC_RXJABBERFRAMES(base)           (*pCPMAC_RXJABBERFRAMES(base))
#define pCPMAC_RXUNDERSIZEDFRAMES(base)       ((MEM_PTR)(base+0x220))
#define  CPMAC_RXUNDERSIZEDFRAMES(base)       (*pCPMAC_RXUNDERSIZEDFRAMES(base))
#define pCPMAC_RXFRAGMENTS(base)              ((MEM_PTR)(base+0x224))
#define  CPMAC_RXFRAGMENTS(base)              (*pCPMAC_RXFRAGMENTS(base))
#define pCPMAC_RXFILTEREDFRAMES(base)         ((MEM_PTR)(base+0x228))
#define  CPMAC_RXFILTEREDFRAMES(base)         (*pCPMAC_RXFILTEREDFRAMES(base))
#define pCPMAC_RXQOSFILTEREDFRAMES(base)      ((MEM_PTR)(base+0x22C))
#define  CPMAC_RXQOSFILTEREDFRAMES(base)      (*pCPMAC_RXQOSFILTEREDFRAMES(base))
#define pCPMAC_RXOCTETS(base)                 ((MEM_PTR)(base+0x230))
#define  CPMAC_RXOCTETS(base)                 (*pCPMAC_RXOCTETS(base))
#define pCPMAC_TXGOODFRAMES(base)             ((MEM_PTR)(base+0x234))
#define  CPMAC_TXGOODFRAMES(base)             (*pCPMAC_TXGOODFRAMES(base))
#define pCPMAC_TXBROADCASTFRAMES(base)        ((MEM_PTR)(base+0x238))
#define  CPMAC_TXBROADCASTFRAMES(base)        (*pCPMAC_TXBROADCASTFRAMES(base))
#define pCPMAC_TXMULTICASTFRAMES(base)        ((MEM_PTR)(base+0x23C))
#define  CPMAC_TXMULTICASTFRAMES(base)        (*pCPMAC_TXMULTICASTFRAMES(base))
#define pCPMAC_TXPAUSEFRAMES(base)            ((MEM_PTR)(base+0x240))
#define  CPMAC_TXPAUSEFRAMES(base)            (*pCPMAC_TXPAUSEFRAMES(base))
#define pCPMAC_TXDEFERREDFRAMES(base)         ((MEM_PTR)(base+0x244))
#define  CPMAC_TXDEFERREDFRAMES(base)         (*pCPMAC_TXDEFERREDFRAMES(base))
#define pCPMAC_TXCOLLISIONFRAMES(base)        ((MEM_PTR)(base+0x248))
#define  CPMAC_TXCOLLISIONFRAMES(base)        (*pCPMAC_TXCOLLISIONFRAMES(base))
#define pCPMAC_TXSINGLECOLLFRAMES(base)       ((MEM_PTR)(base+0x24C))
#define  CPMAC_TXSINGLECOLLFRAMES(base)       (*pCPMAC_TXSINGLECOLLFRAMES(base))
#define pCPMAC_TXMULTCOLLFRAMES(base)         ((MEM_PTR)(base+0x250))
#define  CPMAC_TXMULTCOLLFRAMES(base)         (*pCPMAC_TXMULTCOLLFRAMES(base))
#define pCPMAC_TXEXCESSIVECOLLISIONS(base)    ((MEM_PTR)(base+0x254))
#define  CPMAC_TXEXCESSIVECOLLISIONS(base)    (*pCPMAC_TXEXCESSIVECOLLISIONS(base))
#define pCPMAC_TXLATECOLLISIONS(base)         ((MEM_PTR)(base+0x258))
#define  CPMAC_TXLATECOLLISIONS(base)         (*pCPMAC_TXLATECOLLISIONS(base))
#define pCPMAC_TXUNDERRUN(base)               ((MEM_PTR)(base+0x25C))
#define  CPMAC_TXUNDERRUN(base)               (*pCPMAC_TXUNDERRUN(base))
#define pCPMAC_TXCARRIERSENSEERRORS(base)     ((MEM_PTR)(base+0x260))
#define  CPMAC_TXCARRIERSENSEERRORS(base)     (*pCPMAC_TXCARRIERSENSEERRORS(base))
#define pCPMAC_TXOCTETS(base)                 ((MEM_PTR)(base+0x264))
#define  CPMAC_TXOCTETS(base)                 (*pCPMAC_TXOCTETS(base))
#define pCPMAC_64OCTETFRAMES(base)            ((MEM_PTR)(base+0x268))
#define  CPMAC_64OCTETFRAMES(base)            (*pCPMAC_64OCTETFRAMES(base))
#define pCPMAC_65T127OCTETFRAMES(base)        ((MEM_PTR)(base+0x26C))
#define  CPMAC_65T127OCTETFRAMES(base)        (*pCPMAC_65T127OCTETFRAMES(base))
#define pCPMAC_128T255OCTETFRAMES(base)       ((MEM_PTR)(base+0x270))
#define  CPMAC_128T255OCTETFRAMES(base)       (*pCPMAC_128T255OCTETFRAMES(base))
#define pCPMAC_256T511OCTETFRAMES(base)       ((MEM_PTR)(base+0x274))
#define  CPMAC_256T511OCTETFRAMES(base)       (*pCPMAC_256T511OCTETFRAMES(base))
#define pCPMAC_512T1023OCTETFRAMES(base)      ((MEM_PTR)(base+0x278))
#define  CPMAC_512T1023OCTETFRAMES(base)      (*pCPMAC_512T1023OCTETFRAMES(base))
#define pCPMAC_1024TUPOCTETFRAMES(base)       ((MEM_PTR)(base+0x27C))
#define  CPMAC_1024TUPOCTETFRAMES(base)       (*pCPMAC_1024TUPOCTETFRAMES(base))
#define pCPMAC_NETOCTETS(base)                ((MEM_PTR)(base+0x280))
#define  CPMAC_NETOCTETS(base)                (*pCPMAC_NETOCTETS(base))
#define pCPMAC_RXSOFOVERRUNS(base)            ((MEM_PTR)(base+0x284))
#define  CPMAC_RXSOFOVERRUNS(base)            (*pCPMAC_RXSOFOVERRUNS(base))
#define pCPMAC_RXMOFOVERRUNS(base)            ((MEM_PTR)(base+0x288))
#define  CPMAC_RXMOFOVERRUNS(base)            (*pCPMAC_RXMOFOVERRUNS(base))
#define pCPMAC_RXDMAOVERRUNS(base)            ((MEM_PTR)(base+0x28C))
#define  CPMAC_RXDMAOVERRUNS(base)            (*pCPMAC_RXDMAOVERRUNS(base))

#define  CPMAC_TX_HDP(base,ch)                (*(MEM_PTR)(base+0x600+(4*ch)))
#define pCPMAC_TX0_HDP(base)                  ((MEM_PTR)(base+0x600))
#define  CPMAC_TX0_HDP(base)                  (*pCPMAC_TX0_HDP(base))
#define pCPMAC_TX1_HDP(base)                  ((MEM_PTR)(base+0x604))
#define  CPMAC_TX1_HDP(base)                  (*pCPMAC_TX1_HDP(base))
#define pCPMAC_TX2_HDP(base)                  ((MEM_PTR)(base+0x608))
#define  CPMAC_TX2_HDP(base)                  (*pCPMAC_TX2_HDP(base))
#define pCPMAC_TX3_HDP(base)                  ((MEM_PTR)(base+0x60C))
#define  CPMAC_TX3_HDP(base)                  (*pCPMAC_TX3_HDP(base))
#define pCPMAC_TX4_HDP(base)                  ((MEM_PTR)(base+0x610))
#define  CPMAC_TX4_HDP(base)                  (*pCPMAC_TX4_HDP(base))
#define pCPMAC_TX5_HDP(base)                  ((MEM_PTR)(base+0x614))
#define  CPMAC_TX5_HDP(base)                  (*pCPMAC_TX5_HDP(base))
#define pCPMAC_TX6_HDP(base)                  ((MEM_PTR)(base+0x618))
#define  CPMAC_TX6_HDP(base)                  (*pCPMAC_TX6_HDP(base))
#define pCPMAC_TX7_HDP(base)                  ((MEM_PTR)(base+0x61C))
#define  CPMAC_TX7_HDP(base)                  (*pCPMAC_TX7_HDP(base))
#define  CPMAC_RX_HDP(base,ch)                (*(MEM_PTR)(base+0x620+(4*ch)))
#define pCPMAC_RX0_HDP(base)                  ((MEM_PTR)(base+0x620))
#define  CPMAC_RX0_HDP(base)                  (*pCPMAC_RX0_HDP(base))
#define pCPMAC_RX1_HDP(base)                  ((MEM_PTR)(base+0x624))
#define  CPMAC_RX1_HDP(base)                  (*pCPMAC_RX1_HDP(base))
#define pCPMAC_RX2_HDP(base)                  ((MEM_PTR)(base+0x628))
#define  CPMAC_RX2_HDP(base)                  (*pCPMAC_RX2_HDP(base))
#define pCPMAC_RX3_HDP(base)                  ((MEM_PTR)(base+0x62C))
#define  CPMAC_RX3_HDP(base)                  (*pCPMAC_RX3_HDP(base))
#define pCPMAC_RX4_HDP(base)                  ((MEM_PTR)(base+0x630))
#define  CPMAC_RX4_HDP(base)                  (*pCPMAC_RX4_HDP(base))
#define pCPMAC_RX5_HDP(base)                  ((MEM_PTR)(base+0x634))
#define  CPMAC_RX5_HDP(base)                  (*pCPMAC_RX5_HDP(base))
#define pCPMAC_RX6_HDP(base)                  ((MEM_PTR)(base+0x638))
#define  CPMAC_RX6_HDP(base)                  (*pCPMAC_RX6_HDP(base))
#define pCPMAC_RX7_HDP(base)                  ((MEM_PTR)(base+0x63C))
#define  CPMAC_RX7_HDP(base)                  (*pCPMAC_RX7_HDP(base))


#define CPMAC_TX_INT_ACK(base,ch)             (*(MEM_PTR)(base+0x640+(4*ch)))

#define pCPMAC_TX0_INT_ACK(base)              ((MEM_PTR)(base+0x640))
#define  CPMAC_TX0_INT_ACK(base)              (*pCPMAC_TX0_INT_ACK(base))
#define pCPMAC_TX1_INT_ACK(base)              ((MEM_PTR)(base+0x644))
#define  CPMAC_TX1_INT_ACK(base)              (*pCPMAC_TX1_INT_ACK(base))
#define pCPMAC_TX2_INT_ACK(base)              ((MEM_PTR)(base+0x648))
#define  CPMAC_TX2_INT_ACK(base)              (*pCPMAC_TX2_INT_ACK(base))
#define pCPMAC_TX3_INT_ACK(base)              ((MEM_PTR)(base+0x64C))
#define  CPMAC_TX3_INT_ACK(base)              (*pCPMAC_TX3_INT_ACK(base))
#define pCPMAC_TX4_INT_ACK(base)              ((MEM_PTR)(base+0x650))
#define  CPMAC_TX4_INT_ACK(base)              (*pCPMAC_TX4_INT_ACK(base))
#define pCPMAC_TX5_INT_ACK(base)              ((MEM_PTR)(base+0x654))
#define  CPMAC_TX5_INT_ACK(base)              (*pCPMAC_TX5_INT_ACK(base))
#define pCPMAC_TX6_INT_ACK(base)              ((MEM_PTR)(base+0x658))
#define  CPMAC_TX6_INT_ACK(base)              (*pCPMAC_TX6_INT_ACK(base))
#define pCPMAC_TX7_INT_ACK(base)              ((MEM_PTR)(base+0x65C))
#define  CPMAC_TX7_INT_ACK(base)              (*pCPMAC_TX7_INT_ACK(base))
#define CPMAC_RX_INT_ACK(base,ch)             (*(MEM_PTR)(base+0x660+(4*ch)))
         
#define pCPMAC_RX0_INT_ACK(base)              ((MEM_PTR)(base+0x660))
#define  CPMAC_RX0_INT_ACK(base)              (*pCPMAC_RX0_INT_ACK(base))
#define pCPMAC_RX1_INT_ACK(base)              ((MEM_PTR)(base+0x664))
#define  CPMAC_RX1_INT_ACK(base)              (*pCPMAC_RX1_INT_ACK(base))
#define pCPMAC_RX2_INT_ACK(base)              ((MEM_PTR)(base+0x668))
#define  CPMAC_RX2_INT_ACK(base)              (*pCPMAC_RX2_INT_ACK(base))
#define pCPMAC_RX3_INT_ACK(base)              ((MEM_PTR)(base+0x66C))
#define  CPMAC_RX3_INT_ACK(base)              (*pCPMAC_RX3_INT_ACK(base))
#define pCPMAC_RX4_INT_ACK(base)              ((MEM_PTR)(base+0x670))
#define  CPMAC_RX4_INT_ACK(base)              (*pCPMAC_RX4_INT_ACK(base))
#define pCPMAC_RX5_INT_ACK(base)              ((MEM_PTR)(base+0x674))
#define  CPMAC_RX5_INT_ACK(base)              (*pCPMAC_RX5_INT_ACK(base))
#define pCPMAC_RX6_INT_ACK(base)              ((MEM_PTR)(base+0x678))
#define  CPMAC_RX6_INT_ACK(base)              (*pCPMAC_RX6_INT_ACK(base))
#define pCPMAC_RX7_INT_ACK(base)              ((MEM_PTR)(base+0x67C))
#define  CPMAC_RX7_INT_ACK(base)              (*pCPMAC_RX7_INT_ACK(base))

/****************************************************************************/
/*                                                                          */
/*         R E G I S T E R  B I T  D E F I N I T I O N S                    */
/*                                                                          */
/****************************************************************************/

/* TX_CONTROL */

#define TX_EN               (1 << 0)

/* RX_CONTROL */

#define RX_EN               (1 << 0)

/* RX_MBP_ENABLE */

#define RX_PASS_CRC         (1 << 30)
#define RX_QOS_EN           (1 << 29)
#define RX_NO_CHAIN         (1 << 28)

#define RX_CMF_EN           (1 << 24)
#define RX_CSF_EN           (1 << 23)
#define RX_CEF_EN           (1 << 22)
#define RX_CAF_EN           (1 << 21)

#define RX_PROM_CH(n)       (n << 16)
#define RX_PROM_CH_MASK     RX_PROM_CH(7)
#define RX_PROM_CH_7        RX_PROM_CH(7)
#define RX_PROM_CH_6        RX_PROM_CH(6)
#define RX_PROM_CH_5        RX_PROM_CH(5)
#define RX_PROM_CH_4        RX_PROM_CH(4)
#define RX_PROM_CH_3        RX_PROM_CH(3)
#define RX_PROM_CH_2        RX_PROM_CH(2)
#define RX_PROM_CH_1        RX_PROM_CH(1)
#define RX_PROM_CH_0        RX_PROM_CH(0)

#define RX_BROAD_EN         (1 << 13)

#define RX_BROAD_CH(n)       (n <<  8)
#define RX_BROAD_CH_MASK     RX_BROAD_CH(7)
#define RX_BROAD_CH_7        RX_BROAD_CH(7)
#define RX_BROAD_CH_6        RX_BROAD_CH(6)
#define RX_BROAD_CH_5        RX_BROAD_CH(5)
#define RX_BROAD_CH_4        RX_BROAD_CH(4)
#define RX_BROAD_CH_3        RX_BROAD_CH(3)
#define RX_BROAD_CH_2        RX_BROAD_CH(2)
#define RX_BROAD_CH_1        RX_BROAD_CH(1)
#define RX_BROAD_CH_0        RX_BROAD_CH(0)

#define RX_MULT_EN          (1 <<  5)

#define RX_MULT_CH(n)       (n << 0)
#define RX_MULT_CH_MASK     RX_MULT_CH(7)
#define RX_MULT_CH_7        RX_MULT_CH(7)
#define RX_MULT_CH_6        RX_MULT_CH(6)
#define RX_MULT_CH_5        RX_MULT_CH(5)
#define RX_MULT_CH_4        RX_MULT_CH(4)
#define RX_MULT_CH_3        RX_MULT_CH(3)
#define RX_MULT_CH_2        RX_MULT_CH(2)
#define RX_MULT_CH_1        RX_MULT_CH(1)
#define RX_MULT_CH_0        RX_MULT_CH(0)



/* RX_UNICAST_SET */

#define RX_CH7_EN        (1 <<  7)
#define RX_CH6_EN        (1 <<  6)
#define RX_CH5_EN        (1 <<  5)
#define RX_CH4_EN        (1 <<  4)
#define RX_CH3_EN        (1 <<  3)
#define RX_CH2_EN        (1 <<  2)
#define RX_CH1_EN        (1 <<  1)
#define RX_CH0_EN        (1 <<  0)



/*  MAC control */
#define TX_PTYPE         (1 << 9)
#define TX_PACE          (1 << 6)
#define MII_EN           (1 << 5)
#define TX_FLOW_EN       (1 << 4)
#define RX_FLOW_EN       (1 << 3)
#define MTEST            (1 << 2)
#define CTRL_LOOPBACK    (1 << 1)
#define FULLDUPLEX       (1 << 0)


/* IntVec definitions  */
#define MAC_IN_VECTOR_STATUS_INT   (1 << 19)
#define MAC_IN_VECTOR_HOST_INT     (1 << 18)
#define MAC_IN_VECTOR_RX_INT_OR    (1 << 17)
#define MAC_IN_VECTOR_TX_INT_OR    (1 << 16)
#define MAC_IN_VECTOR_RX_INT_VEC   (7 << 8)
#define MAC_IN_VECTOR_TX_INT_VEC   (7)  


/*  MacStatus */

#define TX_HOST_ERR_CODE         (0xF << 20)
#define TX_ERR_CH                (0x7 << 16)
#define RX_HOST_ERR_CODE         (0xF << 12)
#define RX_ERR_CH                (0x7 <<  8)
#define RX_QOS_ACT               (1 << 2)
#define RX_FLOW_ACT              (1 << 1)
#define TX_FLOW_ACT              (1 << 0)
#endif _INC_CPMAC_REG
