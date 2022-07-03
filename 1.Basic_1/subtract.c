#include<stdio.h>
#include<string.h>

char A[85],B[85];
int a[85],b[85],lena,lenb;

int cmp()
{
	int p=0;
	if(strlen(A)==strlen(B))
	{
		while(A[p]!='\0')
			if(A[p]==B[p])
				p++;
			else
				return A[p]>B[p];
		return -1;
	}
	return strlen(A)>=strlen(B);
}

int main()
{
	scanf("%s\n%s",&A,&B);
	int tcmp=cmp();
	if(tcmp==-1)
	{
		puts("0");
		return 0;
	}
	else if(tcmp==0)
	{
		lena=strlen(B),lenb=strlen(A);
		for(int i=0;i<lena;i++)
			a[i]=B[i]-'0';
		for(int i=lena-lenb;i<lena;i++)
			b[i]=A[i-lena+lenb]-'0';
		putchar('-');
	}
	else
	{
		lena=strlen(A),lenb=strlen(B);
		for(int i=0;i<lena;i++)
			a[i]=A[i]-'0';
		for(int i=lena-lenb;i<lena;i++)
			b[i]=B[i-lena+lenb]-'0';
	}
	for(int i=0;i<lena;i++)
			a[i]-=b[i];
	for(int i=lena-1;i;i--)
		if(a[i]<0)
		{
			a[i]+=10;
			a[i-1]--;
		}
	int p=0;
	while(!a[p])
		p++;
	for(;p<lena;p++)
		putchar(a[p]+'0');
	return 0;
}