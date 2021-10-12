#ifndef _LINK_H_
#define _LINK_H_

#include <stdio.h>
#include <malloc.h>
#include <string.h>


typedef struct LinkNode LinkNode;
struct LinkNode     // ͨ������ڵ�:����һ�����ڴ洢Ŀ������ָ�������ڵ�����
{
    void *data;     // ���ڴ洢Ŀ�����ݶ����ָ��
    LinkNode *next; // �½ڵ�
    LinkNode *pro;  // �Ͻڵ�
};

// ˫��ͨ������:�洢���ݶ����ָ��
typedef struct
{                   
    int len;        // ������
    LinkNode *head; // ����ͷ�ڵ�ָ��
    LinkNode *tail; // ����β�ڵ�ָ��
} Link;

// ��������
Link* link_create();
// ����������
void link_add(Link* link, void* p);
// ��ȡ�� i ���ڵ�
void* link_get_i(Link* link, int i);
// ɾ���� i ���ڵ�
void link_del_i(Link* link, int i);
// ������������
void link_destroy(Link** link);
// �� toLink ����� sorLink
void link_add_link(Link* toLink, Link* sorLink);
// Ϊ link ��������
Link* link_back(Link* link);
// ɾ�������нڵ㣬��ɾ��������
void link_clere(Link* link);

#endif
