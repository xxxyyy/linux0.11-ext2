/*
 * =====================================================================================
 *
 *       Filename:  text2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/24/2014 10:34:58 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jinxiao Huang
 *   Organization:  YJH
 * 
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h> 
#include <assert.h>
#include "ext2_fs.h"

const int blocksize = 1024;
int main(void)
{
    FILE *ext2 = fopen("e.img", "rb");
    assert( NULL != ext2 );
    fseek(ext2, 0x0L, SEEK_END);
    int file_size = ftell(ext2);/*  获取 e.img 文件大小 */
    char *img = (char*)malloc(file_size);/* 申请同等大小的内存空间 */
    assert( NULL != img );
    fseek(ext2, 0, SEEK_SET);
    fread(img, file_size, 1, ext2);
    fclose(ext2);

    // ext2 各种块的整体布局，可以参考 (vim下光标移到超链接上，然后普通模式下gx有彩蛋)
    // http://courses.cs.washington.edu/courses/cse451/09sp/projects/project3light/project3_light.html
    
    // ext2 各个数据结构的详细信息，可以参考
    // http://www.nongnu.org/ext2-doc/ext2.html
    
    /* 考虑各种块的位置关系时，把示意图放在旁边会有很大帮助 */

    /* 整个分区最前面的1 block(1024 byte)是启动扇区  */
    struct ext2_super_block *sb = (struct ext2_super_block*) (img + blocksize); 
    printf("ext2幻数:%X\n第一个非保留结点(用户可用):%ld\n"
           "每组的块数:%ld\n每组的inode数:%ld\n",
            sb->s_magic, sb->s_first_ino, 
            sb->s_blocks_per_group, sb->s_inodes_per_group );

    /* super block size == 1024 byte  */
    struct ext2_group_desc *gdt = (struct ext2_group_desc*)((char*)sb+blocksize); /* ok  */

    /* 
     * 数据块位图的起始位置需要计算，参考上文给出的华盛顿大学的资料:
     * 注意， group descriptor table 占用整数个block，所以不足1个block的补齐
     */
    char *dbmap = NULL ; /* TODO 需要计算！ */
    (void)dbmap;/* 消除未使用变量的警告  */

    /* inode bitmap(inode位图) 的起始地址可以由gdt表中的数据来算  */
    char *inmap = img + gdt->bg_inode_bitmap * blocksize;
    /*printf("%X\n", inmap-img);  */ /* AC00 */
    (void)inmap;

    /* inode bitmap(inode位图) 占1个block， 故接下来的inode表的地址可以这么算  */
    struct ext2_inode *inodes = (struct ext2_inode*)( img + (gdt->bg_inode_bitmap+1)*1024 );

    /* 
     * xxd img文件看inode位图可以知道 第13号inode 是我们测试文件的inode 
     *
     * 一般来说，0号inode不用， 1号inode是这个分区的根目录
     * 正常的、合理的，我们根据 inode位图 判定一个inode是否使用，这个实现过程交给你啦～ 
     *
     *   这里我已知该文件系统的特性(通过 xxd/dumpe2fs等工具)，所以直接定位到13号inode，并且只查看了1个数据块，
     *   这仅仅是作为一个简单的示例。
     *   正常情况下各种信息都是要算出来的！
     *
     *   XXX 危险代码风格，千万不要模仿！
     */
    /*struct ext2_inode *anode = inodes + 13 ;  */
//    char   *data = anode->i_block[0] * blocksize + img;
//    printf("文件的内容是：%s\n", data);

    struct ext2_inode *iroot = inodes + 1; /* root dir 的 inode */
    struct ext2_dir_entry *root = (struct ext2_dir_entry*)(img + iroot->i_block[0] * blocksize);
    printf("inode:%ld, len:%d\n", root->inode, root->rec_len);
    struct ext2_inode *file_inode;
    int total_len = root->rec_len;
    while( root->rec_len && total_len < blocksize ){
        /*printf("*inode:%ld*\n", root->inode);  */
        if( 1 == root->file_type ){
            file_inode = inodes + root->inode - 1; /*第N块的下标是N-1 */
            printf("data: %s\n", file_inode->i_block[0] * blocksize + img);
        }
        total_len += root->rec_len;
        root = (struct ext2_dir_entry*)((char*)root + root->rec_len);
    }

    return 0;
}

