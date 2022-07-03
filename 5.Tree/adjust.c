#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _GATE {
	int id,flow;
} Gate;

typedef struct _TREE {
	int id;
	struct _TREE *nxt[3];
} Tree;

Tree *nodes[205];
Gate gates[105];
int cntgate,cntnode;

Tree *FindOrCreate(int x)
{
	int res;
	for(res=0;res<cntnode;res++)
		if(nodes[res]->id==x)
			break;
	if(res<cntnode)
		return nodes[res];
	nodes[cntnode++]=(Tree*)malloc(sizeof(Tree));
	memset(nodes[cntnode-1],0,sizeof(Tree));
	nodes[cntnode-1]->id=x;
	return nodes[cntnode-1];
}

void bfs()
{
	Tree *queue[205];
	int qhead=0,qend=-1,total=0;
	queue[++qend]=nodes[0];
	Tree *p;
	while(qhead<=qend)
	{
		p=queue[qhead++];
		if(p->id<100)
			printf("%d->%d\n",gates[total++].id,p->id);
		else
			for(int i=0;i<3;i++)
				if(p->nxt[i])
					queue[++qend]=p->nxt[i];
				else break;
	}
}

int mycmp(const void *pa,const void *pb)
{
	const Gate *a=(const Gate*)pa,*b=(const Gate*)pb;
	if(a->flow==b->flow)
		return a->id < b->id?-1:1;
	return a->flow > b->flow?-1:1;
}

int main()
{
	int t,s;
	while(1)
	{
		scanf("%d",&t);
		if(t==-1)
			break;
		Tree *p=FindOrCreate(t);
		for(int i=0;i<4;i++)
		{
			scanf("%d",&t);
			if(t==-1)
				break;
			p->nxt[i]=FindOrCreate(t);
		}
	}
	while(scanf("%d%d",&t,&s)!=EOF)
	{
		gates[cntgate].id=t;
		gates[cntgate++].flow=s;
	}
	qsort(gates,cntgate,sizeof(Gate),mycmp);
	bfs();
	return 0;
}