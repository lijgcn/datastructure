#include "3.7.bs.h"

typedef struct QElemType{
	int arrival_time;
	int duration;
}QElemType;

typedef struct QNode{
	struct QElemType *data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct LinkQueue{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

Status PrintQueue(LinkQueue* Q)
{
    QueuePtr p;
    p=Q->front->next;
    while(p)
    {
        printf("arrival_time=%d  duration=%d\n",p->data->arrival_time, p->data->duration);
        p=p->next;
    }
    return OK;
}

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

Status EnQueue(LinkQueue* Q, QElemType* e)
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
    e = p->data;
    Q->front->next = p->next;
    if(Q->rear == p)
        Q->rear = Q->front;
    free(p);
    return OK;
}

int QueueLength(LinkQueue Q)
{
	int i=0;
	QueuePtr p;

	p = Q.front->next;
	while(p)
	{
		i++;
		p = p->next;
	}
	return i;
}

Status GetHead(LinkQueue* Q, QElemType* e)
{
	QueuePtr p;
	p = Q->front->next;
	e = p->data;
}

Status QueueEmpty(LinkQueue Q)
{
	if(Q.front == Q.rear)
		return OK;
	else
		return ERROR;
}
