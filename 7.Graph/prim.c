#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct _Edge {
	int id,w;
} Edge;
Edge e[205][205];
int n,m,edges[205],ans;

void prim(int x)
{
	int d[205],vis[205];
	for(int i=0;i<n;i++)
	{
		d[i]=0x3f3f3f3f;
		vis[i]=0;
	}
	d[x]=0;
	for(int i=1;i<n;i++)
	{
		int k=-1;
		for(int j=0;j<n;j++)
			if(!vis[j] && (k==-1 || d[j]<d[k]))
				k=j;
		vis[k]=1;
		for(int j=0;j<n;j++) 
			if(!vis[j] && e[k][j].w<d[j])
			{
				d[j]=e[k][j].w;
				edges[j]=e[k][j].id;
			}
	}
	for(int i=1;i<n;i++)
		ans+=d[i];
}

int cmp(const void *a,const void *b)
{
	return (*(int*)a)<(*(int*)b)?-1:1;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			e[i][j].w=0x3f3f3f3f;
	for(int i=0;i<m;i++)
	{
		int u,v,w,id;
		scanf("%d%d%d%d",&id,&u,&v,&w);
		e[u][v].id=e[v][u].id=id;
		e[u][v].w=e[v][u].w=w;
	}
	prim(0);
	printf("%d\n",ans);
	qsort(edges+1,n-1,sizeof(int),cmp);
	for(int i=1;i<n;i++)
		printf("%d ",edges[i]);
	return 0;
}