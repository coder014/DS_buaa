#include<stdio.h>
#include<malloc.h>

typedef struct _DATATYPE {
	int id,t;
} DATATYPE;
typedef struct _Linked {
	DATATYPE d;
	struct _Linked *pre,*nxt;
} NODE;
typedef struct _Queue {
	int len;
	NODE *front, *end;
} Queue;
Queue *NewQueue()
{
	Queue *ret=(Queue*)malloc(sizeof(Queue));
	ret->len=0;
	return ret;
}
void FreeQueue(Queue *q)
{
	NODE *p=q->front;
	for(int i=0;i<(q->len);i++)
	{
		free(p);
		p=p->nxt;
	}
	free(q);
}
void PushQueue(Queue *q, DATATYPE *x)
{
	NODE *node=(NODE*)malloc(sizeof(NODE));
	node->d=*x;
	if(q->len)
	{
		node->nxt=q->front;
		q->front->pre=node;
	}
	else
		q->end=node;
	q->front=node;
	++(q->len);
}
int PopQueue(Queue *q, DATATYPE *x)
{
	if((q->len) <= 0)
		return 1;
	--(q->len);
	if(x)
		*x=q->end->d;
	if(q->len)
	{
		q->end=q->end->pre;
		free(q->end->nxt);
	}
	else
		free(q->end);
	return 0;
}

int main()
{
	int n,t;
	int idcnt=0,time=0,ctr=3;
	DATATYPE d;
	Queue *Q=NewQueue();
	scanf("%d",&n);
	while(n--)
	{
		scanf("%d",&t);
		// Pushing
		while(t--)
		{
			d.id=++idcnt;
			d.t=time;
			PushQueue(Q,&d);
		}
		// Checking
		for(;ctr<5;ctr++)
			if((Q->len)/ctr<7)
				break;
		// Popping
		for(int i=0;i<ctr;i++)
		{
			if(!(Q->len))
				break;
			PopQueue(Q,&d);
			printf("%d : %d\n",d.id,time-d.t);
		}
		// Checking
		for(;ctr>3;ctr--)
			if((Q->len)/ctr>=7)
				break;
		++time;
	}
	while(Q->len)
	{
		// Popping
		for(int i=0;i<ctr;i++)
		{
			if(!(Q->len))
				break;
			PopQueue(Q,&d);
			printf("%d : %d\n",d.id,time-d.t);
		}
		// Checking
		for(;ctr>3;ctr--)
			if((Q->len)/ctr>=7)
				break;
		++time;
	}
	return 0;
}