#include <stdio.h>
#include <stdlib.h>

#define OK 2
#define ERROR -1
#define OVERFLOW -2

typedef int Status;
typedef int QElemType;

typedef struct QNode{
    QElemType data;
    struct QNode *next;
}QNode, *QueuePtr;

typedef struct{
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;

Status InitQueue(LinkQueue* Q)
{
    Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
    if(!Q->front)
        exit(OVERFLOW);
    Q->front->next = NULL;
    return OK;
}

Status DestroyQueue(LinkQueue* Q)
{
    while(Q->front)
    {
        Q->rear = Q->front->next;
        free(Q->front);
        Q->front = Q->rear;
    }
    return OK;
}

Status EnQueue(LinkQueue* Q, QElemType e)
{
    QueuePtr p;
    p = (QueuePtr)malloc(sizeof(QNode));
    if(!p)
        exit(OVERFLOW);
    p->data = e;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
    return OK;
}

Status DeQueue(LinkQueue* Q, QElemType* e)
{
    QueuePtr p;
    if(Q->front == Q->rear)
        return ERROR;
    p = Q->front->next;
    *e = p->data;
    Q->front->next = p->next;
    if(Q->rear == p)
        Q->rear = Q->front;
    free(p);
    return OK;
}

Status PrintQueue(LinkQueue* Q)
{
    QueuePtr p;
    p=Q->front->next;
    while(p)
    {
        printf("%d ",p->data);
        p=p->next;
    }
    return OK;
}

int main()
{
    int a,b,c,d;
    a=1;
    b=2;
    c=3;
    LinkQueue mq;

    InitQueue(&mq);

    EnQueue(&mq,a);
    EnQueue(&mq,b);
    EnQueue(&mq,c);
    PrintQueue(&mq);

    DeQueue(&mq,&d);

    DestroyQueue(&mq);

    return OK;
}
