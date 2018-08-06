#include "3.7.bs.h"

typedef struct Event{
	int occur_time;
	int n_type;
}Event, ElemType;

typedef struct LNode{
	struct Event data;
	struct LNode *next;
}LNode, *LinkList;

Status Print_LinkList(LNode* L)
{
    LinkList p;
    p = L;
    while(p)
    {
        printf("event: occur_time=%d  n_type=%d\n",p->data.occur_time,p->data.n_type);
        p=p->next;
    }
    return OK;
}

int Init_LinkList(LNode* L)
{
	L->data.occur_time = L->data.n_type = -1; 
	L->next = NULL;
	return OK;
}

Status GetElem_L(LNode* L,int i,ElemType* e)
{
    LinkList p;
    p=L->next;
    int j=1;
    while(p && j<i)
    {
        p=p->next;
        j++;
    }
    if(!p || j>i)
        return ERROR;
    e=&p->data;
    return OK;
}

Status ListInsert_L(LNode* L,int i, ElemType* e)
{
	LinkList p=L;
	LinkList s;
	int j=0;
	while(p && j<(i-1))
    	{
        	p=p->next;
        	j++;
    	}
    	if(!p || j>(i-1))
        	return ERROR;
    	s=(LinkList)malloc(sizeof(LNode));
    	s->data=*e;
    	s->next=p->next;
    	p->next=s;
    	return OK;
}

Status ListDelete_L(LNode* L,int i,ElemType* e)
{
    LinkList p=L;
    LinkList q;
    int j=0;
    while(p->next && j<(i-1))
    {
        p=p->next;
        j++;
    }
    if(!(p->next) || j>(i-1))
        return ERROR;
    q=p->next;
    p->next=q->next;
    *e=q->data;
    free(q);
    return OK;
}

Status ListEmpty(LNode* L)
{
	LinkList p=L;
	if(!p->next)
	{
		return OK;
	}
	else
	{
		return ERROR;
	}
}
