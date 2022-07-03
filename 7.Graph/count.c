#include<stdio.h>
#include<stdlib.h>
typedef struct _Edge {
	int next,to,w;
} Edge;
Edge e[2005];
int n,m;
int head[105],vis[105],cnt;
int status[105],cnt_s;

void adde(int u,int v,int w)
{
	e[++cnt].to=v;
	e[cnt].w=w;
	int pre=0;
	for(int i=head[u];i;pre=i,i=e[i].next)
		if(e[i].w>w)
		{
			e[cnt].next=i;
			e[pre].next=cnt;
			return;
		}
	if(!pre)
	{
		e[cnt].next=head[u];
		head[u]=cnt;
	}
	else
		e[pre].next=cnt;
}

void dfs(int x)
{
	if(vis[x])
		return;
	if(x==n-1)
	{
		for(int i=0;i<cnt_s;i++)
			printf("%d ",status[i]);
		putchar('\n');
		return;
	}
	vis[x]=1;
	for(int i=head[x];i;i=e[i].next)
	{
		status[cnt_s++]=e[i].w;
		dfs(e[i].to);
		--cnt_s;
	}
	vis[x]=0;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&w,&u,&v);
		adde(u,v,w);adde(v,u,w);
	}
	dfs(0);
	return 0;
}
