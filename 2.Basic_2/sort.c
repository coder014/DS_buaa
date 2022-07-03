#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef long long ll;

typedef struct _CON {
	char name[25];
	ll num;
	int _n;
} con;
con a[105],tcon;
int cnt;

int cmp(const void *ta, const void *tb)
{
	con *a=(con*)ta,*b=(con*)tb;
	int ret=strcmp(a->name, b->name);
	if(ret == 0)
		return (a->_n) - (b->_n);
	return ret;
}

int check()
{
	int t=0;
	for(int i=0;i<cnt;i++)
		if(strcmp(tcon.name, a[i].name) == 0)
		{
			t++;
			if(tcon.num == a[i].num)
				return -1;
		}
	return t;
}

int main()  
{
	int n;
	scanf("%d",&n);
	while(n--)
	{
		scanf("%s%lld",&tcon.name,&tcon.num);
		int t=check();
		if(t==-1)
			continue;
		strcpy(a[cnt].name,tcon.name);
		a[cnt].num = tcon.num;
		a[cnt++]._n = t;
	}
	qsort(a,cnt,sizeof(con),cmp);
	for(int i=0;i<cnt;i++)
		if(a[i]._n)
			printf("%s_%d %lld\n",a[i].name,a[i]._n,a[i].num);
		else
			printf("%s %lld\n",a[i].name,a[i].num);
	return 0;
} 