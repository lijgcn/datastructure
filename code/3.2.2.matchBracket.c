#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define OVERFLOW -2
#define ERROR -1
#define TRUE 1
#define FALSE 0

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

status getTop(SqStack S,elemType* e)
{
    if(S.base==S.top)
        return ERROR;
    *e=*(S.top-1);
}

status stackEmpty(SqStack S)
{
    if(S.base==S.top)
        return TRUE;
    else
        return FALSE;
}

status printSqStack(SqStack S)
{
    elemType* n;
    n=S.base;
    printf("now: ");
    while(n!=S.top)
    {
        printf("%c",*n++);
    }
    printf("\n");
    return OK;
}

status matchBracket()
{
    char C;
    SqStack S;
    char e;

    initStack(&S);
    printf("input the first open bracket:\n");
    scanf("%c",&C);
    if(C=='<' || C=='(' || C=='[' || C=='{')
    {
        push(&S,C);
    }
    else
    {
        printf("Wrong bracket, bye.");
        exit(ERROR);
    }

    while(!stackEmpty(S))
    {
        //fflush(stdin);
        getchar();
        printf("input bracket:\n");
        scanf("%c",&C);
        if(C=='<' || C=='(' || C=='[' || C=='{')
        {
            push(&S,C);
            printSqStack(S);
        }
        else if(C=='>' || C==')' || C==']' || C=='}')
        {
            getTop(S,&e);
            if(C-e==2 || C-e==1)
            {
                pop(&S,&e);
                printf("match success: %c%c\n",e,C);
                printSqStack(S);
            }
            else
                printf("Wrong close bracket, try again.\n");
        }
        else
            printf("Not bracket, try again.\n");
    }
}

int main()
{
    matchBracket();
    return 0;
}
