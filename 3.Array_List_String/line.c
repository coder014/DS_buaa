#include<stdio.h>
#include<stdlib.h>

typedef struct _line {
	int x1,x2,y1,y2;
} line;

line a[105];
int n,ansx,ansy,ans=0;

int cmp(const void *pa, const void *pb)
{
	line *a=(line*)pa,*b=(line*)pb;
	if(a->x1 == b->x1)
		return a->y1 < b->y1 ?-1:1;
	return a->x1 < b->x1 ?-1:1;
}

int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d%d%d%d",&a[i].x1,&a[i].y1,&a[i].x2,&a[i].y2);
	qsort(a,n,sizeof(line),cmp);
	for(int i=0;i<n;i++)
	{
		int tans=1,tx=a[i].x2,ty=a[i].y2;
		for(int j=0;j<n;j++)
		{
			if(i==j) continue;
			if(tx==a[j].x1 && ty==a[j].y1)
			{
				tx=a[j].x2;
				ty=a[j].y2;
				tans++;
			}
		}
		if(tans>ans)
		{
			ans=tans;
			ansx=a[i].x1;
			ansy=a[i].y1;
		}
	}
	printf("%d %d %d",ans,ansx,ansy);
	return 0;
}