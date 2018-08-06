#include <stdio.h>
#include <stdlib.h>

#define OK 2
#define TRUE 1
#define FALSE 0
#define ERROR -1
#define OVERFLOW -2

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef int status;

typedef struct{
    int* base;
    int* top;
    int stacksize;
}SqStack;

status initStack(SqStack* S)
{
    S->base=(int *)malloc(STACK_INIT_SIZE*sizeof(char));
    if(!S->base)
        exit(OVERFLOW);
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
    return OK;
}

status push(SqStack* S,int e)
{
    if(S->top-S->base >= S->stacksize)
    {
        S->base=(int*)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(int));
        if(!S->base)
            exit(OVERFLOW);
        S->top=S->base+S->stacksize;
        S->stacksize+=STACKINCREMENT;
    }
    *S->top++=e;
    return OK;
}

status pop(SqStack* S,int* e)
{
    if(S->base==S->top)
        return ERROR;
    *e=*--S->top;
    return OK;
}

status stackEmpty(SqStack S)
{
    if(S.base==S.top)
        return TRUE;
    else
        return FALSE;
}

status getTop(SqStack S)
{
    if(S.base!=S.top)
        return *--S.top;
    return ERROR;
}

status in(int c,int optrSet[7])
{
    int i;
    for(i=0;i<7;i++)
    {
        if(optrSet[i]==c)
        {
            return TRUE;
        }
    }
    return FALSE;
}

char precede(int theta1,int theta2)
{
    char priority;
    if(theta1=='+' || theta1=='-')
    {
        switch(theta2)
        {
            case '+':
            case '-':
            case ')':
            case '#':
                priority='>';
                break;
            case '*':
            case '/':
            case '(':
                priority='<';
                break;

        }
    }
    else if(theta1=='*' || theta1=='/')
    {
        switch(theta2)
        {
            case '+':
            case '-':
            case '*':
            case '/':
            case ')':
            case '#':
                priority='>';
                break;
            case '(':
                priority='<';
                break;

        }
    }
    else if(theta1=='(')
    {
        switch(theta2)
        {
            case '+':
            case '-':
            case '*':
            case '/':
            case '(':
                priority='<';
                break;
            case ')':
                priority='=';
                break;
            case '#':
                return ERROR;
        }
    }
    else if(theta1==')')
    {
        switch(theta2)
        {
            case '+':
            case '-':
            case '*':
            case '/':
            case ')':
            case '#':
                priority='>';
                break;
            case '(':
                return ERROR;
        }
    }
    else if(theta1=='#')
    {
        switch(theta2)
        {
            case '+':
            case '-':
            case '*':
            case '/':
            case '(':
                priority='<';
                break;
            case '#':
                priority='=';
                break;
            case ')':
                return ERROR;
        }
    }
    else
    {
        return ERROR;
    }
    return priority;
}

int operate(int a,char theta,int b)
{
    int result;
    switch(theta)
    {
        case '+':
            result=a+b;
            break;
        case '-':
            result=a-b;
            break;
        case '*':
            result=a*b;
            break;
        case '/':
            result=a/b;
            break;
    }
    return result;
}

int evaluateExpression()
{
    SqStack opndSqStack;
    SqStack optrSqStack;
    int c,a,b,theta,x;
    int optrSet[7]={'+','-','*','/','(',')','#'};

    initStack(&opndSqStack);
    initStack(&optrSqStack);

    push(&optrSqStack,'#');
    c=getchar();

    while(c!='#' || getTop(optrSqStack)!='#')
    {
        if(!in(c,optrSet))
        {
            c-=48;
            push(&opndSqStack,c);
            c=getchar();
        }
        else
        {
            switch(precede(getTop(optrSqStack),c))
            {
                case '<':
                    push(&optrSqStack,c);
                    c=getchar();
                    break;
                case '=':
                    pop(&optrSqStack,&x);
                    c=getchar();
                    break;
                case '>':
                    pop(&optrSqStack,&theta);
                    pop(&opndSqStack,&b);
                    pop(&opndSqStack,&a);
                    push(&opndSqStack,operate(a,theta,b));
                    break;
            }
        }
    }

    return getTop(opndSqStack);
}

int main()
{
    printf("result = %d",evaluateExpression());
    return OK;
}
