#include<stdio.h>
#include<string.h>

double num[1005];
char op[1005];
char s[2005];
int top_num,top_op;

void revert()
{
	int p=0,q=0;
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

int main()
{
	gets(s);
	revert();
	int p=0,t=0;
	while(s[p])
	{
		switch(s[p])
		{
		case '+':
			num[top_num-2]+=num[top_num-1];
			--top_num;
			break;
		case '-':
			num[top_num-2]-=num[top_num-1];
			--top_num;
			break;
		case '*':
			num[top_num-2]*=num[top_num-1];
			--top_num;
			break;
		case '/':
			num[top_num-2]/=num[top_num-1];
			--top_num;
			break;
		case ' ':
			num[top_num++]=t;
			t=0;
			break;
		default:
			if(s[p]>='0' && s[p]<='9')
			t=t*10+s[p]-'0';
		}
		p++;
	}
	printf("%.2lf",num[0]);
	return 0;
}