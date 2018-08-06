#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define OVERFLOW -2
#define ERROR -1

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef int status;
typedef char elemType;

typedef struct{
    elemType* base;
    elemType* top;
    int stacksize;
}SqStack;

status initStack(SqStack* S)
{
    S->base=(elemType*)malloc(STACK_INIT_SIZE*sizeof(elemType));
    if(!S->base)
        exit(OVERFLOW);
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
    return OK;
}

status push(SqStack* S,elemType e)
{
    if(S->top-S->base >= S->stacksize)
    {
        S->base=(elemType*)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(elemType));
        if(!S->base)
            exit(OVERFLOW);
        S->top=S->base+S->stacksize;
        S->stacksize+=STACKINCREMENT;
    }
    *S->top++=e;
    return OK;
}

status pop(SqStack* S,elemType* e)
{
    if(S->base==S->top)
        return ERROR;
    *e=*--S->top;
    return OK;
}

status clearStack(SqStack *S)
{
    if(S->top!=S->base)
        S->top=S->base;
    return OK;
}

status destroyStack(SqStack *S)
{
    free(S->base);
    return OK;
}

status saveStack(SqStack S)
{
    elemType* n;
    FILE* fp;
    n=S.base;
    fp=fopen("/home/lijg/Downloads/test.txt","a+");
    while(n!=S.top)
    {
        fputc(*n++,fp);
    }
    fclose(fp);
    return OK;
}

status lineEdit()
{
    SqStack S;
    elemType c;
    elemType ch;

    initStack(&S);
    ch=getchar();
    while(ch!=EOF)
    {
        while(ch!=EOF && ch!='\n')
        {
            switch(ch)
            {
                case '#':
                    pop(&S,&c);
                    break;
                case '@':
                    clearStack(&S);
                    break;
                default:
                    push(&S,ch);
                    break;
            }
            ch=getchar();
        }
        saveStack(S);
        clearStack(&S);
        if(ch!=EOF)
            ch=getchar();
    }
    destroyStack(&S);
}

int main()
{
    lineEdit();
    return 0;
}
