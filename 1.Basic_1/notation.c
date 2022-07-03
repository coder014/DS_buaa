#include<stdio.h>
#include<string.h>

char s[105],num[105];

int main()
{
	int digit;
	gets(s);
	for(int i=0,j=0;s[i]!='\0';i++)
		if(s[i]!='.')
			num[j++]=s[i];
		else
			digit=i;
	int p=0;
	while(num[p]=='0')
		p++;
	if(num[p+1])
		printf("%c.%se%d",num[p],num+p+1,digit-p-1);
	else
		printf("%ce%d",num[p],digit-p-1);
	return 0;
}