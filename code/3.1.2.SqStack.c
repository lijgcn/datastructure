#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define OVERFLOW -2
#define ERROR -1

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef int Status;

typedef struct{
    int* base;
    int* top;
    int stacksize;
}SqStack;

Status printSq(SqStack S)
{
    while(S.base!=S.top)
        printf("%d ",*(--S.top));
    printf("\n");
}

Status InitStack(SqStack* S)
{
    S->base=(int*)malloc(STACK_INIT_SIZE*sizeof(int));
    if(!S->base)
        exit(OVERFLOW);
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
    return OK;
}

Status GetTop(SqStack S,int* e)
{
    if(S.top==S.base)
    {
        return ERROR;
    }
    e=S.top-1;
    return OK;
}

Status Push(SqStack* S,int e)
{
    if(S->top-S->base >= S->stacksize)
    {
        S->base=(int*)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(int));
        if(!S->base)
            exit(OVERFLOW);
        S->top=S->base+S->stacksize;
        S->stacksize+=STACKINCREMENT;
    }
    *S->top++ = e;
    return OK;
}

Status Pop(SqStack* S,int* e)
{
    if(S->top==S->base)
        return ERROR;
    *e=*(--S->top);
    return OK;
}

int main()
{
    int i=0;
    int e;
    SqStack S;

    InitStack(&S);
    while(i++<5)
    {
        printf("input stack elem:\n");
        scanf("%d",&e);
        Push(&S,e);
    }
    GetTop(S,&e);
    printf("%d\n",e);
    while(--i>0)
    {
        Pop(&S,&e);
        printf("%d ",e);
    }

    return 0;
}
