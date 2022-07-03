#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct _data {
	char s[20];
	int h;
} data;
data a[20];
char base[20];
int cmp(const void *pa,const void *pb)
{
	const data *a=(const data*)pa,*b=(const data*)pb;
	if(a->h==b->h)
		return strcmp(a->s,b->s);
	return a->h - b->h;
}

int main()
{
	int n,len;
	scanf("%d",&n);
	scanf("%s",base);
	--n;len=strlen(base);
	for(int i=0;i<n;i++)
	{
		scanf("%s",&a[i].s);
		for(int j=0;j<len;j++)
			if(a[i].s[j]!=base[j])
				++a[i].h;
	}
	qsort(a,n,sizeof(data),cmp);
	for(int i=0;i<n;i++)
		printf("%s %s %d\n",base,a[i].s,a[i].h);
	return 0;
}