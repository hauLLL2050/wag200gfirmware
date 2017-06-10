/*
 * Automatically generated by make menuconfig: don't edit
 */
#define AUTOCONF_INCLUDED
#define CONFIG_MIPS 1

/*
 * Code maturity level options
 */
#define CONFIG_EXPERIMENTAL 1

/*
 * Machine selection
 */
#undef  CONFIG_ACER_PICA_61
#undef  CONFIG_ALGOR_P4032
#undef  CONFIG_BAGET_MIPS
#undef  CONFIG_COBALT_MICRO_SERVER
#undef  CONFIG_DECSTATION
#undef  CONFIG_DDB5074
#undef  CONFIG_NEC_EAGLE
#undef  CONFIG_MIPS_EV96100
#undef  CONFIG_MIPS_EV64120
#undef  CONFIG_MIPS_ATLAS
#undef  CONFIG_MIPS_MALTA
#define CONFIG_MIPS_TI 1
#undef  CONFIG_MIPS_PUMAS
#undef  CONFIG_MIPS_TITAN
#undef  CONFIG_MIPS_APEX
#define CONFIG_MIPS_SANGAM 1
#undef  CONFIG_MIPS_SEAD2
#undef  CONFIG_MIPS_AR7DB
#undef  CONFIG_MIPS_AR7RD
#define CONFIG_MIPS_AR7WRD 1
#undef  CONFIG_MIPS_AR7VWI
#undef  CONFIG_MIPS_AR7VW
#undef  CONFIG_MIPS_AR7WI
#undef  CONFIG_MIPS_AR7V
#undef  CONFIG_MIPS_AVALANCHE_CUSTOM
#define CONFIG_CPU_FREQUENCY_AVALANCHE (125)
#define CONFIG_MEMORY_START 0x14000000
#define CONFIG_MIPS_AVALANCHE_SOC 1
#undef  CONFIG_MIPS_AVALANCHE_PSPBOOT
#define CONFIG_MIPS_AVALANCHE_ADAM2 1
#undef  CONFIG_MIPS_AVALANCHE_ADAM2_JMP_TBL
#undef  CONFIG_NINO
#undef  CONFIG_MIPS_LXPB20K
#undef  CONFIG_SIBYTE_SB1250
#undef  CONFIG_PS2
#undef  CONFIG_CASIO_BE300
#undef  CONFIG_VADEM_CLIO_1000
#undef  CONFIG_NEC_MOBILEPRO_780
#undef  CONFIG_IDT_79S334
#undef  CONFIG_IDT_79EB355
#undef  CONFIG_MIPS_MAGNUM_4000
#undef  CONFIG_MOMENCO_OCELOT
#undef  CONFIG_DDB5476
#undef  CONFIG_DDB5477
#undef  CONFIG_NEC_OSPREY
#undef  CONFIG_OLIVETTI_M700
#undef  CONFIG_SGI_IP22
#undef  CONFIG_SNI_RM200_PCI
#undef  CONFIG_MIPS_ITE8172
#undef  CONFIG_MIPS_IVR
#undef  CONFIG_MIPS_PB1000
#undef  CONFIG_MIPS_PB1500
#undef  CONFIG_TOSHIBA_JMR3927
#undef  CONFIG_HP_LASERJET
#define CONFIG_RWSEM_GENERIC_SPINLOCK 1
#undef  CONFIG_RWSEM_XCHGADD_ALGORITHM
#define CONFIG_GENERIC_ISA_DMA 1
#undef  CONFIG_MCA
#undef  CONFIG_SBUS
#define CONFIG_CPU_LITTLE_ENDIAN 1
#define CONFIG_MIPS_AVALANCHE_PAGING 1
#define CONFIG_SWAP_IO_SPACE 1
#define CONFIG_NONCOHERENT_IO 1
#define CONFIG_TI_FILESYSTEM 1
#define CONFIG_MIPS_AVALANCHE_INTC 1
#define CONFIG_AVALANCHE_INTC_PACING 1
#define CONFIG_AVALANCHE_INTC_TYPE 1
#define CONFIG_MIPS_AVALANCHE_DMA 1
#define CONFIG_MIPS_AVALANCHE_TIMER16 1
#define CONFIG_MIPS_AVALANCHE_WDTIMER 1
#define CONFIG_AVALANCHE_GENERIC_GPIO 1
#define CONFIG_MIPS_AVALANCHE_TICFG 1
#undef  CONFIG_PCI
#define CONFIG_TI_CUSTOM_SYS_CALLS 1
#define CONFIG_NR_TI_CUSTOM_SYSCALLS (16)
#define CONFIG_AVALANCHE_SERIAL 1
#undef  CONFIG_AVALANCHE_UART1_TTYS0
#undef  CONFIG_ISA
#undef  CONFIG_EISA
#undef  CONFIG_PCI
#undef  CONFIG_I8259

/*
 * Loadable module support
 */
#define CONFIG_MODULES 1
#undef  CONFIG_MODVERSIONS
#define CONFIG_KMOD 1

/*
 * CPU selection
 */
#undef  CONFIG_CPU_R3000
#undef  CONFIG_CPU_LX45XXX
#undef  CONFIG_CPU_TX39XX
#undef  CONFIG_CPU_R6000
#undef  CONFIG_CPU_VR41XX
#undef  CONFIG_CPU_R4300
#undef  CONFIG_CPU_R4X00
#undef  CONFIG_CPU_TX49XX
#undef  CONFIG_CPU_R5000
#undef  CONFIG_CPU_R5432
#undef  CONFIG_CPU_R5900
#undef  CONFIG_CPU_RM7000
#undef  CONFIG_CPU_NEVADA
#undef  CONFIG_CPU_R10000
#undef  CONFIG_CPU_SB1
#define CONFIG_CPU_MIPS32 1
#undef  CONFIG_CPU_MIPS64
#undef  CONFIG_CPU_RC32300
#undef  CONFIG_CPU_ADVANCED
#define CONFIG_CPU_HAS_LLSC 1
#undef  CONFIG_CPU_HAS_LLDSCD
#undef  CONFIG_CPU_HAS_WB
#undef  CONFIG_EMBEDDED_OOM_KILLER
#undef  CONFIG_RTSCHED

/*
 * General setup
 */
#define CONFIG_CPU_LITTLE_ENDIAN 1
#undef  CONFIG_HIGH_RES_TIMERS
#define CONFIG_HIGH_RES_RESOLUTION (10000)
#undef  CONFIG_NEW_TIMERLIST
#define CONFIG_MAX_POSIX_TIMERS (3000)
#define CONFIG_KCORE_ELF 1
#define CONFIG_ELF_KERNEL 1
#undef  CONFIG_BINFMT_AOUT
#define CONFIG_BINFMT_ELF 1
#undef  CONFIG_MULTITHREADED_CORES
#undef  CONFIG_BINFMT_MISC
#define CONFIG_NET 1
#undef  CONFIG_HOTPLUG
#undef  CONFIG_PCMCIA
#undef  CONFIG_HOTPLUG_PCI
#define CONFIG_SYSVIPC 1
#undef  CONFIG_BSD_PROCESS_ACCT
#define CONFIG_SYSCTL 1
#undef  CONFIG_ILATENCY
#undef  CONFIG_PREEMPT
#define CONFIG_KERNEL_COMPRESS_7ZIP 1
#undef  CONFIG_PSP_TRACE

/*
 * Memory Technology Devices (MTD)
 */
#define CONFIG_MTD 1
#undef  CONFIG_MTD_DEBUG
#define CONFIG_MTD_PARTITIONS 1
#undef  CONFIG_MTD_CONCAT
#undef  CONFIG_MTD_REDBOOT_PARTS
#undef  CONFIG_MTD_CMDLINE_PARTS
#undef  CONFIG_MTD_CHAR
#define CONFIG_MTD_BLOCK 1
#undef  CONFIG_FTL
#undef  CONFIG_NFTL
#undef  CONFIG_INFTL

/*
 * RAM/ROM/Flash chip drivers
 */
#define CONFIG_MTD_CFI 1
#undef  CONFIG_MTD_JEDECPROBE
#define CONFIG_MTD_GEN_PROBE 1
#define CONFIG_MTD_CFI_ADV_OPTIONS 1
#define CONFIG_MTD_CFI_NOSWAP 1
#undef  CONFIG_MTD_CFI_BE_BYTE_SWAP
#undef  CONFIG_MTD_CFI_LE_BYTE_SWAP
#define CONFIG_MTD_CFI_GEOMETRY 1
#undef  CONFIG_MTD_MAP_BANK_WIDTH_1
#define CONFIG_MTD_MAP_BANK_WIDTH_2 1
#undef  CONFIG_MTD_MAP_BANK_WIDTH_4
#undef  CONFIG_MTD_MAP_BANK_WIDTH_8
#undef  CONFIG_MTD_MAP_BANK_WIDTH_16
#undef  CONFIG_MTD_MAP_BANK_WIDTH_32
#define CONFIG_MTD_CFI_I1 1
#undef  CONFIG_MTD_CFI_I2
#undef  CONFIG_MTD_CFI_I4
#undef  CONFIG_MTD_CFI_I8
#define CONFIG_MTD_CFI_INTELEXT 1
#define CONFIG_MTD_CFI_AMDSTD 1
#undef  CONFIG_MTD_CFI_STAA
#define CONFIG_MTD_CFI_UTIL 1
#undef  CONFIG_MTD_RAM
#undef  CONFIG_MTD_ROM
#undef  CONFIG_MTD_ABSENT
#undef  CONFIG_MTD_OBSOLETE_CHIPS
#undef  CONFIG_MTD_AMDSTD
#undef  CONFIG_MTD_SHARP
#undef  CONFIG_MTD_JEDEC

/*
 * Mapping drivers for chip access
 */
#define CONFIG_MTD_COMPLEX_MAPPINGS 1
#undef  CONFIG_MTD_PHYSMAP
#define CONFIG_MTD_AVALANCHE 1
#undef  CONFIG_MTD_AVALANCHE_DEFAULTS
#define CONFIG_MTD_AVALANCHE_START 0x10000000
#define CONFIG_MTD_AVALANCHE_LEN 0x400000
#define CONFIG_MTD_AVALANCHE_BUSWIDTH (2)
#undef  CONFIG_MTD_ALCHEMY
#undef  CONFIG_MTD_CSTM_MIPS_IXX
#undef  CONFIG_MTD_OCELOT
#undef  CONFIG_MTD_LASAT
#undef  CONFIG_MTD_PCI
#undef  CONFIG_MTD_PCMCIA

/*
 * Self-contained MTD device drivers
 */
#undef  CONFIG_MTD_PMC551
#undef  CONFIG_MTD_SLRAM
#undef  CONFIG_MTD_MTDRAM
#undef  CONFIG_MTD_BLKMTD
#undef  CONFIG_MTD_DOC2000
#undef  CONFIG_MTD_DOC2001
#undef  CONFIG_MTD_DOC2001PLUS
#undef  CONFIG_MTD_DOCPROBE
#undef  CONFIG_MTD_DOCECC

/*
 * NAND Flash Device Drivers
 */
#undef  CONFIG_MTD_NAND
#undef  CONFIG_MTD_NAND_DISKONCHIP

/*
 * Parallel port support
 */
#undef  CONFIG_PARPORT

/*
 * Block devices
 */
#undef  CONFIG_BLK_DEV_FD
#undef  CONFIG_BLK_DEV_XD
#undef  CONFIG_PARIDE
#undef  CONFIG_BLK_CPQ_DA
#undef  CONFIG_BLK_CPQ_CISS_DA
#undef  CONFIG_BLK_DEV_DAC960
#undef  CONFIG_BLK_DEV_LOOP
#undef  CONFIG_BLK_DEV_NBD
#undef  CONFIG_BLK_DEV_RAM
#undef  CONFIG_BLK_DEV_INITRD
#undef  CONFIG_EMBEDDED_RAMDISK

/*
 * Multi-device support (RAID and LVM)
 */
#undef  CONFIG_MD
#undef  CONFIG_BLK_DEV_MD
#undef  CONFIG_MD_LINEAR
#undef  CONFIG_MD_RAID0
#undef  CONFIG_MD_RAID1
#undef  CONFIG_MD_RAID5
#undef  CONFIG_MD_MULTIPATH
#undef  CONFIG_BLK_DEV_LVM

/*
 * Networking options
 */
#define CONFIG_PACKET 1
#define CONFIG_PACKET_MMAP 1
#undef  CONFIG_NETLINK_DEV
#define CONFIG_NETFILTER 1
#undef  CONFIG_NETFILTER_DEBUG
#define CONFIG_FILTER 1
#define CONFIG_UNIX 1
#define CONFIG_INET 1
#define CONFIG_IP_MULTICAST 1
#undef  CONFIG_IP_ADVANCED_ROUTER
#undef  CONFIG_IP_PNP
#undef  CONFIG_NET_IPIP
#undef  CONFIG_NET_IPGRE
#define CONFIG_IP_MROUTE 1
#undef  CONFIG_IP_PIMSM_V1
#undef  CONFIG_IP_PIMSM_V2
#undef  CONFIG_ARPD
#undef  CONFIG_INET_ECN
#undef  CONFIG_SYN_COOKIES

/*
 *   IP: Netfilter Configuration
 */
#define CONFIG_IP_NF_CONNTRACK 1
#define CONFIG_IP_NF_FTP 1
#undef  CONFIG_IP_NF_TALK
#undef  CONFIG_IP_NF_H323
#define CONFIG_IP_NF_IRC 1
#define CONFIG_IP_NF_RTSP 1
#undef  CONFIG_IP_NF_DTX8
#undef  CONFIG_IP_NF_PT
#define CONFIG_IP_NF_TFTP 1
#undef  CONFIG_IP_NF_IPSEC
#undef  CONFIG_IP_NF_PPTP
#undef  CONFIG_IP_NF_QUEUE
#define CONFIG_IP_NF_IPTABLES 1
#define CONFIG_IP_NF_MATCH_LIMIT 1
#define CONFIG_IP_NF_MATCH_DSTLIMIT 1
#define CONFIG_IP_NF_MATCH_IPRANGE 1
#define CONFIG_IP_NF_MATCH_MAC 1
#undef  CONFIG_IP_NF_MATCH_PKTTYPE
#define CONFIG_IP_NF_MATCH_MARK 1
#define CONFIG_IP_NF_MATCH_MULTIPORT 1
#define CONFIG_IP_NF_MATCH_TOS 1
#define CONFIG_IP_NF_MATCH_RECENT 1
#undef  CONFIG_IP_NF_MATCH_ECN
#undef  CONFIG_IP_NF_MATCH_DSCP
#define CONFIG_IP_NF_MATCH_PSD 1
#define CONFIG_IP_NF_MATCH_LENGTH 1
#undef  CONFIG_IP_NF_MATCH_TTL
#undef  CONFIG_IP_NF_MATCH_TCPMSS
#undef  CONFIG_IP_NF_MATCH_HELPER
#undef  CONFIG_IP_NF_MATCH_UNCLEAN
#define CONFIG_IP_NF_MATCH_STRING 1
#define CONFIG_IP_NF_MATCH_STRINGGET 1
#define CONFIG_IP_NF_MATCH_STRINGHEAD 1
#define CONFIG_IP_NF_MATCH_STRINGHOST 1
#define CONFIG_IP_NF_MATCH_RANDOM 1
#define CONFIG_IP_NF_MATCH_STATE 1
#undef  CONFIG_IP_NF_MATCH_CONNLIMIT
#undef  CONFIG_IP_NF_MATCH_CONNTRACK
#undef  CONFIG_IP_NF_MATCH_UNCLEAN
#define CONFIG_IP_NF_MATCH_STRING 1
#undef  CONFIG_IP_NF_MATCH_OWNER
#undef  CONFIG_IP_NF_MATCH_LAYER7
#undef  CONFIG_IP_NF_MATCH_LAYER7_DEBUG
#define CONFIG_IP_NF_MATCH_LAYER7_MAXDATALEN (2048)
#define CONFIG_IP_NF_FILTER 1
#define CONFIG_IP_NF_TARGET_REJECT 1
#undef  CONFIG_IP_NF_TARGET_NETLINK
#undef  CONFIG_IP_NF_TARGET_IPV4OPTSSTRIP
#undef  CONFIG_IP_NF_TARGET_MIRROR
#define CONFIG_IP_NF_NAT 1
#define CONFIG_IP_NF_NAT_NEEDED 1
#define CONFIG_IP_NF_TARGET_MASQUERADE 1
#define CONFIG_IP_NF_TARGET_REDIRECT 1
#undef  CONFIG_IP_NF_TARGET_SAME
#undef  CONFIG_IP_NF_TARGET_NETMAP
#undef  CONFIG_IP_NF_NAT_LOCAL
#define CONFIG_IP_NF_NAT_SNMP_BASIC 1
#define CONFIG_IP_NF_NAT_IRC 1
#define CONFIG_IP_NF_NAT_FTP 1
#define CONFIG_IP_NF_NAT_TFTP 1
#define CONFIG_IP_NF_NAT_RTSP 1
#define CONFIG_IP_NF_MANGLE 1
#define CONFIG_IP_NF_TARGET_TOS 1
#undef  CONFIG_IP_NF_TARGET_ECN
#undef  CONFIG_IP_NF_TARGET_DSCP
#define CONFIG_IP_NF_TARGET_FTOS 1
#define CONFIG_IP_NF_TARGET_MARK 1
#define CONFIG_IP_NF_TARGET_LOG 1
#undef  CONFIG_IP_NF_TARGET_TTL
#define CONFIG_IP_NF_TARGET_TCPMSS 1
#define CONFIG_IP_NF_TARGET_TRIGGER 1
#undef  CONFIG_IPV6
#undef  CONFIG_KHTTPD
#define CONFIG_ATM 1
#define CONFIG_ATM_CLIP 1
#undef  CONFIG_ATM_CLIP_NO_ICMP
#undef  CONFIG_ATM_LANE
#define CONFIG_ATM_BR2684 1
#undef  CONFIG_ATM_BR2684_IPFILTER
#undef  CONFIG_VLAN_8021Q
#undef  CONFIG_IPX
#undef  CONFIG_ATALK
#undef  CONFIG_DECNET
#define CONFIG_BRIDGE 1
#undef  CONFIG_MIPS_AVALANCHE_FAST_BRIDGE
#undef  CONFIG_X25
#undef  CONFIG_LAPB
#undef  CONFIG_LLC
#undef  CONFIG_NET_DIVERT
#undef  CONFIG_ECONET
#undef  CONFIG_WAN_ROUTER
#undef  CONFIG_NET_FASTROUTE
#undef  CONFIG_NET_HW_FLOWCONTROL

/*
 * QoS and/or fair queueing
 */
#define CONFIG_NET_SCHED 1
#define CONFIG_NET_SCH_CBQ 1
#define CONFIG_NET_SCH_HTB 1
#undef  CONFIG_NET_SCH_CSZ
#undef  CONFIG_NET_SCH_ATM
#define CONFIG_NET_SCH_PRIO 1
#define CONFIG_NET_SCH_PRIOWRR 1
#undef  CONFIG_NET_SCH_RED
#define CONFIG_NET_SCH_SFQ 1
#undef  CONFIG_NET_SCH_TEQL
#undef  CONFIG_NET_SCH_TBF
#undef  CONFIG_NET_SCH_GRED
#define CONFIG_NET_SCH_DSMARK 1
#undef  CONFIG_NET_SCH_INGRESS
#define CONFIG_NET_QOS 1
#define CONFIG_NET_ESTIMATOR 1
#define CONFIG_NET_CLS 1
#define CONFIG_NET_CLS_TCINDEX 1
#undef  CONFIG_NET_CLS_ROUTE4
#define CONFIG_NET_CLS_FW 1
#define CONFIG_NET_CLS_U32 1
#undef  CONFIG_NET_CLS_RSVP
#undef  CONFIG_NET_CLS_RSVP6
#define CONFIG_NET_CLS_POLICE 1
#undef  CONFIG_IPSEC
#define CONFIG_IPSEC_MODULE 1
#define CONFIG_IPSEC_IPIP 1
#undef  CONFIG_IPSEC_AH
#define CONFIG_IPSEC_AUTH_HMAC_MD5 1
#define CONFIG_IPSEC_AUTH_HMAC_SHA1 1
#define CONFIG_IPSEC_ESP 1
#define CONFIG_IPSEC_ENC_3DES 1
#define CONFIG_IPSEC_ALG 1
#undef  CONFIG_IPSEC_ALG_MD5
#undef  CONFIG_IPSEC_ALG_SHA1
#undef  CONFIG_IPSEC_ALG_SHA2
#undef  CONFIG_IPSEC_ALG_3DES
#undef  CONFIG_IPSEC_ALG_AES
#undef  CONFIG_IPSEC_ALG_BLOWFISH
#undef  CONFIG_IPSEC_ALG_TWOFISH
#undef  CONFIG_IPSEC_ALG_SERPENT
#undef  CONFIG_IPSEC_ALG_CAST
#undef  CONFIG_IPSEC_ALG_NULL
#undef  CONFIG_IPSEC_ALG_CRYPTOAPI
#define CONFIG_IPSEC_ALG_1DES 1
#define CONFIG_IPSEC_IPCOMP 1
#undef  CONFIG_IPSEC_DEBUG
#undef  CONFIG_IPSEC_NAT_TRAVERSAL

/*
 * Telephony Support
 */
#undef  CONFIG_PHONE
#undef  CONFIG_PHONE_IXJ
#undef  CONFIG_PHONE_IXJ_PCMCIA

/*
 * ATA/IDE/MFM/RLL support
 */
#undef  CONFIG_IDE
#undef  CONFIG_BLK_DEV_IDE_MODES
#undef  CONFIG_BLK_DEV_HD

/*
 * SCSI support
 */
#undef  CONFIG_SCSI

/*
 * I2O device support
 */
#undef  CONFIG_I2O
#undef  CONFIG_I2O_BLOCK
#undef  CONFIG_I2O_LAN
#undef  CONFIG_I2O_SCSI
#undef  CONFIG_I2O_PROC

/*
 * Network device support
 */
#define CONFIG_NETDEVICES 1

/*
 * ARCnet devices
 */
#undef  CONFIG_ARCNET
#undef  CONFIG_DUMMY
#undef  CONFIG_BONDING
#undef  CONFIG_EQUALIZER
#undef  CONFIG_TUN
#undef  CONFIG_ETHERTAP

/*
 * Ethernet (10 or 100Mbit)
 */
#define CONFIG_NET_ETHERNET 1
#define CONFIG_MIPS_AVALANCHE_CPMAC 1
#define CONFIG_MIPS_CPMAC_INIT_BUF_MALLOC 1
#define CONFIG_MIPS_CPMAC_PORTS (1)
#undef  CONFIG_AVALANCHE_SANGAM_CPMAC_AUTO
#define CONFIG_AVALANCHE_HIGH_CPMAC 1
#undef  CONFIG_AVALANCHE_LOW_CPMAC
#define CONFIG_MIPS_EXTERNAL_SWITCH 1
#define CONFIG_MIPS_AVALANCHE_MARVELL_6063 1
#undef  CONFIG_MIPS_AVALANCHE_USB
#undef  CONFIG_MIPS_AVALANCHE_USB_SLAVE20
#undef  CONFIG_SUNLANCE
#undef  CONFIG_SUNBMAC
#undef  CONFIG_SUNQE
#undef  CONFIG_SUNLANCE
#undef  CONFIG_SUNGEM
#undef  CONFIG_NET_VENDOR_3COM
#undef  CONFIG_LANCE
#undef  CONFIG_NET_VENDOR_SMC
#undef  CONFIG_NET_VENDOR_RACAL
#undef  CONFIG_NET_ISA
#undef  CONFIG_NET_PCI
#undef  CONFIG_NET_POCKET
#undef  CONFIG_HHNET

/*
 * Ethernet (1000 Mbit)
 */
#undef  CONFIG_ACENIC
#undef  CONFIG_DL2K
#undef  CONFIG_MYRI_SBUS
#undef  CONFIG_NS83820
#undef  CONFIG_HAMACHI
#undef  CONFIG_YELLOWFIN
#undef  CONFIG_SK98LIN
#undef  CONFIG_FDDI
#undef  CONFIG_HIPPI
#undef  CONFIG_PLIP
#define CONFIG_PPP 1
#undef  CONFIG_PPP_MULTILINK
#undef  CONFIG_PPP_FILTER
#undef  CONFIG_PPP_ASYNC
#undef  CONFIG_PPP_SYNC_TTY
#define CONFIG_PPP_DEFLATE 1
#define CONFIG_PPP_BSDCOMP 1
#undef  CONFIG_PPP_MPPE_MPPC
#define CONFIG_PPPOE 1
#define CONFIG_PPPOATM 1
#undef  CONFIG_SLIP

/*
 * Wireless LAN (non-hamradio)
 */
#define CONFIG_NET_RADIO 1
#undef  CONFIG_STRIP
#undef  CONFIG_WAVELAN
#undef  CONFIG_ARLAN
#undef  CONFIG_AIRONET4500
#undef  CONFIG_AIRONET4500_NONCS
#undef  CONFIG_AIRONET4500_PROC
#undef  CONFIG_HERMES
#undef  CONFIG_NET_WIRELESS

/*
 * Token Ring devices
 */
#undef  CONFIG_TR
#undef  CONFIG_NET_FC
#undef  CONFIG_RCPCI
#undef  CONFIG_SHAPER

/*
 * Wan interfaces
 */
#undef  CONFIG_WAN

/*
 * ATM drivers
 */
#undef  CONFIG_ATM_TCP
#undef  CONFIG_MIPS_SANGAM_ATM
#define CONFIG_MIPS_SANGAM_ATM_MODULE 1

/*
 * Amateur Radio support
 */
#undef  CONFIG_HAMRADIO

/*
 * IrDA (infrared) support
 */
#undef  CONFIG_IRDA

/*
 * ISDN subsystem
 */
#undef  CONFIG_ISDN

/*
 * Old CD-ROM drivers (not SCSI, not IDE)
 */
#undef  CONFIG_CD_NO_IDESCSI

/*
 * Character devices
 */
#undef  CONFIG_VT
#define CONFIG_SERIAL 1
#define CONFIG_SERIAL_CONSOLE 1
#define CONFIG_MIPS_AVALANCHE_LED 1
#undef  CONFIG_SERIAL_NONSTANDARD
#define CONFIG_UNIX98_PTYS 1
#define CONFIG_UNIX98_PTY_COUNT (32)
#define CONFIG_MIPS_AVALANCHE_VLYNQ 1
#undef  CONFIG_AVALANCHE_VLYNQ_CLK_LOCAL
#define CONFIG_MIPS_AVALANCHE_VLYNQ_PORTS (2)
#define CONFIG_AVALANCHE_VLYNQ_POLARITY_LOW 1
#undef  CONFIG_MIPS_V2USB_EVM

/*
 * I2C support
 */
#undef  CONFIG_I2C

/*
 * Mice
 */
#undef  CONFIG_BUSMOUSE
#undef  CONFIG_MOUSE

/*
 * Joysticks
 */
#undef  CONFIG_INPUT_GAMEPORT
#undef  CONFIG_QIC02_TAPE

/*
 * Watchdog Cards
 */
#define CONFIG_WATCHDOG 1
#undef  CONFIG_WATCHDOG_NOWAYOUT
#undef  CONFIG_SOFT_WATCHDOG
#define CONFIG_SOFT_WATCHDOG_MODULE 1
#undef  CONFIG_WDT
#undef  CONFIG_WDTPCI
#undef  CONFIG_PCWATCHDOG
#undef  CONFIG_ACQUIRE_WDT
#undef  CONFIG_ADVANTECH_WDT
#undef  CONFIG_EUROTECH_WDT
#undef  CONFIG_IB700_WDT
#undef  CONFIG_I810_TCO
#undef  CONFIG_MIXCOMWD
#undef  CONFIG_60XX_WDT
#undef  CONFIG_W83877F_WDT
#undef  CONFIG_MACHZ_WDT
#undef  CONFIG_VR41XX_WDT
#undef  CONFIG_INTEL_RNG
#undef  CONFIG_NVRAM
#undef  CONFIG_RTC
#undef  CONFIG_DTLK
#undef  CONFIG_R3964
#undef  CONFIG_APPLICOM

/*
 * Ftape, the floppy tape device driver
 */
#undef  CONFIG_FTAPE
#undef  CONFIG_AGP
#undef  CONFIG_DRM

/*
 * Multimedia devices
 */
#undef  CONFIG_VIDEO_DEV

/*
 * File systems
 */
#undef  CONFIG_QUOTA
#undef  CONFIG_AUTOFS_FS
#undef  CONFIG_AUTOFS4_FS
#undef  CONFIG_REISERFS_FS
#undef  CONFIG_REISERFS_CHECK
#undef  CONFIG_REISERFS_PROC_INFO
#undef  CONFIG_ADFS_FS
#undef  CONFIG_ADFS_FS_RW
#undef  CONFIG_AFFS_FS
#undef  CONFIG_HFS_FS
#undef  CONFIG_BFS_FS
#undef  CONFIG_EXT3_FS
#undef  CONFIG_JBD
#undef  CONFIG_JBD_DEBUG
#undef  CONFIG_FAT_FS
#undef  CONFIG_MSDOS_FS
#undef  CONFIG_UMSDOS_FS
#undef  CONFIG_VFAT_FS
#undef  CONFIG_EFS_FS
#undef  CONFIG_JFFS_FS
#undef  CONFIG_JFFS2_FS
#undef  CONFIG_CRAMFS
#define CONFIG_SQUASHFS 1
#define CONFIG_LZMA_FS_INFLATE 1
#undef  CONFIG_TMPFS
#define CONFIG_RAMFS 1
#undef  CONFIG_ISO9660_FS
#undef  CONFIG_JOLIET
#undef  CONFIG_ZISOFS
#define CONFIG_MINIX_FS 1
#undef  CONFIG_MINI_FO
#undef  CONFIG_VXFS_FS
#undef  CONFIG_NTFS_FS
#undef  CONFIG_NTFS_RW
#undef  CONFIG_HPFS_FS
#define CONFIG_PROC_FS 1
#define CONFIG_DEVFS_FS 1
#define CONFIG_DEVFS_MOUNT 1
#undef  CONFIG_DEVFS_DEBUG
#undef  CONFIG_DEVPTS_FS
#undef  CONFIG_QNX4FS_FS
#undef  CONFIG_QNX4FS_RW
#undef  CONFIG_ROMFS_FS
#undef  CONFIG_EXT2_FS
#undef  CONFIG_SYSV_FS
#undef  CONFIG_UDF_FS
#undef  CONFIG_UDF_RW
#undef  CONFIG_UFS_FS
#undef  CONFIG_UFS_FS_WRITE

/*
 * Network File Systems
 */
#undef  CONFIG_CODA_FS
#undef  CONFIG_INTERMEZZO_FS
#undef  CONFIG_NFS_FS
#undef  CONFIG_NFS_V3
#undef  CONFIG_ROOT_NFS
#undef  CONFIG_NFSD
#undef  CONFIG_NFSD_V3
#undef  CONFIG_SUNRPC
#undef  CONFIG_LOCKD
#define CONFIG_CIFS 1
#define CONFIG_CIFS_STATS 1
#undef  CONFIG_CIFS_POSIX
#define CONFIG_SMB_FS 1
#undef  CONFIG_SMB_NLS_DEFAULT
#undef  CONFIG_NCP_FS
#undef  CONFIG_NCPFS_PACKET_SIGNING
#undef  CONFIG_NCPFS_IOCTL_LOCKING
#undef  CONFIG_NCPFS_STRONG
#undef  CONFIG_NCPFS_NFS_NS
#undef  CONFIG_NCPFS_OS2_NS
#undef  CONFIG_NCPFS_SMALLDOS
#undef  CONFIG_NCPFS_NLS
#undef  CONFIG_NCPFS_EXTRAS
#undef  CONFIG_ZISOFS_FS
#define CONFIG_ZLIB_FS_INFLATE 1

/*
 * Partition Types
 */
#undef  CONFIG_PARTITION_ADVANCED
#define CONFIG_MSDOS_PARTITION 1
#define CONFIG_SMB_NLS 1
#define CONFIG_NLS 1

/*
 * Native Language Support
 */
#define CONFIG_NLS_DEFAULT "iso8859-1"
#undef  CONFIG_NLS_CODEPAGE_437
#undef  CONFIG_NLS_CODEPAGE_737
#undef  CONFIG_NLS_CODEPAGE_775
#undef  CONFIG_NLS_CODEPAGE_850
#undef  CONFIG_NLS_CODEPAGE_852
#undef  CONFIG_NLS_CODEPAGE_855
#undef  CONFIG_NLS_CODEPAGE_857
#undef  CONFIG_NLS_CODEPAGE_860
#undef  CONFIG_NLS_CODEPAGE_861
#undef  CONFIG_NLS_CODEPAGE_862
#undef  CONFIG_NLS_CODEPAGE_863
#undef  CONFIG_NLS_CODEPAGE_864
#undef  CONFIG_NLS_CODEPAGE_865
#undef  CONFIG_NLS_CODEPAGE_866
#undef  CONFIG_NLS_CODEPAGE_869
#undef  CONFIG_NLS_CODEPAGE_936
#undef  CONFIG_NLS_CODEPAGE_950
#undef  CONFIG_NLS_CODEPAGE_932
#undef  CONFIG_NLS_CODEPAGE_949
#undef  CONFIG_NLS_CODEPAGE_874
#undef  CONFIG_NLS_ISO8859_8
#undef  CONFIG_NLS_CODEPAGE_1251
#undef  CONFIG_NLS_ISO8859_1
#undef  CONFIG_NLS_ISO8859_2
#undef  CONFIG_NLS_ISO8859_3
#undef  CONFIG_NLS_ISO8859_4
#undef  CONFIG_NLS_ISO8859_5
#undef  CONFIG_NLS_ISO8859_6
#undef  CONFIG_NLS_ISO8859_7
#undef  CONFIG_NLS_ISO8859_9
#undef  CONFIG_NLS_ISO8859_13
#undef  CONFIG_NLS_ISO8859_14
#undef  CONFIG_NLS_ISO8859_15
#undef  CONFIG_NLS_KOI8_R
#undef  CONFIG_NLS_KOI8_U
#undef  CONFIG_NLS_UTF8

/*
 * Sound
 */
#undef  CONFIG_SOUND

/*
 * USB support
 */
#undef  CONFIG_USB
#undef  CONFIG_USB_UHCI
#undef  CONFIG_USB_UHCI_ALT
#undef  CONFIG_USB_OHCI
#undef  CONFIG_USB_NON_PCI_OHCI
#undef  CONFIG_USB_PSP_HOST11
#undef  CONFIG_USB_AUDIO
#undef  CONFIG_USB_BLUETOOTH
#undef  CONFIG_USB_STORAGE
#undef  CONFIG_USB_STORAGE_DEBUG
#undef  CONFIG_USB_STORAGE_DATAFAB
#undef  CONFIG_USB_STORAGE_FREECOM
#undef  CONFIG_USB_STORAGE_ISD200
#undef  CONFIG_USB_STORAGE_DPCM
#undef  CONFIG_USB_STORAGE_HP8200e
#undef  CONFIG_USB_STORAGE_SDDR09
#undef  CONFIG_USB_STORAGE_JUMPSHOT
#undef  CONFIG_USB_ACM
#undef  CONFIG_USB_PRINTER
#undef  CONFIG_USB_DC2XX
#undef  CONFIG_USB_MDC800
#undef  CONFIG_USB_SCANNER
#undef  CONFIG_USB_MICROTEK
#undef  CONFIG_USB_HPUSBSCSI
#undef  CONFIG_USB_PEGASUS
#undef  CONFIG_USB_KAWETH
#undef  CONFIG_USB_CATC
#undef  CONFIG_USB_CDCETHER
#undef  CONFIG_USB_USBNET
#undef  CONFIG_USB_USS720

/*
 * USB Serial Converter support
 */
#undef  CONFIG_USB_SERIAL
#undef  CONFIG_USB_SERIAL_GENERIC
#undef  CONFIG_USB_SERIAL_BELKIN
#undef  CONFIG_USB_SERIAL_WHITEHEAT
#undef  CONFIG_USB_SERIAL_DIGI_ACCELEPORT
#undef  CONFIG_USB_SERIAL_EMPEG
#undef  CONFIG_USB_SERIAL_FTDI_SIO
#undef  CONFIG_USB_SERIAL_VISOR
#undef  CONFIG_USB_SERIAL_IR
#undef  CONFIG_USB_SERIAL_EDGEPORT
#undef  CONFIG_USB_SERIAL_KEYSPAN_PDA
#undef  CONFIG_USB_SERIAL_KEYSPAN
#undef  CONFIG_USB_SERIAL_KEYSPAN_USA28
#undef  CONFIG_USB_SERIAL_KEYSPAN_USA28X
#undef  CONFIG_USB_SERIAL_KEYSPAN_USA28XA
#undef  CONFIG_USB_SERIAL_KEYSPAN_USA28XB
#undef  CONFIG_USB_SERIAL_KEYSPAN_USA19
#undef  CONFIG_USB_SERIAL_KEYSPAN_USA18X
#undef  CONFIG_USB_SERIAL_KEYSPAN_USA19W
#undef  CONFIG_USB_SERIAL_KEYSPAN_USA49W
#undef  CONFIG_USB_SERIAL_MCT_U232
#undef  CONFIG_USB_SERIAL_PL2303
#undef  CONFIG_USB_SERIAL_CYBERJACK
#undef  CONFIG_USB_SERIAL_XIRCOM
#undef  CONFIG_USB_SERIAL_OMNINET
#undef  CONFIG_USB_RIO500

/*
 * Input core support
 */
#undef  CONFIG_INPUT
#undef  CONFIG_INPUT_KEYBDEV
#undef  CONFIG_INPUT_MOUSEDEV
#undef  CONFIG_INPUT_JOYDEV
#undef  CONFIG_INPUT_EVDEV

/*
 * Kernel hacking
 */
#define CONFIG_CROSSCOMPILE 1
#undef  CONFIG_REMOTE_DEBUG
#undef  CONFIG_GDB_CONSOLE
#undef  CONFIG_DEBUG
#undef  CONFIG_MAGIC_SYSRQ
#define CONFIG_MIPS_EMERALD 1
#undef  CONFIG_MIPS_JADE
#undef  CONFIG_MIPS_UNCACHED
#define CONFIG_ZLIB 1
