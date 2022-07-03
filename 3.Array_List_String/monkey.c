#include<stdio.h>

int vis[100005];

int main()
{
	int n,m,q;
	int cnt=0,ctr=0;
	scanf("%d%d%d",&n,&m,&q);
	q=(q+n-1)%n;
	do
	{
		if(++q > n)
			q=1;
		if(!vis[q])
			ctr++;
		if(ctr==m)
		{
			ctr=0;
			vis[q]=1;
			cnt++;
		}
	}while(cnt!=n);
	printf("%d",q);
	return 0;
}