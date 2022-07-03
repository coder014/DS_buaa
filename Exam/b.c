#include<stdio.h>
#include<stdlib.h>

typedef struct _T {
	struct _T *l,*r;
	int v,cnt;
}T;

T *bst;
int total,anscnt,ansv;

T *insert(T *tree, int x)
{
	if(!tree)
	{
		tree=(T*)malloc(sizeof(T));
		tree->v=x;
		tree->cnt=1;
		tree->l=tree->r=NULL;
		return tree;
	}
	++total;
	if(x == tree->v)
		++(tree->cnt);
	else if(x < tree->v)
		tree->l=insert(tree->l,x);
	else
		tree->r=insert(tree->r,x);
	return tree;
}

void search(T *tree)
{
	printf("%d ",tree->v);
	if(tree->v == ansv)
		return;
	else if(ansv < tree->v)
		search(tree->l);
	else
		search(tree->r);
}

void dfs(T *tree)
{
	if(!tree)
		return;
	if(tree->cnt > anscnt)
	{
		anscnt=tree->cnt;
		ansv=tree->v;
	}
	dfs(tree->l);
	dfs(tree->r);
}

int main()
{
	int n;
	scanf("%d",&n);
	while(n--)
	{
		int t;
		scanf("%d",&t);
		bst=insert(bst,t);
	}
	printf("%d\n",total);
	dfs(bst);search(bst);
	return 0;
}