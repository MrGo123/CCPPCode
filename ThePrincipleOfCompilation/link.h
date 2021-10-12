#ifndef _LINK_H_
#define _LINK_H_

#include <stdio.h>
#include <malloc.h>
#include <string.h>


typedef struct LinkNode LinkNode;
struct LinkNode     // 通用链表节点:定义一个用于存储目标数据指针的链表节点类型
{
    void *data;     // 用于存储目标数据对象的指针
    LinkNode *next; // 下节点
    LinkNode *pro;  // 上节点
};

// 双向通用链表:存储数据对象的指针
typedef struct
{                   
    int len;        // 链表长度
    LinkNode *head; // 链表头节点指针
    LinkNode *tail; // 链表尾节点指针
} Link;

// 创建链表
Link* link_create();
// 向后插入数据
void link_add(Link* link, void* p);
// 获取第 i 个节点
void* link_get_i(Link* link, int i);
// 删除第 i 个节点
void link_del_i(Link* link, int i);
// 销毁整个链表
void link_destroy(Link** link);
// 在 toLink 后添加 sorLink
void link_add_link(Link* toLink, Link* sorLink);
// 为 link 创建备份
Link* link_back(Link* link);
// 删除链表中节点，不删除链表本身
void link_clere(Link* link);

#endif
