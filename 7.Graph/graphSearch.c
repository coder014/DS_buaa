#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int n,m;
char a[102][102];
int vis[102];

void dfs(int x)
{
	if(vis[x])
		return;
	vis[x]=1;
	printf("%d ",x);
	for(int i=0;i<n;i++)
		if(a[x][i])
			dfs(i);
}

void bfs(int x)
{
	int Q[505],head=0,tail=0;
	Q[0]=x;
	while(head<=tail)
	{
		x=Q[head++];
		if(vis[x])
			continue;
		vis[x]=1;
		printf("%d ",x);
		for(int i=0;i<n;i++)
			if(a[x][i] && !vis[i])
				Q[++tail]=i;
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		a[u][v]=a[v][u]=1;
	}
	int t;
	scanf("%d",&t);
	dfs(0);putchar('\n');
	memset(vis,0,sizeof(vis));bfs(0);putchar('\n');
	for(int i=0;i<n;i++)
		a[i][t]=a[t][i]=0;
	memset(vis,0,sizeof(vis));dfs(0);putchar('\n');
	memset(vis,0,sizeof(vis));bfs(0);
	return 0;
}