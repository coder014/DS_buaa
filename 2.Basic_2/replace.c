#include <stdio.h>
#include <string.h>
#define TOLOWER(x) ((x)>='A' && (x)<='Z' ? (x)-'A'+'a' : (x))

char s[128];
char pre[32],nxt[32];
int prelen;

char *stristr(const char *s1, const char *s2)
{
	int len=strlen(s2);
	for(int i=0;s1[i]!='\0';i++)
	{
		int j,k;
		for(j=i,k=0; s1[j]!='\0'&&s2[k]!='\0'&& TOLOWER(s1[j])==TOLOWER(s2[k]); j++,k++);
		if(len==k)
			return s1+i;
	}
	return NULL;
}

int main()  
{
	scanf("%s%s",pre,nxt);
	prelen=strlen(pre);
	freopen("filein.txt","r",stdin);
	freopen("fileout.txt","w",stdout);
	while(gets(s) != NULL)
	{
		char *p0=s,*p;
		while((p=stristr(p0,pre)) != NULL)
		{
			for(;p0<p;p0++)
				putchar(*p0);
			printf("%s",nxt);
			p0+=prelen;
		}
		puts(p0);
	}
	return 0;
} 