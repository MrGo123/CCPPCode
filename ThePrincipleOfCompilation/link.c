#include "link.h"

#define LINK_DEBUG

Link* link_create()
{
    Link* p;
    p = (Link *)malloc((int)sizeof(Link));
    if (p == NULL)
    {
        #ifdef LINK_DEBUG
            printf("(link debug)NULL pointer on(link_create)\n");
        #endif
        return NULL;
    }
    p->len = 0;
    p->head = NULL;
    p->tail = NULL;
    return p;
}

void link_add(Link* link, void* p)
{
    LinkNode* np = NULL;
    if (p == NULL || link == NULL)
    {
        #ifdef LINK_DEBUG
            printf("(link debug)NULL pointer on(link_add)\n");
        #endif
        return ;
    }
    np = (LinkNode *)malloc((int)sizeof(LinkNode));
    if (np == NULL)
    {
        return ;
    }
    np->data = p;
    np->next = NULL;
    np->pro = NULL;
    if (link->len == 0)
    {
        link->head = np;
        link->tail = np;
    }
    else
    {
        link->tail->next = np;
        np->pro = link->tail;
        link->tail = np;
    }
    link->len++;
    return ;
}

void* link_get_i(Link* link, int i) 
{
    LinkNode* pn;
    if (link == NULL || link->head == NULL || i < 0 || i >= link->len)
    {
        #ifdef LINK_DEBUG
            printf("(link debug)NULL pointer on(link_get_i)\nlink = %x, link_len = %d, i = %d\n", \
            link, (link == NULL)?-1:link->len,i);
        #endif
        return NULL;
    }
    pn = link->head;
    while (i-->0)
    {
        pn = pn->next;
    }
    return pn->data;
}

void link_destroy(Link** link)
{
    int i;
    LinkNode* np;
    if (*link == NULL)
    {
        #ifdef LINK_DEBUG
            printf("(link debug)NULL pointer on(link_destroy)\n");
        #endif
        return ;
    }
    for (i = 0; i < (*link)->len; i++)
    {
        np = (*link)->head;
        (*link)->head = (*link)->head->next;
        free(np);
    }
    free(*link);
    *link = NULL;
}

void link_add_link(Link* toLink, Link* sorLink)
{
    LinkNode *p;
    if (toLink == NULL || sorLink == NULL)
    {
        #ifdef LINK_DEBUG
            printf("(link debug)NULL pointer on(link_add_link)\n");
        #endif
        return ;
    }
    p = sorLink->head;
    while (p)
    {
        link_add(toLink, (Link *)p->data);
        p = p->next;
    }
    return ;
}

Link* link_back(Link* link)
{
    Link* new_link;
    new_link = link_create();
    link_add_link(new_link, link);
    return new_link;
}

void link_clere(Link* link)
{
    int i;
    LinkNode* np;
    if (link == NULL)
    {
        #ifdef LINK_DEBUG
            printf("(link debug)NULL pointer on(link_clere)\n");
        #endif
        return ;
    }
    for (i = 0; i < link->len; i++)
    {
        np = link->head;
        link->head = link->head->next;
        free(np);
    }
    link->len = 0;
    link->head = NULL;
    link->tail = NULL;
}
























