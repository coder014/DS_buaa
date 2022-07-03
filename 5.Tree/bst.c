#include<stdio.h>
#include<stdlib.h>

typedef struct _TREE {
	int d;
	struct _TREE *l,*r;
} Tree;

Tree *Root;

void Insert(Tree *T, int x)
{
	Tree **p;
	if(x < T->d)
		p=&(T->l);
	else
		p=&(T->r);
	if(!(*p))
	{
		*p=(Tree*)malloc(sizeof(Tree));
		(*p)->l=(*p)->r=NULL;
		(*p)->d=x;
	}
	else
		Insert(*p,x);
}

void dfs(Tree *T,int depth)
{
	if(!T)
		return;
	if(!(T->l || T->r))
		printf("%d %d\n",T->d,depth);
	else
	{
		dfs(T->l,depth+1);
		dfs(T->r,depth+1);
	}
}

int main()
{
	int n,t;
	scanf("%d",&n);
	scanf("%d",&t);
	Root=(Tree*)malloc(sizeof(Tree));
	Root->l=Root->r=NULL;
	Root->d=t;
	--n;
	while(n--)
	{
		scanf("%d",&t);
		Insert(Root,t);
	}
	dfs(Root,1);
	return 0;
}