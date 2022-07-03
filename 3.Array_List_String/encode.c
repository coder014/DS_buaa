#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct _node {
	char c;
	struct _node *next;
} node;

char s[35],code[128],mapping[128];
int vis[128];
node *head;

node *getpre(node *p)
{
	node *pre=p;
	while(pre->next != p)
		pre=pre->next;
	return pre;
}

void uniq()
{
	int p=0;
	for(int i=0;s[i]!='\0';i++)
		if(!vis[s[i]])
		{
			code[p++]=s[i];
			vis[s[i]]=1;
		}
	for(int i=32;i<=126;i++)
		if(!vis[i])
			code[p++]=i;
}

void gen()
{
	head=(node*)malloc(sizeof(node));
	head->c=code[0];
	node *p=head;
	for(int i=1;i<95;i++)
	{
		p->next=(node*)malloc(sizeof(node));
		p=p->next;
		p->c=code[i];
	}
	p->next=head;
	char headc=head->c;
	while(head->next != head)
	{
		char pre=head->c;
		p=getpre(head);
		p->next=head->next;
		free(head);
		head=p->next;
		for(int i=0;i<pre-1;i++)
			head=head->next;
		mapping[pre]=head->c;
	}
	mapping[head->c]=headc;
	free(head);
}

int main()  
{
	gets(s);
	uniq();
	gen();
	freopen("in.txt","r",stdin);
	freopen("in_crpyt.txt","w",stdout);
	char c;
	while((c=getchar()) != EOF)
	{
		if(c>=32 && c<=126)
			putchar(mapping[c]);
		else
			putchar(c);
	}
	return 0;
} 