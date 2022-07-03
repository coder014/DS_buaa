#include <stdio.h>
#include <string.h>

char s[128],code[32];
int vis[32];

void uniq()
{
	int p=0;
	for(int i=0;s[i]!='\0';i++)
		if(!vis[s[i]-'a'])
		{
			code[p++]=s[i];
			vis[s[i]-'a']=1;
		}
	for(int i=25;i>=0;i--)
		if(!vis[i])
			code[p++]=i+'a';
}

int main()  
{
	gets(s);
	uniq();
	freopen("encrypt.txt","r",stdin);
	freopen("output.txt","w",stdout);
	while(gets(s) != NULL)
	{
		for(int i=0;s[i]!='\0';i++)
			if(s[i]>='a' && s[i]<='z')
				putchar(code[s[i]-'a']);
			else
				putchar(s[i]);
		putchar('\n');
	}
	return 0;
} 