#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "id_table.h"


int get_id_addr(Link* id_link, char* id_name)
{
    LinkNode* p = id_link->head;
    Id* id_node;
    char addr_name[100];
    if (id_link == NULL)
    {
        printf("no id_table!\n");
        return -2;
    }
    for (int i = 0; i < id_link->len; i++)
    {
        id_node = (Id *)p->data;
        strcpy(addr_name, id_node->name);
        if (strcmp(addr_name, id_name) == 0)
        {
            return id_node->addr;
        }
        p = p->next;
    }
    return -1;   
}

int add_id_addr(Link* id_link, char* id_name)
{
    Id* id_word, *have_id;
    LinkNode* np, *p = id_link->head;
    id_word = (Id *)malloc((int)sizeof(Id));
    np = (LinkNode *)malloc((int)sizeof(LinkNode));
    id_word->addr = id_link->len+1;
    strcpy(id_word->name, id_name);
    np->data = id_word;
    if (id_link == NULL)
    {
        printf("no id_table!\n");
        return -2;
    }
    
    if (id_link->len == 0)
    {
        id_link->head = np;
        id_link->tail = np;
    }
    else
    {
        for (int i = 0; i < id_link->len; i++)
        {
            have_id = (Id *)p->data;
            if (strcmp(have_id->name, id_name) == 0)
            {
                return -1;
            }
            p = p->next;
        }
        id_link->tail->next = np;
        np->pro = id_link->tail;
        id_link->tail = np;
    }
    id_link->len++;
    return id_link->len;        
}

