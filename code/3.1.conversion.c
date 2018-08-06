#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define OVERFLOW -2
#define ERROR -1
#define TRUE 1
#define FALSE 0

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef int Status;

typedef struct{
    int* base;
    int* top;
    int stacksize;
}SqStack;

Status InitStack(SqStack* S)
{
    S->base=(int*)malloc(STACK_INIT_SIZE*sizeof(int));
    if(!S->base)
        exit(OVERFLOW);
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
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

Status StackEmpty(SqStack S)
{
    if(S.base==S.top)
        return TRUE;
    else
        return FALSE;
}

Status conversion()
{
    int N;
    SqStack S;
    int e;

    InitStack(&S);
    printf("input a number:\nDecimal:");
    scanf("%d",&N);
    while(N)
    {
        Push(&S,N%8);
        N/=8;
    }
    printf("Octal:");
    while(!StackEmpty(S))
    {
        Pop(&S,&e);
        printf("%d",e);
    }
    return OK;
}

int main()
{
    conversion();
    return 0;
}
