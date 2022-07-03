#include<stdio.h>
#include<malloc.h>
#include<string.h>

char s[520];
typedef struct _DATATYPE {
	int op,pos;
	char str[128];
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
int PushStack(Stack *s, DATATYPE *x)
{
	if((s->top)-(s->_s)>=(s->STACKSIZE))
		return 1;
	*((s->top)++)=*x;
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
	*x=*(--(s->top));
	return 0;
}

int main()
{
	Stack *S=NewStack(25);
	int n;
	DATATYPE t;
	char ss[128];
	gets(s);
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d%d%s",&t.op,&t.pos,&t.str);
		PushStack(S,&t);
	}
	while(1)
	{
		scanf("%d", &n);
		if(n==-1)
		{
			puts(s);
			return 0;
		}
		else if(n==1)
		{
			t.op=n;
			scanf("%d%s",&t.pos,&t.str);
			PushStack(S,&t);
			strcpy(ss,s+t.pos);
			strcpy(s+t.pos,t.str);
			strcat(s,ss);
		}
		else if(n==2)
		{
			t.op=n;
			scanf("%d%d",&t.pos,&n);
			n=n<strlen(s+t.pos)?n:strlen(s+t.pos);
			strncpy(t.str,s+t.pos,n);
			t.str[n]='\0';
			PushStack(S,&t);
			strcpy(ss,s+t.pos+n);
			strcpy(s+t.pos,ss);
		}
		else
		{
			if(IsEmptyStack(S))
				continue;
			PopStack(S,&t);
			if(t.op==1)
			{
				n=strlen(t.str);
				strcpy(ss,s+t.pos+n);
				strcpy(s+t.pos,ss);
			}
			else
			{
				strcpy(ss,s+t.pos);
				strcpy(s+t.pos,t.str);
				strcat(s,ss);
			}
		}
	}
	return 0;
}