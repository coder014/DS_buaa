#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct _node {
	int cnt;
	struct _node *next[26];
} node;
node *Trie;
char s[10005];

void dfs(node *p,int len)
{
	if(p->cnt)
		printf("%s %d\n",s,p->cnt);
	s[len+1]='\0';
	for(int i=0;i<26;i++)
	{
		if(!(p->next[i]))
			continue;
		s[len]=i+'a';
		dfs(p->next[i], len+1);
	}
	s[len]='\0';
}

int main()
{
	freopen("article.txt","r",stdin);
	Trie=(node*)calloc(1,sizeof(node));
	char c;
	node *p=Trie;
	while((c=getchar())!=EOF)
	{
		if(c>='A' && c<='Z')
			c=c-'A'+'a';
		if(c<'a' || c>'z')
		{
			if(p!=Trie)
			{
				(p->cnt)++;
				p=Trie;
			}
			continue;
		}
		if(!(p->next[c-'a']))
			p->next[c-'a']=(node*)calloc(1,sizeof(node));
		p=p->next[c-'a'];
	}
	if(p!=Trie)
		(p->cnt)++;
	dfs(Trie,0);
	return 0;
}