#include "3.7.bs.h"
#include "3.7.LL.c"
#include "3.7.QN.c"

typedef LinkList EventList;

EventList ev;
Event en;
LinkQueue q[5];
QElemType customer;
int TotalTime, CustomerNum, close_time;

int min_q(LinkQueue q[])
{
	int min_length = QueueLength(q[1]);
	int i = 1;
	int ql;

	for(int j=2; j<=4; j++)
	{
		ql = QueueLength(q[j]);
		if(min_length > ql)
		{
			min_length = ql;
			i = j;
		}
	}
	return i;
}

void create_random(int *dt, int *it)
{
	time_t t;
	srand((unsigned) time(&t));
	*dt = (rand() % 30) + 5;
	*it = rand() % 5;
}

Status ev_insert(Event *en)
{
	int i=1;
	EventList p;
	p = ev->next;
	while(p)
	{
		if(en->occur_time < p->data.occur_time)
		{
			ListInsert_L(ev, i, en);
			return OK;
		}
		i++;
		p = p->next;
	}

	ListInsert_L(ev, i, en);
	return OK;
}

void open_for_day()
{
	int i;
	TotalTime = 0;
	CustomerNum = 0;

	ev = (LinkList)malloc(sizeof(LNode));
	Init_LinkList(ev);
	
	en.occur_time = 0;
	en.n_type = 0;
	ev_insert(&en);
	for(i=1; i<=4; i++)
	{
		InitQueue(&q[i]);
	}
}

void customer_arrived()
{
	int i = 0;
	int dt = 0, it = 0, nt = 0;
	Event tmpen;
	CustomerNum++;

	create_random(&dt, &it);
	nt = en.occur_time + it;
	if(nt < close_time)
	{
		tmpen.occur_time = nt;
		tmpen.n_type = 0;
		ev_insert(&tmpen);
	}

	i = min_q(q);
	customer.arrival_time = en.occur_time;
	customer.duration = dt;
	EnQueue(&q[i], &customer);
	
	if(QueueLength(q[i]) == 1)
	{
		tmpen.occur_time = en.occur_time + dt;
		tmpen.n_type = i;
		ev_insert(&tmpen);
	}

}

void customer_departure()
{
	int i=en.n_type;
	DeQueue(&q[i], &customer);
	
	if(en.occur_time >= customer.arrival_time)
	{
		TotalTime += (en.occur_time - customer.arrival_time);
	}
	else
	{
		printf("something wrong: en.occur_time=%d  customer.arrival_time=%d\n", en.occur_time, customer.arrival_time);
		exit(0);
	}

	if(!QueueEmpty(q[i]))
	{
		GetHead(&q[i], &customer);
		en.occur_time = en.occur_time + customer.duration;
		en.n_type = i;
		ev_insert(&en);
	}
}

void bank_simulation()
{
	int t=0;
	TotalTime = 0;
	CustomerNum = 0;
	open_for_day();

	while(!ListEmpty(ev))
	{
		ListDelete_L(ev, 1, &en);
		if(en.n_type == 0)
		{
			customer_arrived();
		}
		else
		{
			customer_departure();
		}
		printf("\nno.%d\n", ++t);
		Print_LinkList(ev);
	}
	printf("The Average Time is %.2f\n", (float)TotalTime/CustomerNum);
}

int main()
{
	close_time = 480;
	bank_simulation();

	return OK;
}
