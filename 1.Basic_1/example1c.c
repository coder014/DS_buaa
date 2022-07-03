#include<stdio.h>
#include<string.h>

int stack_n[105],top_n,top_op;
char s[10005],stack_op[105];
void pushn(int x)
{
	stack_n[top_n++]=x;
}
int popn()
{
	return stack_n[--top_n];
}
void pushop(char x)
{
	stack_op[top_op++]=x;
}
int popop()
{
	return stack_op[--top_op];
}

int main()
{
	int num=0;
	gets(s);
	int len=strlen(s),p=0;
	while(p<len)
	{
		if(s[p]==' ')
		{
			p++;
			continue;
		}
		if(s[p]>='0' && s[p]<='9')
		{
			num*=10;
			num+=s[p]-'0';
		}
		else
		{
			pushn(num);num=0;
			if(top_op)
			{
				if(stack_op[top_op-1]=='*')
				{
					pushn(popn()*popn());
					popop();
				}
				else if(stack_op[top_op-1]=='/')
				{
					int b=popn();
					int a=popn();
					pushn(a/b);
					popop();
				}
			}
			if(s[p]!='=')
				pushop(s[p]);
		}
		p++;
	}
	for(int i=0;i<top_op;i++)
	{
		if(stack_op[i]=='+')
			stack_n[0]+=stack_n[i+1];
		else
			stack_n[0]-=stack_n[i+1];
	}
	printf("%d",stack_n[0]);
	return 0;
}