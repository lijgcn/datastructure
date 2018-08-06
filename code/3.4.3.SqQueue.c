#include <stdio.h>
#include <stdlib.h>

#define OK 2
#define ERROR -1
#define OVERFLOW -2
#define MAXQSIZE 100

typedef int Status;
typedef int QElemType;

typedef struct{
    QElemType *base;
    int front;
    int rear;
}SqQueue;

Status InitQueue(SqQueue *Q)
{
    Q->base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
    if(!Q->base)
        exit(OVERFLOW);
    Q->front = Q->rear = 0;
    return OK;
}

int QueueLength(SqQueue Q)
{
    return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

Status EnQueue(SqQueue *Q, QElemType e)
{
    if((Q->rear + 1) % MAXQSIZE == Q->front)
        return ERROR;
    Q->base[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAXQSIZE;
    return OK;
}

Status DeQueue(SqQueue *Q, QElemType *e)
{
    if(Q->front == Q->rear)
        return ERROR;
    *e = Q->base[Q->front];
    Q->front = (Q->front + 1) % MAXQSIZE;
    return OK;
}

Status OutputQueue(SqQueue Q)
{
	int m = Q.front;
	printf("now queue length: %d\n", QueueLength(Q));
	while(m != Q.rear)
	{
		printf("%d ", Q.base[m]);
		m++;
	}
	printf("\n");
}

int main()
{
	QElemType a, b, c, f;
	a = 1;
	b = 2;
	c = 3;

	SqQueue que;

	InitQueue(&que);
	OutputQueue(que);

	EnQueue(&que, a);
	EnQueue(&que, b);
	EnQueue(&que, c);
	OutputQueue(que);

	DeQueue(&que, &f);
	DeQueue(&que, &f);
	OutputQueue(que);

	return OK;
}
