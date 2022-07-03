#include<stdio.h>
#include<string.h>
typedef struct _List {
	int cnt;
	char name[22];
	char *callees[11];
} List;
List func[102];int nfunc;
char *stack[202];int stop;

int getfunc(const char *s)
{
	int i;
	for(i=0;i<nfunc;i++)
		if(strcmp(func[i].name,s)==0)
			break;
	if(i==nfunc)
	{
		strcpy(func[i].name,s);
		return nfunc++;
	}
	return i;
}

void insert(const char *u,const char *v)
{
	List *caller=func+getfunc(u),*callee=func+getfunc(v);
	for(int i=0;i<caller->cnt;i++)
		if(strcmp(caller->callees[i],callee->name)==0)
			return;
	caller->callees[(caller->cnt)++]=callee->name;
}

int main()
{
	int op;
	char t[22];
	while(1)
	{
		scanf("%d",&op);
		if(op==0)
		{
			if(!(--stop))
				break;
		}
		else
		{
			scanf("%s",t);
			stack[stop++]=func[getfunc(t)].name;
			if(stop<=1)
				continue;
			insert(stack[stop-2],stack[stop-1]);
		}
	}
	for(int i=0;i<nfunc;i++)
	{
		if(!func[i].cnt)
			continue;
		printf("%s:%s",func[i].name,func[i].callees[0]);
		for(int j=1;j<func[i].cnt;j++)
			printf(",%s",func[i].callees[j]);
		putchar('\n');
	}
	return 0;
}