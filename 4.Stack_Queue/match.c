#include<stdio.h>
#include<malloc.h>

char ans[512];
int anscnt;

typedef struct _DATATYPE {
	char c;
	int l;
} DATATYPE;
typedef struct _Stack {
	int STACKSIZE;
	DATATYPE *_s, *top;
} Stack;
Stack *NewStack(int size)
{
	Stack *ret=(Stack*)malloc(sizeof(Stack));
	ret->STACKSIZE=size;
	ret->_s=(DATATYPE *)malloc(size*sizeof(DATATYPE));
	ret->top=ret->_s;
	return ret;
}
void FreeStack(Stack *s)
{
	free(s->_s);
	free(s);
}
int PushStack(Stack *s, DATATYPE x)
{
	if((s->top)-(s->_s)>=(s->STACKSIZE))
		return 1;
	*((s->top)++)=x;
	return 0;
}
int IsEmptyStack(Stack *s)
{
	return (s->top)<=(s->_s);
}
int PopStack(Stack *s,DATATYPE *x)
{
	if(IsEmptyStack(s))
		return 1;
	--(s->top);
	if(x)
		*x=*(s->top);
	return 0;
}

int main()
{
	freopen("example.c","r",stdin);
	int linenum=0,innote=0;
	char s[512];
	Stack *S=NewStack(512);
	while(gets(s))
	{
		int p=0;
		++linenum;
		while(s[p]!='\0')
		{
			if(innote)
			{
				if(s[p]=='*' && s[p+1]=='/')
				{
					++p;
					innote=0;
				}
			}
			else
			{
				DATATYPE t;
				if(s[p]=='/' && s[p+1]=='/')
					break;
				else if(s[p]=='/' && s[p+1]=='*')
				{
					++p;
					innote=1;
				}
				else if(s[p]=='\'')
					while(s[++p]!='\'');
				else if(s[p]=='\"')
					while(s[++p]!='\"');
				else if(s[p]=='(')
				{
					t.c='(',t.l=linenum;
					PushStack(S,t);
					ans[anscnt++]='(';
				}
				else if(s[p]=='{')
				{
					if(!IsEmptyStack(S))
					{
						t=*((S->top)-1);
						if(t.c=='(')
						{
							printf("without maching \'(\' at line %d",t.l);
							return 0;
						}
					}
					t.c='{',t.l=linenum;
					PushStack(S,t);
					ans[anscnt++]='{';
				}
				else if(s[p]==')')
				{
					if(IsEmptyStack(S))
					{
						printf("without maching \')\' at line %d",linenum);
						return 0;
					}
					t=*((S->top)-1);
					if(t.c!='(')
					{
						printf("without maching \')\' at line %d",linenum);
						return 0;
					}
					PopStack(S,NULL);
					ans[anscnt++]=')';
				}
				else if(s[p]=='}')
				{
					if(IsEmptyStack(S))
					{
						printf("without maching \'}\' at line %d",linenum);
						return 0;
					}
					t=*((S->top)-1);
					if(t.c!='{')
					{
						printf("without maching \'}\' at line %d",linenum);
						return 0;
					}
					PopStack(S,NULL);
					ans[anscnt++]='}';
				}
			}
			++p;
		}
	}
	if(!IsEmptyStack(S))
	{
		DATATYPE t;
		PopStack(S,&t);
		printf("without maching \'%c\' at line %d",t.c,t.l);
	}
	else
		puts(ans);
	return 0;
}