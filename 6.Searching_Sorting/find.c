#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define NHASH 3001
#define MULT  37

typedef struct _Link {
	int index;
	struct _Link *next;
} Link;

typedef struct _Table {
	int cnt;
	Link *l;
} Table;

Table table[NHASH];
char words[3505][22],s[22];
int word_cnt,cmp;

unsigned hash(char *str)
{
	unsigned h=0;
	char *p;
	for(p=str;*p!='\0';p++)
		h=MULT*h+*p;
	return h%NHASH;
}

int Seq()
{
	int i=0;
	while(i<=word_cnt)
	{
		++cmp;
		int t=strcmp(words[i++],s);
		if(t==0)
			return 1;
		else if(t>0)
			return 0;
	}
	return 0;
}

int Bin(int l,int r)
{
	int m,t;
	while(l<=r)
	{
		++cmp;
		m=(l+r)>>1;
		t=strcmp(words[m],s);
		if(t>0)
			r=m-1;
		else if(t<0)
			l=m+1;
		else
			return 1;
	}
	return 0;
}

int Idx()
{
	int st=-1;
	while(words[++st][0]!=s[0] && st<word_cnt);
	if(st>=word_cnt)
		return 0;
	int ed=st;
	while(words[++ed][0]==s[0]);
	return Bin(st,ed-1);
}

int Hash()
{
	int h;
	for(int i=0;i<word_cnt;i++)
	{
		h=hash(words[i]);
		table[h].cnt++;
		Link *tt=(Link*)malloc(sizeof(Link));
		tt->index=i;
		if(table[h].cnt>1)
		{
			tt->next=table[h].l->next;
			table[h].l->next=tt;
		}
		else
		{
			tt->next=NULL;
			table[h].l=tt;
		}
	}

	h=hash(s);
	if(!table[h].cnt)
		return 0;
	Link *p=table[h].l;
	while(p)
	{
		++cmp;
		int t=strcmp(words[p->index],s);
		if(t==0)
			return 1;
		else if(t>0)
			return 0;
		p=p->next;
	}
	return 0;
}

int main()
{
	FILE *in=fopen("dictionary3000.txt","r");
	while(fscanf(in,"%s",words[word_cnt++])!=EOF); --word_cnt;
	
	int op,ret;
	scanf("%s %d",s,&op);
	switch(op)
	{
	case 1: ret=Seq(); break;
	case 2: ret=Bin(0,word_cnt-1); break;
	case 3: ret=Idx(); break;
	case 4: ret=Hash(); break;
	}
	printf("%d %d",ret,cmp);
	return 0;
}