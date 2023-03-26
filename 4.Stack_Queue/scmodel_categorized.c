#include<stdio.h>
#include<malloc.h>

typedef struct _DATATYPE {
	int cost;
	int in, deal;
} DATATYPE;
typedef struct _Linked {
	DATATYPE *d;
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
	node->d=x;
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
int PopQueue(Queue *q, DATATYPE **x)
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
	int idcnt=0,time=0,ctr=3,popid=0;
	int waves[100];
	DATATYPE d[10000];
	Queue *Q=NewQueue();
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",waves+i);
	for(int ti=0;ti<n;ti++)
	{
		// Pushing
		while(waves[ti]--)
		{
			scanf("%d",&t);
			++idcnt;
			d[idcnt].in=time;
			d[idcnt].cost=t;
			PushQueue(Q,d+idcnt);
		}
		// Checking
		for(;ctr<5;ctr++)
			if((Q->len)/ctr<7)
				break;
		int occ=0;
		for(int i=1;i<=popid;i++)
			if(d[i].cost) ++occ;
		// Popping
		for(int i=0;i<(ctr-occ);i++)
		{
			if(!(Q->len))
				break;
			DATATYPE *pd;
			PopQueue(Q,&pd);
			pd->deal=time;
			popid = pd-d;
		}
		for(int i=1;i<=popid;i++)
			if(d[i].cost) --d[i].cost;
		// Checking
		for(;ctr>3;ctr--)
			if((Q->len)/ctr>=7)
				break;
		++time;
	}
	while(Q->len)
	{
		int occ=0;
		for(int i=1;i<=popid;i++)
			if(d[i].cost) ++occ;
		// Popping
		for(int i=0;i<(ctr-occ);i++)
		{
			if(!(Q->len))
				break;
			DATATYPE *pd;
			PopQueue(Q,&pd);
			pd->deal=time;
			popid = pd-d;
		}
		for(int i=1;i<=popid;i++)
			if(d[i].cost) --d[i].cost;
		// Checking
		for(;ctr>3;ctr--)
			if((Q->len)/ctr>=7)
				break;
		++time;
	}
	for(int i=1;i<=idcnt;i++)
		printf("%d : %d\n", i, d[i].deal-d[i].in);
	return 0;
}