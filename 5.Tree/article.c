#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _TREE {
	char word[16];
	int cnt;
	struct _TREE *l,*r;
} Tree;

Tree *Root;

void Insert(Tree *T, char *x)
{
	if(!T)
	{
		Root=(Tree*)malloc(sizeof(Tree));
		Root->l=Root->r=NULL;
		Root->cnt=1;
		strcpy(Root->word,x);
		return;
	}
	int res=strcmp(T->word,x);
	if(res==0)
	{
		++(T->cnt);
		return;
	}
	Tree **p;
	if(res>0)
		p=&(T->l);
	else
		p=&(T->r);
	if(!(*p))
	{
		*p=(Tree*)malloc(sizeof(Tree));
		(*p)->l=(*p)->r=NULL;
		(*p)->cnt=1;
		strcpy((*p)->word,x);
	}
	else
		Insert(*p,x);
}

void dfs(Tree *T)
{
	if(!T)
		return;
	dfs(T->l);
	printf("%s %d\n",T->word,T->cnt);
	dfs(T->r);
}

int main()
{
	freopen("article.txt","r",stdin);
	char c,buf[20];
	int pbuf=0,inword=0;
	while(scanf("%c",&c)!=EOF)
		if((c>='a' && c<='z')||(c>='A' && c<='Z'))
		{
			inword=1;
			c|=32;
			buf[pbuf++]=c;
		}
		else if(inword)
		{
			inword=0;
			buf[pbuf]='\0';
			Insert(Root,buf);
			pbuf=0;
		}
	if(inword)
	{
		buf[pbuf]='\0';
		Insert(Root,buf);
	}
	printf("%s",Root->word);
	if(Root->r)
	{
		printf(" %s",Root->r->word);
		if(Root->r->r)
			printf(" %s",Root->r->r->word);
	}
	putchar('\n');
	dfs(Root);
	return 0;
}