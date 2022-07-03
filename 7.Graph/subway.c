#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct _Edge {
	int w,id;
} Edge;
typedef struct _Node {
	char name[16];
	int isc;
} Node;

int n,path[512];
Node st[512];
Edge e[512][512];

int getStation(char *s,int isc)
{
	for(int i=0;i<n;i++)
		if(strcmp(s,st[i].name)==0)
			return i;
	strcpy(st[n].name,s);
	st[n].isc=isc;
	return n++;
}

void addE(int u,int v,int id)
{
	e[u][v].w=e[v][u].w=1;
	e[u][v].id=e[v][u].id=id;
}

void dijkstra(int u)
{
	char vis[512]={0};
	int d[512];
	for(int i=0;i<n;i++)
	{
		d[i]=e[u][i].w;
		path[i]=u;
	}
	d[u]=0;  
	vis[u]=1;  
	for(int i=1;i<n;i++)
	{
		int dmin=0x3f3f3f3f,v;
		for(int j=0;j<n;j++)
			if(!vis[j] && d[j]<dmin)
			{
				v=j; 
				dmin=d[v];
			}
		vis[v]=1;
		for(int j=0;j<n;j++)
			if(!vis[j] && (dmin+e[v][j].w<d[j]))
			{
				d[j]=dmin+e[v][j].w;
				path[j]=v;
			}
	}
}

int main()
{
	FILE *in = fopen("bgstations.txt","r");
	int lines,u,v;
	fscanf(in,"%d",&lines);
	memset(e,0x3f,sizeof(e));
	while(lines--)
	{
		int id,t,isc;
		char name[16];
		fscanf(in,"%d%d",&id,&t);
		u=-1;
		while(t--)
		{
			fscanf(in,"%s%d",name,&isc);
			v=getStation(name,isc);
			if(u>=0)
				addE(u,v,id);
			u=v;
		}
	}
	char start[16],end[16];
	scanf("%s%s",start,end);
	u=getStation(end,0);v=getStation(start,0);
	dijkstra(u);
	int cnt=0,id=e[v][path[v]].id;
	char *last;
	printf("%s",st[v].name);
	while(v!=u)
	{
		if(e[v][path[v]].id!=id)
		{
			printf("-%d(%d)-%s",id,cnt,last);
			id=e[v][path[v]].id;
			cnt=0;
		}
		v=path[v];
		if(st[v].isc)
			last=st[v].name;
		++cnt;
	}
	printf("-%d(%d)-%s",id,cnt,st[v].name);
	return 0;
}