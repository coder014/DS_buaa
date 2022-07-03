#include <stdio.h>

int a[25][25];
const int dx[4]={1,0,1,1};
const int dy[4]={0,1,1,-1};

int check(int x,int y)
{
	for(int i=0;i<4;i++)
	{
		int cnt=0;
		for(int j=1;j<4;j++)
		{
			int tx=x+dx[i]*j,ty=y+dy[i]*j;
			if(tx>0 && tx<=19 && ty>0 && ty<=19)
			{
				if(a[tx][ty]==a[x][y])
					cnt++;
				else break;
			}
			else break;
		}
		if(cnt==3)
		{
			int tx=x-dx[i],ty=y-dy[i];
			if(tx>0 && tx<=19 && ty>0 && ty<=19 && a[tx][ty]==0)
				return 1;
			tx=x+dx[i]*4;ty=y+dy[i]*4;
			if(tx>0 && tx<=19 && ty>0 && ty<=19 && a[tx][ty]==0)
				return 1;
		}
	}
	return 0;
}

int main()  
{
	for(int i=1;i<=19;i++)
		for(int j=1;j<=19;j++)
			scanf("%d",&a[i][j]);
	for(int i=1;i<=19;i++)
		for(int j=1;j<=19;j++)
		{
			if(!a[i][j])
				continue;
			if(check(i,j))
			{
				printf("%d:%d,%d\n",a[i][j],i,j);
				return 0;
			}
		}
	puts("No");
	return 0;
} 