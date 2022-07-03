#include<stdio.h>
#include<malloc.h>

#define DATATYPE int

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
	*x=*(--(s->top));
	return 0;
}

int main()
{
	int t=0,x;
	Stack *s=NewStack(100);
	while(t!=-1)
	{
		scanf("%d",&t);
		if(t==1)
		{
			scanf("%d",&t);
			x=PushStack(s,t);
			if(x)
				printf("error ");
		}
		else if(t==0)
		{
			x=PopStack(s,&t);
			if(x)
				printf("error ");
			else
				printf("%d ",t);
		}
	}
	return 0;
}