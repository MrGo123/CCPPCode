#ifndef _ID_TABLE_H_
#define _ID_TABLE_H_

#include "link.h"

// ���ű�
typedef struct 
{
    int addr;       // ��ʶ�����ŵ�ַ
    char name[100]; // ��ʶ����������
}Id;



// ��ȡһ����������Ӧ���ڴ��ַ�������ڷ��� -1
int get_id_addr(Link* id_link, char* id_name);

// ��һ��������ӵ����ű��У������ظ÷��ŵ�ַ��������Ŵ��ڷ��� -1
int add_id_addr(Link* id_link, char* id_name);

#endif