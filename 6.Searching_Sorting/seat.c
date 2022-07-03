#include<stdio.h>
#include<stdlib.h>
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

typedef struct _Info {
	int id,seat;
	char name[25];
} Info;

Info T[105];
int n,m;

int cmp(const void *pa, const void *pb)
{
	const Info *a=(const Info*)pa,*b=(const Info*)pb;
	if(a->seat == b->seat)
		return a->id < b->id ? -1 : 1;
	return a->seat < b->seat ? -1 : 1;
}

int cmp1(const void *pa, const void *pb)
{
	const Info *a=(const Info*)pa,*b=(const Info*)pb;
	return a->id < b->id ? -1 : 1;
}

int main()
{
	FILE *in=fopen("in.txt","r"),*out=fopen("out.txt","w");
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		fscanf(in,"%d %s %d",&T[i].id,&T[i].name,&T[i].seat);
		m=max(T[i].seat,m);
	}
	qsort(T,n,sizeof(Info),cmp);
	int q=min(n,m),p=0,last=n;
	for(int i=1;i<=q && p<last-1;i++)
	{
		while(T[p].seat<i)
			++p;
		if(T[p].seat>i)
			T[--last].seat=i;
	}
	qsort(T,n,sizeof(Info),cmp);
	m=0;
	for(int i=0;i<n;i++)
		m=max(T[i].seat,m);
	for(int i=1;i<n;i++)
		if(T[i].seat==T[i-1].seat)
			T[i].seat=++m;
	qsort(T,n,sizeof(Info),cmp1);
	for(int i=0;i<n;i++)
		fprintf(out,"%d %s %d\n",T[i].id,T[i].name,T[i].seat);
	return 0;
}