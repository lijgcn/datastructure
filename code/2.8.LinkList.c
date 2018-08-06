#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef int ElemType;

typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;

Status Print_LinkList(LNode* L)
{
    LinkList p;
    p=L->next;
    while(p)
    {
        printf("[%d|%d]->",p->data,p->next);
        p=p->next;
    }
    printf("\n");
    return OK;
}

int Init_LinkList(LNode* L,int length)
{
    LinkList p;
    int i;
    L->next=NULL;
    for(i=0;i<length;i++)
    {
        p=(LinkList)malloc(sizeof(LNode));
        if(!p)
            return(OVERFLOW);
        printf("Please input Lt.data:\n");
        scanf("%d",&(p->data));
        p->next=L->next;
        L->next=p;
    }
    Print_LinkList(L);
    return OK;
}

Status GetElem_L(LNode* L,int i,int* e)
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
    *e=p->data;
    printf("%d\n",*e);
    return OK;
}

Status ListInsert_L(LNode* L,int i,ElemType e)
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
    s->data=e;
    s->next=p->next;
    p->next=s;
    Print_LinkList(L);
    return OK;
}

Status ListDelet_L(LNode* L,int i,ElemType* e)
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
    Print_LinkList(L);
    return OK;
}

void MergeList_L(LinkList La,LinkList Lb,LinkList Lc)
{
    LinkList pa,pb,pc;
    pa=La->next;
    pb=Lb->next;
    Lc=pc=La;
    while(pa && pb)
    {
        if(pa->data<=pb->data)
        {
            pc->next=pa;
            pc=pa;
            pa=pa->next;
        }
        else
        {
            pc->next=pb;
            pc=pb;
            pb=pb->next;
        }
    }
    pc->next=pa?pa:pb;
    free(Lb);
    Print_LinkList(Lc);
}

int main()
{
    LinkList L,La,Lb,Lc;
    int i,length=5;
    int e;

    //init
    L=(LinkList)malloc(sizeof(LNode));
    Init_LinkList(L,length);

    //locate
    GetElem_L(L,2,&e);

    //insert
    ListInsert_L(L,3,100);

    //delete
    ListDelet_L(L,2,&e);

    //merge
    La=(LinkList)malloc(sizeof(LNode));
    Init_LinkList(La,5);
    Lb=(LinkList)malloc(sizeof(LNode));
    Init_LinkList(Lb,7);
    MergeList_L(La,Lb,Lc);

    return 0;
}
