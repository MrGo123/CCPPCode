#ifndef _ID_TABLE_H_
#define _ID_TABLE_H_

#include "link.h"

// 符号表
typedef struct 
{
    int addr;       // 标识符符号地址
    char name[100]; // 标识符符号名字
}Id;



// 获取一个符号名对应的内存地址，不存在返回 -1
int get_id_addr(Link* id_link, char* id_name);

// 将一个符号添加到符号表中，并返回该符号地址，如果符号存在返回 -1
int add_id_addr(Link* id_link, char* id_name);

#endif