#ifndef _LINUX_VIRTUAL_H
#define _LINUX_VIRTUAL_H


#define NB_IPV4ROOT     16


#define VC_CATEGORY(c)		(((c) >> 24) & 0x3F)
#define VC_COMMAND(c)		(((c) >> 16) & 0xFF)
#define VC_VERSION(c)		((c) & 0xFFF)

#define VC_CMD(c,i,v)		((((VC_CAT_ ## c) & 0x3F) << 24) \
				| (((i) & 0xFF) << 16) | ((v) & 0xFFF))

/*

  Syscall Matrix V2.3

         |VERSION|CREATE |MODIFY |MIGRATE|CONTROL|EXPERIM| |SPECIAL|SPECIAL|
         |STATS  |DESTROY|ALTER  |CHANGE |LIMIT  |TEST   | |       |       |
         |INFO   |SETUP  |       |MOVE   |       |       | |       |       |
  -------+-------+-------+-------+-------+-------+-------+ +-------+-------+
  SYSTEM |VERSION|       |       |       |       |       | |DEVICES|       |
  HOST   |     00|     01|     02|     03|     04|     05| |     06|     07|
  -------+-------+-------+-------+-------+-------+-------+ +-------+-------+
  CPU    |       |       |       |       |       |       | |SCHED. |       |
  PROCESS|     08|     09|     10|     11|     12|     13| |     14|     15|
  -------+-------+-------+-------+-------+-------+-------+ +-------+-------+
  MEMORY |       |       |       |       |       |       | |SWAP   |       |
         |     16|     17|     18|     19|     20|     21| |     22|     23|
  -------+-------+-------+-------+-------+-------+-------+ +-------+-------+
  NETWORK|       |       |       |       |       |       | |SERIAL |       |
         |     24|     25|     26|     27|     28|     29| |     30|     31|
  -------+-------+-------+-------+-------+-------+-------+ +-------+-------+
  DISK   |       |       |       |       |       |       | |       |       |
  VFS    |     32|     33|     34|     35|     36|     37| |     38|     39|
  -------+-------+-------+-------+-------+-------+-------+ +-------+-------+
  OTHER  |       |       |       |       |       |       | |       |       |
         |     40|     41|     42|     43|     44|     45| |     46|     47|
  =======+=======+=======+=======+=======+=======+=======+ +=======+=======+
  SPECIAL|       |       |       |       |       |       | |       |       |
         |     48|     49|     50|     51|     52|     53| |     54|     55|
  -------+-------+-------+-------+-------+-------+-------+ +-------+-------+
  SPECIAL|       |       |       |       |RLIMIT |SYSCALL| |       |COMPAT |
         |     56|     57|     58|     59|     60|TEST 61| |     62|     63|
  -------+-------+-------+-------+-------+-------+-------+ +-------+-------+

*/

#define VC_CAT_VERSION		0
#define VC_CAT_VSETUP           1
#define VC_CAT_VHOST		2

#define VC_CAT_PROCALT		10
#define VC_CAT_PROCMIG          11
#define VC_CAT_PROCTRL		12

#define VC_CAT_SCHED		14
#define VC_CAT_INODE		38

#define	VC_CAT_VINFO		46

#define VC_CAT_FLAGS            59
#define VC_CAT_RLIMIT		60

#define VC_CAT_SYSTEST		61
#define VC_CAT_COMPAT		63



/*  interface version */

#define VCI_VERSION		0x00010004



/*  query version */

#define VCMD_get_version	VC_CMD(VERSION, 0, 0)


/*  compatibiliy vserver commands */

#define VCMD_new_s_context	VC_CMD(COMPAT, 1, 1)
#define VCMD_set_ipv4root	VC_CMD(COMPAT, 2, 3)

#define	VCMD_enter_namespace	VC_CMD(PROCALT, 1, 0)
#define	VCMD_cleanup_namespace	VC_CMD(PROCALT, 2, 0)
#define	VCMD_set_namespace	VC_CMD(PROCALT, 3, 0)

/*  compatibiliy vserver arguments */

struct  vcmd_new_s_context_v1 {
	uint32_t remove_cap;
	uint32_t flags;
};

struct  vcmd_set_ipv4root_v3 {
	/* number of pairs in id */
	uint32_t broadcast;
	struct {
		uint32_t ip;
		uint32_t mask;
	} ip_mask_pair[NB_IPV4ROOT];
};

/*  context signalling */

#define VCMD_ctx_kill		VC_CMD(PROCTRL, 1, 0)

struct  vcmd_ctx_kill_v0 {
	int32_t pid;
	int32_t sig;
};

/*  rlimit vserver commands */

#define VCMD_get_rlimit		VC_CMD(RLIMIT, 1, 0)
#define VCMD_set_rlimit		VC_CMD(RLIMIT, 2, 0)
#define VCMD_get_rlimit_mask	VC_CMD(RLIMIT, 3, 0)

struct  vcmd_ctx_rlimit_v0 {
	uint32_t id;
	uint64_t minimum;
	uint64_t softlimit;
	uint64_t maximum;
};

struct  vcmd_ctx_rlimit_mask_v0 {
	uint32_t minimum;
	uint32_t softlimit;
	uint32_t maximum;
};

#define CRLIM_INFINITY		(~0ULL)
#define CRLIM_KEEP		(~1ULL)



#define VC_CAT_SCHED		14

/* scheduler vserver commands */

#define VCMD_set_sched		VC_CMD(SCHED, 1, 1)

/* Options - these ones enable or disable the CTX_SCHED flag */
#define TBF_SCHED_ENABLE       0x0001
#define TBF_SCHED_DISABLE      0x0002

/* Structure for context's TBF scheduling priorities */
struct  vcmd_set_sched_v1 {
       int32_t fill_rate;
       int32_t period;
       int32_t fill_level;
       int32_t bucket_size;
};



/*  inode vserver commands */

#define VCMD_get_iattr_v0       VC_CMD(INODE, 1, 0)
#define VCMD_set_iattr_v0       VC_CMD(INODE, 2, 0)
#define VCMD_get_iattr          VC_CMD(INODE, 1, 1)
#define VCMD_set_iattr          VC_CMD(INODE, 2, 1)

struct  vcmd_ctx_iattr_v1 {
        const char *file_name;
        uint32_t xid;
        uint32_t flags;
        uint32_t mask;
};

#define IATTR_XID	0x01000000

#define IATTR_ADMIN	0x00000001
#define IATTR_WATCH	0x00000002
#define IATTR_HIDE	0x00000004

#define IATTR_BARRIER	0x00010000
#define	IATTR_IUNLINK	0x00020000
#define IATTR_IMMUTABLE	0x00040000


/* vinfo commands */

#define	VCMD_task_xid		VC_CMD(VINFO, 1, 0)
#define	VCMD_task_nid		VC_CMD(VINFO, 2, 0)

#define	VCMD_vx_info		VC_CMD(VINFO, 5, 0)
#define	VCMD_nx_info		VC_CMD(VINFO, 6, 0)

struct  vcmd_vx_info_v0 {
    uint32_t xid;
    uint32_t initpid;
    /* more to come */
};


#define VCMD_vx_set_vhi_name		VC_CMD(VHOST, 1, 0)
#define VCMD_vx_get_vhi_name		VC_CMD(VHOST, 2, 0)

struct  vcmd_vx_vhi_name_v0 {
       uint32_t field;
       char name[65];
};

enum vx_vhi_name_field {
       VHIN_CONTEXT=0,
       VHIN_SYSNAME,
       VHIN_NODENAME,
       VHIN_RELEASE,
       VHIN_VERSION,
       VHIN_MACHINE,
       VHIN_DOMAINNAME,
};

#define VCMD_create_context     VC_CMD(VSETUP, 1, 0)
#define VCMD_migrate_context    VC_CMD(PROCMIG, 1, 0)

#define VCMD_get_flags          VC_CMD(FLAGS, 1, 0)
#define VCMD_set_flags          VC_CMD(FLAGS, 2, 0)
struct  vcmd_ctx_flags_v0 {
        uint64_t flagword;
        uint64_t mask;
};


#define VCMD_get_ccaps          VC_CMD(FLAGS, 3, 0)
#define VCMD_set_ccaps          VC_CMD(FLAGS, 4, 0)
struct  vcmd_ctx_caps_v0 {
        uint64_t scaps;
        uint64_t ccaps;
        uint64_t cmask;
};

#endif /* _LINUX_VIRTUAL_H */
