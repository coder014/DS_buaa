#include<stdio.h>
#include<stdlib.h>

typedef struct _sub {
	int k,e;
	struct _sub *next;
} sub;

sub a[10005],b[10005];
int cnta,cntb;
sub *ans;

sub *find(int e)
{
	sub *p=ans;
	while(p->next)
	{
		if(p->next->e >= e)
			p=p->next;
		else
			break;
	}
	return p;
}

void insertback(sub *p,int k,int e)
{
	sub *newp=(sub*)malloc(sizeof(sub));
	newp->k=k;
	newp->e=e;
	newp->next=p->next;
	p->next=newp;
}

int main()
{
	ans=(sub*)malloc(sizeof(sub));
	ans->e=-1;
	ans->next=NULL;
	for(;;)
	{
		scanf("%d%d",&a[cnta].k,&a[cnta].e);
		cnta++;
		if(getchar()!=' ')
			break;
	}
	for(;scanf("%d%d",&b[cntb].k,&b[cntb].e)!=EOF;)
		cntb++;
	for(int i=0;i<cnta;i++)
		for(int j=0;j<cntb;j++)
		{
			int k=a[i].k*b[j].k,e=a[i].e+b[j].e;
			if(k==0)
				continue;
			sub *p=find(e);
			if(p->e>=0 && p->e==e)
				p->k+=k;
			else
				insertback(p,k,e);
		}
	while(ans->next)
	{
		printf("%d %d ",ans->next->k,ans->next->e);
		ans=ans->next;
	}
	return 0;
}