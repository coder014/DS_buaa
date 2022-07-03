#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _TREE {
	char op;
	int num;
	struct _TREE *l,*r;
} Tree;

char s[2005];
Tree *trees[1000];
int num[2005],top_num,cnttrees;

void revert()
{
	int p=0,q=0,top_op=0;
	char op[1005];
	char t[2005];
	while(s[p])
	{
		char k;
		switch(s[p])
		{
		case '(':
			op[top_op++]='(';
			break;
		case ')':
			k=op[--top_op];
			while(k!='(')
			{
				t[q++]=k;
				k=op[--top_op];
			}
			break;
		case '+':
		case '-':
			while(top_op)
			{
				k=op[top_op-1];
				if(k=='(')
					break;
				t[q++]=k;
				--top_op;
			}
			op[top_op++]=s[p];
			break;
		case '*':
		case '/':
			while(top_op)
			{
				k=op[top_op-1];
				if(k!='*' && k!='/')
					break;
				t[q++]=k;
				--top_op;
			}
			op[top_op++]=s[p];
			break;
		case ' ': break;
		case '=': 
			while(top_op)
				t[q++]=op[--top_op];
			t[q]='\0';
			break;
		default:
			while(s[p]>='0' && s[p]<='9')
				t[q++]=s[p++];
			t[q++]=' ';
			p--;
		}
		p++;
	}
	strcpy(s,t);
}

void insert(char x,int d)
{
	trees[cnttrees++]=(Tree*)malloc(sizeof(Tree));
	trees[cnttrees-1]->op=x;
	trees[cnttrees-1]->num=d;
	if(x=='\0')
		trees[cnttrees-1]->l=trees[cnttrees-1]->r=NULL;
	else
	{
		trees[cnttrees-1]->l=trees[cnttrees-3];
		trees[cnttrees-1]->r=trees[cnttrees-2];
		trees[cnttrees-3]=trees[cnttrees-1];
		cnttrees-=2;
	}
}

int main()
{
	gets(s);
	revert();
	int p=0,t=0;
	//printf("%s\n",s);
	while(s[p])
	{
		switch(s[p])
		{
		case '+':
			insert(s[p],0);
			num[top_num-2]+=num[top_num-1];
			--top_num;
			break;
		case '-':
			insert(s[p],0);
			num[top_num-2]-=num[top_num-1];
			--top_num;
			break;
		case '*':
			insert(s[p],0);
			num[top_num-2]*=num[top_num-1];
			--top_num;
			break;
		case '/':
			insert(s[p],0);
			num[top_num-2]/=num[top_num-1];
			--top_num;
			break;
		case ' ':
			insert('\0',t);
			num[top_num++]=t;
			t=0;
			break;
		default:
			if(s[p]>='0' && s[p]<='9')
			t=t*10+s[p]-'0';
		}
		p++;
	}
	trees[0]->op?printf("%c",trees[0]->op):printf("%d",trees[0]->num);
	if(trees[0]->l)
		trees[0]->l->op?printf(" %c",trees[0]->l->op):printf(" %d",trees[0]->l->num);
	if(trees[0]->r)
		trees[0]->r->op?printf(" %c",trees[0]->r->op):printf(" %d",trees[0]->r->num);
	putchar('\n');
	printf("%d",num[0]);
	return 0;
}