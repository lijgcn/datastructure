#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;

typedef struct DuLNode{
    ElemType data;
    struct DuLNode* prior;
    struct DuLNode* next;
}DuLNode,*DuLinkList;

DuLinkList GetElemP_DuL(DuLinkList L,int i)
{
    DuLinkList p;
    p=L;
    while(i)
    {
        p=p->next;
        if(p==L)
            return ERROR;
        i--;
    }
    return p;
}

int Print_DuLinkList(DuLinkList L,int length)
{
    int i;
    DuLinkList p;
    p=L->next;
    for(i=0;i<length;i++)
    {
        printf("[%d | %d | %d]\n",p->prior,p->data,p->next);
        p=p->next;
    }
}

Status Init_DuL(DuLinkList L,int length)
{
    DuLinkList p,q;
    int i;
    L->prior=L;
    L->next=L;
    q=L;
    for(i=0;i<length;i++)
    {
        p=(DuLinkList)malloc(sizeof(DuLNode));
        if(!p)
            return ERROR;
        printf("Please input L[%d]:",i);
        scanf("%d",&(p->data));
        p->prior=q;
        p->prior->next=p;
        p->next=L;
        q=p;
    }
    L->prior=q;
    return OK;
}

Status ListInsert_DuL(DuLinkList L,int i,ElemType e)
{
    DuLinkList p,s;
    if(!(p=GetElemP_DuL(L,i)))
        return ERROR;
    if(!(s=(DuLinkList)malloc(sizeof(DuLNode))))
        return ERROR;
    s->data=e;
    s->prior=p->prior;
    p->prior->next=s;
    s->next=p;
    p->prior=s;
    Print_DuLinkList(L,10);
    return OK;
}

Status ListDelete_DuL(DuLinkList L,int i,ElemType* e)
{
    DuLinkList p;
    if(!(p=GetElemP_DuL(L,i)))
        return ERROR;
    *e=p->data;
    p->prior->next=p->next;
    p->next->prior=p->prior;
    free(p);
    Print_DuLinkList(L,9);
    return OK;
}

int main()
{
    DuLinkList L;
    int length=9;
    int e;
    L=(DuLinkList)malloc(sizeof(DuLNode));
    //init
    Init_DuL(L,length);
    //insert
    ListInsert_DuL(L,9,0);
    //delete
    ListDelete_DuL(L,5,&e);
    return OK;
}
