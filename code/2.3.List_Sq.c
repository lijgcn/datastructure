#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE 10
#define LISTINCREMENT 10

typedef struct{
    int *elem;
    int length;
    int listsize;
}SqList;

int InitList_Sq(SqList* L)
{
    int i=0;
    L->elem=(int*)malloc(LIST_INIT_SIZE*sizeof(int));
    if(!L->elem)
        exit(-1);
    L->length=0;
    L->listsize=LIST_INIT_SIZE;
    while(i<L->listsize)
    {
        printf("input L->elem[%d]=",i);
        scanf("%d",&L->elem[i]);
        L->length++;
        i++;
    }
    return 0;
}

void Print_Sq(SqList *L)
{
    int i;
    for(i=0;i<L->length;i++)
        printf("%d ",L->elem[i]);
}

int ListInsert_Sq(SqList* L,int i,int e)
{
    int* newbase;
    int* p;
    int* q;
    if((i<1)||(i>L->length+1))
        return -1;
    if(L->length+1>=L->listsize)
    {
        newbase=(int*)realloc(L->elem,(L->listsize+LISTINCREMENT)*sizeof(int));
        if(!newbase)
            exit(-1);
        L->elem=newbase;
        L->listsize+=LISTINCREMENT;
    }
    q=&(L->elem[i-1]);
    for(p=&(L->elem[L->length-1]);p>=q;p--)
    {
        *(p+1)=*p;
    }
    L->length++;
    *q=e;

    return 0;
}

int ListDelete_Sq(SqList* L,int i,int* e)
{
    int* p;
    int* q;
    if((i<1)||(i>L->length))
        return -1;
    p=&(L->elem[i-1]);
    *e=*p;
    q=L->elem+L->length-1;
    for(++p;p<=q;p++)
        *(p-1)=*p;
    L->length--;

    return 0;
}

int compare(int a,int b)
{
    if(a==b)
        return 1;
    else
        return 0;
}

int LocateElem_Sq(SqList* L,int e)
{
    int i=1;
    int* p=L->elem;
    while((i<=L->length)&&!(compare(*p++,e)))
        i++;
    if(i<=L->length)
        return i;
    else
        return 0;
}

void MergeList_Sq(SqList* La,SqList* Lb,SqList* Lc)
{
    int* pa=La->elem;
    int* pb=Lb->elem;
    int* pa_last=La->elem+La->length-1;
    int* pb_last=Lb->elem+Lb->length-1;
    Lc->listsize=Lc->length=La->length+Lb->length;
    int* pc=Lc->elem=(int *)malloc(Lc->listsize*sizeof(int));
    if(!Lc->elem)
        exit(-1);
    while((pa<=pa_last)&&(pb<=pb_last))
    {
        if(*pa<=*pb)
            *pc++=*pa++;
        else
            *pc++=*pb++;
    }
    while(pa<=pa_last)
        *pc++=*pa++;
    while(pb<=pb_last)
        *pc++=*pb++;
}

int main()
{
    SqList L,La,Lb,Lc;
    int i=0,e;
    //init
    InitList_Sq(&L);
    //insert
    printf("Please input insert number:\n");
    scanf("%d",&e);
    printf("Please input insert position:\n");
    scanf("%d",&i);
    ListInsert_Sq(&L,i,e);
    //delete
    printf("Please input which one delete:\n");
    scanf("%d",&i);
    ListDelete_Sq(&L,i,&e);
    printf("e = %d:\n",e);
    //locate
    printf("Please input search number:\n");
    scanf("%d",&e);
    printf("locate = %d\n",LocateElem_Sq(&L,e));
    //merge
    InitList_Sq(&La);
    InitList_Sq(&Lb);
    MergeList_Sq(&La,&Lb,&Lc);
    Print_Sq(&Lc);

    return 0;
}
