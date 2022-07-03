#include<stdio.h>
#include<string.h>

char s[10005];

int gettype(char c)
{
	if(c>='0' && c<='9')
		return 0;
	if(c>='A' && c<='Z')
		return 1;
	if(c>='a' && c<='z')
		return 2;
	return -1;
}

int main()
{
	gets(s);
	int len=strlen(s),i=1;
	putchar(s[0]);
	while(i<len)
	{
		if(s[i]=='-')
		{
			if(gettype(s[i-1])==gettype(s[i+1]) && s[i-1]<s[i+1])
				for(char c=s[i-1]+1;c<s[i+1];c++)
					putchar(c);
			else
				putchar('-');
		}
		else
			putchar(s[i]);
		i++;
	}
	if(s[len-1]=='-')
			putchar('-');
	return 0;
}