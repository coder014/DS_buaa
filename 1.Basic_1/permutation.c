#include<stdio.h>
int n;
int ans[15],vis[15];

void perm(int d)
{
	if(d==n)
	{
		for(int i=1;i<n;i++)
			printf("%d ",ans[i]);
		for(int i=1;i<=n;i++)
			if(!vis[i])
			{
				printf("%d\n",i);
				return;
			}
	}
	for(int i=1;i<=n;i++)
		if(!vis[i])
		{
			vis[i]=1;
			ans[d]=i;
			perm(d+1);
			vis[i]=0;
		}
}

int main()
{
	scanf("%d",&n);
	perm(1);
	return 0;
}