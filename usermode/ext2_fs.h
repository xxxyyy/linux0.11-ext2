#ifndef _LINUX_EXT2_FS_H
#define _LINUX_EXT2_FS_H

/*
 * The second extended filesystem constants/structures
 */

/*
 * Define EXT2FS_DEBUG to produce debug messages
 */
#undef EXT2FS_DEBUG

/*
 * Define DONT_USE_DCACHE to inhibit the directory cache
 */
#undef DONT_USE_DCACHE

/*
 * Define EXT2FS_DEBUG_CACHE to produce cache debug messages
 */
#undef EXT2FS_DEBUG_CACHE

/*
 * The second extended file system version
 */
#define EXT2FS_VERSION	"0.2c, 93/03/06"

/*
 * Special inodes numbers
 */
#define	EXT2_BAD_INO		 1	/* Bad blocks inode */
#define EXT2_ROOT_INO		 2	/* Root inode */
#define EXT2_ACL_INO		 3	/* ACL inode */
#define EXT2_FIRST_INO		11	/* First non reserved inode */

/*
 * The second extended file system magic number
 */
#define EXT2_OLD_SUPER_MAGIC	0xEF51
#define EXT2_SUPER_MAGIC	0xEF53

/*
 * Macro-instructions used to manage several block sizes
 */
#define EXT2_MIN_BLOCK_SIZE		1024
#define	EXT2_MAX_BLOCK_SIZE		4096
#define EXT2_MIN_BLOCK_LOG_SIZE		  10
#ifdef KERNEL
# define EXT2_BLOCK_SIZE(s)		((s)->s_blocksize)
#else
# define EXT2_BLOCK_SIZE(s)		(EXT2_MIN_BLOCK_SIZE << (s)->s_log_block_size)
#endif
#define	EXT2_ADDR_PER_BLOCK(s)		(EXT2_BLOCK_SIZE(s) / sizeof (unsigned long))
#ifdef KERNEL
# define EXT2_BLOCK_SIZE_BITS(s)	((s)->u.ext2_sb.s_log_block_size + 10)
#else
# define EXT2_BLOCK_SIZE_BITS(s)	((s)->s_log_block_size + 10)
#endif
#define	EXT2_INODES_PER_BLOCK(s)	(EXT2_BLOCK_SIZE(s) / sizeof (struct ext2_inode))

/*
 * Macro-instructions used to manage fragments
 */
#define EXT2_MIN_FRAG_SIZE		1024
#define	EXT2_MAX_FRAG_SIZE		1024
#define EXT2_MIN_FRAG_LOG_SIZE		  10
#ifdef KERNEL
# define EXT2_FRAG_SIZE(s)		((s)->u.ext2_sb.s_frag_size)
# define EXT2_FRAGS_PER_BLOCK(s)	((s)->u.ext2_sb.s_frags_per_block)
#else
# define EXT2_FRAG_SIZE(s)		(EXT2_MIN_FRAG_SIZE << (s)->s_log_frag_size)
# define EXT2_FRAGS_PER_BLOCK(s)	(EXT2_BLOCK_SIZE(s) / EXT2_FRAG_SIZE(s))
#endif

/*
 * Structure of a blocks group descriptor
 */
struct ext2_old_group_desc
{
	unsigned long bg_block_bitmap;		/* Blocks bitmap block */
	unsigned long bg_inode_bitmap;		/* Inodes bitmap block */
	unsigned long bg_inode_table;		/* Inodes table block */
	unsigned short bg_free_blocks_count;	/* Free blocks count */
	unsigned short bg_free_inodes_count;	/* Free inodes count */
};

struct ext2_group_desc
{
	unsigned long bg_block_bitmap;		/* Blocks bitmap block */
	unsigned long bg_inode_bitmap;		/* Inodes bitmap block */
	unsigned long bg_inode_table;		/* Inodes table block */
	unsigned short bg_free_blocks_count;	/* Free blocks count */
	unsigned short bg_free_inodes_count;	/* Free inodes count */
	unsigned short bg_used_dirs_count;	/* Directories count */
	unsigned short bg_pad;
	unsigned long bg_reserved[3];
};

/*
 * Macro-instructions used to manage group descriptors
 */
#ifdef KERNEL
# define EXT2_BLOCKS_PER_GROUP(s)	((s)->u.ext2_sb.s_blocks_per_group)
# define EXT2_DESC_PER_BLOCK(s)		((s)->u.ext2_sb.s_desc_per_block)
# define EXT2_INODES_PER_GROUP(s)	((s)->u.ext2_sb.s_inodes_per_group)
#else
# define EXT2_BLOCKS_PER_GROUP(s)	((s)->s_blocks_per_group)
# define EXT2_DESC_PER_BLOCK(s)		(EXT2_BLOCK_SIZE(s) / sizeof (struct ext2_group_desc))
# define EXT2_INODES_PER_GROUP(s)	((s)->s_inodes_per_group)
#endif

/*
 * Constants relative to the data blocks
 */
#define	EXT2_NDIR_BLOCKS	12
#define	EXT2_IND_BLOCK		EXT2_NDIR_BLOCKS
#define	EXT2_DIND_BLOCK		(EXT2_IND_BLOCK + 1)
#define	EXT2_TIND_BLOCK		(EXT2_DIND_BLOCK + 1)
#define	EXT2_N_BLOCKS		(EXT2_TIND_BLOCK + 1)

/*
 * Structure of an inode on the disk
 */
struct ext2_inode {
	unsigned short i_mode;		/* File mode */
	unsigned short i_uid;		/* Owner Uid */
	unsigned long i_size;		/* Size in bytes */
	unsigned long i_atime;		/* Access time */
	unsigned long i_ctime;		/* Creation time */
	unsigned long i_mtime;		/* Modification time */
	unsigned long i_dtime;		/* Deletion Time */
	unsigned short i_gid;		/* Group Id */
	unsigned short i_links_count;	/* Links count */
	unsigned long i_blocks;		/* Blocks count */
	unsigned long i_flags;		/* File flags */
	unsigned long i_reserved1;
	unsigned long i_block[EXT2_N_BLOCKS];/* Pointers to blocks */
	unsigned long i_version;	/* File version (for NFS) */
	unsigned long i_file_acl;	/* File ACL */
	unsigned long i_dir_acl;	/* Directory ACL */
	unsigned short i_faddr;		/* Fragment address */
	unsigned char i_frag;		/* Fragment number */
	unsigned char i_fsize;		/* Fragment size */
	unsigned long i_reserved2[3];
};
//

/* XXX 已经在我的机器上测试，大小一致。。。 */
typedef unsigned long   __u32;
typedef int             __s32;
typedef unsigned short  __u16;
typedef short           __s16;
typedef unsigned char   __u8;
typedef char            __s8;

/*
* Structure of an inode on the disk
*/
//struct ext2_inode {
//    __u16	i_mode;	/* File mode */
//    __u16	i_uid;	/* Low 16 bits of Owner Uid */
//    __u32	i_size;	/* Size in bytes */
//    __u32	i_atime;	/* Access time */
//    __u32	i_ctime;	/* Creation time */
//    __u32	i_mtime;	/* Modification time */
//    __u32	i_dtime;	/* Deletion Time */
//    __u16	i_gid;	/* Low 16 bits of Group Id */
//    __u16	i_links_count;	/* Links count */
//    __u32	i_blocks;	/* Blocks count */
//    __u32	i_flags;	/* File flags */
//    union {
//        struct {
//        __u32 l_i_reserved1;
//        } linux1;
//        struct {
//        __u32 h_i_translator;
//        } hurd1;
//        struct {
//        __u32 m_i_reserved1;
//        } masix1;
//    } osd1;	/* OS dependent 1 */
//    __u32	i_block[EXT2_N_BLOCKS];/* Pointers to blocks */
//    __u32	i_generation;	/* File version (for NFS) */
//    __u32	i_file_acl;	/* File ACL */
//    __u32	i_dir_acl;	/* Directory ACL */
//    __u32	i_faddr;	/* Fragment address */
//    union {
//        struct {
//        __u8	l_i_frag;	/* Fragment number */
//        __u8	l_i_fsize;	/* Fragment size */
//        __u16	i_pad1;
//        __u16	l_i_uid_high;	/* these 2 fields */
//        __u16	l_i_gid_high;	/* were reserved2[0] */
//        __u32	l_i_reserved2;
//        } linux2;
//        struct {
//        __u8	h_i_frag;	/* Fragment number */
//        __u8	h_i_fsize;	/* Fragment size */
//        __u16	h_i_mode_high;
//        __u16	h_i_uid_high;
//        __u16	h_i_gid_high;
//        __u32	h_i_author;
//        } hurd2;
//        struct {
//        __u8	m_i_frag;	/* Fragment number */
//        __u8	m_i_fsize;	/* Fragment size */
//        __u16	m_pad1;
//        __u32	m_i_reserved2[2];
//        } masix2;
//    } osd2;	/* OS dependent 2 */
//}; 
//


/*
 * Structure of the super block
 */
//struct ext2_super_block {
//	unsigned long s_inodes_count;	/* Inodes count */
//	unsigned long s_blocks_count;	/* Blocks count */
//	unsigned long s_r_blocks_count;	/* Reserved blocks count */
//	unsigned long s_free_blocks_count;/* Free blocks count */
//	unsigned long s_free_inodes_count;/* Free inodes count */
//	unsigned long s_first_data_block;/* First Data Block */
//	unsigned long s_log_block_size;	/* Block size */
//	unsigned long s_log_frag_size;	/* Fragment size */
//	unsigned long s_blocks_per_group;/* # Blocks per group */
//	unsigned long s_frags_per_group;/* # Fragments per group */
//	unsigned long s_inodes_per_group;/* # Inodes per group */
//	unsigned long s_mtime;		/* Mount time */
//	unsigned long s_wtime;		/* Write time */
//	unsigned long s_pad;		/* Padding to get the magic signature*/
//					/* at the same offset as in the */
//					/* previous ext fs */
//	unsigned short s_magic;		/* Magic signature */
//	unsigned short s_valid;		/* Flag */
//	unsigned long s_reserved[243];	/* Padding to the end of the block */
//};

/*
* Structure of the super block
*/
struct ext2_super_block {
    __u32	s_inodes_count;	/* Inodes count */
    __u32	s_blocks_count;	/* Blocks count */
    __u32	s_r_blocks_count;	/* Reserved blocks count */
    __u32	s_free_blocks_count;	/* Free blocks count */
    __u32	s_free_inodes_count;	/* Free inodes count */
    __u32	s_first_data_block;	/* First Data Block */
    __u32	s_log_block_size;	/* Block size */
    __s32	s_log_frag_size;	/* Fragment size */
    __u32	s_blocks_per_group;	/* # Blocks per group */
    __u32	s_frags_per_group;	/* # Fragments per group */
    __u32	s_inodes_per_group;	/* # Inodes per group */
    __u32	s_mtime;	/* Mount time */
    __u32	s_wtime;	/* Write time */
    __u16	s_mnt_count;	/* Mount count */
    __s16	s_max_mnt_count;	/* Maximal mount count */
    __u16	s_magic;	/* Magic signature */
    __u16	s_state;	/* File system state */
    __u16	s_errors;	/* Behaviour when detecting errors */
    __u16	s_minor_rev_level; /* minor revision level */
    __u32	s_lastcheck;	/* time of last check */
    __u32	s_checkinterval;	/* max. time between checks */
    __u32	s_creator_os;	/* OS */
    __u32	s_rev_level;	/* Revision level */
    __u16	s_def_resuid;	/* Default uid for reserved blocks */
    __u16	s_def_resgid;	/* Default gid for reserved blocks */
    /*
    * These fields are for EXT2_DYNAMIC_REV superblocks only.
    *
    * Note: the difference between the compatible feature set and
    * the incompatible feature set is that if there is a bit set
    * in the incompatible feature set that the kernel doesn't
    * know about, it should refuse to mount the filesystem.
    *
    * e2fsck's requirements are more strict; if it doesn't know
    * about a feature in either the compatible or incompatible
    * feature set, it must abort and not try to meddle with
    * things it doesn't understand...
    */
    __u32	s_first_ino; /* First non-reserved inode */
    __u16 s_inode_size; /* size of inode structure */
    __u16	s_block_group_nr; /* block group # of this superblock */
    __u32	s_feature_compat; /* compatible feature set */
    __u32	s_feature_incompat; /* incompatible feature set */
    __u32	s_feature_ro_compat; /* readonly-compatible feature set */
    __u8	s_uuid[16];	/* 128-bit uuid for volume */
    char	s_volume_name[16]; /* volume name */
    char	s_last_mounted[64]; /* directory where last mounted */
    __u32	s_algorithm_usage_bitmap; /* For compression */
    /*
    * Performance hints. Directory preallocation should only
    * happen if the EXT2_FEATURE_COMPAT_DIR_PREALLOC flag is on.
    */
    __u8	s_prealloc_blocks;	/* Nr of blocks to try to preallocate*/
    __u8	s_prealloc_dir_blocks;	/* Nr to preallocate for dirs */
    __u16	s_padding1;
    /*
    * Journaling support valid if EXT2_FEATURE_COMPAT_HAS_JOURNAL set.
    */
    __u8	s_journal_uuid[16];	/* uuid of journal superblock */
    __u32	s_journal_inum;	/* inode number of journal file */
    __u32	s_journal_dev;	/* device number of journal file */
    __u32	s_last_orphan;	/* start of list of inodes to delete */
    __u32	s_reserved[197];	/* Padding to the end of the block */
}; 
/*
 * Structure of a directory entry
 */
#define EXT2_NAME_LEN 255

struct ext2_dir_entry {
	unsigned long inode;		/* Inode number */
	unsigned short rec_len;		/* Directory entry length */
	unsigned short name_len;	/* Name length */
	char name[EXT2_NAME_LEN];	/* File name */
};

/*
 * EXT2_DIR_PAD defines the directory entries boundaries
 *
 * NOTE: It must be a multiple of 4
 */
#define EXT2_DIR_PAD		 	4
#define EXT2_DIR_ROUND 			(EXT2_DIR_PAD - 1)
#define EXT2_DIR_REC_LEN(name_len)	(((name_len) + 8 + EXT2_DIR_ROUND) & \
					 ~EXT2_DIR_ROUND)

#endif
