#include<stdio.h>
#include<string.h>

double tokens[30];
char expression[256];
//===start of stack zone===//
char op[200];int top_op;
double num[200];int top_num;
//====end of stack zone====//

void print(char *s)
{
	int n=strlen(s);
	--n;
	for(int i=0;i<n;i+=2)
		printf("%.2lf ",tokens[s[i]-'a']);
	printf("%.2lf\n",tokens[s[n]-'a']);
}

void gen_expression(char *s)
{
	int p=0,q=0;
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
				expression[q++]=k;
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
				expression[q++]=k;
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
				expression[q++]=k;
				--top_op;
			}
			op[top_op++]=s[p];
			break;
		default:
			while((s[p]>='0' && s[p]<='9') || (s[p]>='a' && s[p]<='z'))
				expression[q++]=s[p++];
			expression[q++]=' ';
			p--;
		}
		p++;
	}
	while(top_op)
		expression[q++]=op[--top_op];
	expression[q]='\0';
}

double calc()
{
	//printf("%s\n",expression);
	int p=0,t=0;
	int istoken=0;
	double r;
	while(expression[p])
	{
		switch(expression[p])
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
			if(istoken)
			{
				num[top_num++]=r;
				istoken=0;
			}
			else
			{
				num[top_num++]=t;
				t=0;
			}
			break;
		default:
			if(expression[p]>='a' && expression[p]<='z')
			{
				r=tokens[expression[p]-'a'];
				istoken=1;
			}
			else
				t=t*10+expression[p]-'0';
		}
		p++;
	}
	return num[--top_num];
}

int main()
{
	char line[205];
	while(1)
	{
		gets(line);
		if(strcmp("exit",line)==0)
			break;
		if(strlen(line)>5 && strncmp("print",line,5)==0)
			print(line+6);
		else if(strlen(line)>2)
		{
			gen_expression(line+2);
			tokens[line[0]-'a']=calc();
		}
	}
	return 0;
}