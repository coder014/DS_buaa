#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _book {
	char title[55];
	char author[25];
	char publisher[35];
	char date[15];
} book;

book tbook,a[502];
int cnt;

void insback()
{
	int i;
	for(i=0;i<cnt && strcmp(a[i].title,tbook.title)<0;i++);
	for(int j=cnt-1;j>=i;j--)
	{
		strcpy(a[j+1].title,a[j].title);
		strcpy(a[j+1].author,a[j].author);
		strcpy(a[j+1].publisher,a[j].publisher);
		strcpy(a[j+1].date,a[j].date);
	}
	strcpy(a[i].title,tbook.title);
	strcpy(a[i].author,tbook.author);
	strcpy(a[i].publisher,tbook.publisher);
	strcpy(a[i].date,tbook.date);
	++cnt;
}
void search(const char *key)
{
	for(int i=0;i<cnt;i++)
		if(strstr(a[i].title,key) != NULL)
			printf("%-50s%-20s%-30s%-10s\n",a[i].title,a[i].author,a[i].publisher,a[i].date);
}
void del(const char *key)
{
	for(int i=cnt-1;i>=0;i--)
		if(strstr(a[i].title,key) != NULL)
		{
			for(int j=i;j<cnt;j++)
			{
				strcpy(a[j].title,a[j+1].title);
				strcpy(a[j].author,a[j+1].author);
				strcpy(a[j].publisher,a[j+1].publisher);
				strcpy(a[j].date,a[j+1].date);
			}
			cnt--;
		}
}

int cmp(const void *ta, const void *tb)
{
	book *a=(book*)ta,*b=(book*)tb;
	return strcmp(a->title,b->title);
}

int main()  
{
	FILE *fpin,*fpout;
	fpin = fopen("books.txt","r");
	fpout = fopen("ordered.txt","w");
	while(fscanf(fpin,"%s%s%s%s",tbook.title,tbook.author,tbook.publisher,tbook.date) != EOF)
	{
		strcpy(a[cnt].title,tbook.title);
		strcpy(a[cnt].author,tbook.author);
		strcpy(a[cnt].publisher,tbook.publisher);
		strcpy(a[cnt++].date,tbook.date);
	}
	qsort(a,cnt,sizeof(book),cmp);
	int op;char t[55];
	while(1)
	{
		scanf("%d",&op);
		if(op==1)
		{
			scanf("%s%s%s%s",tbook.title,tbook.author,tbook.publisher,tbook.date);
			insback();
		}
		else if(op==2)
		{
			scanf("%s",t);
			search(t);
		}
		else if(op==3)
		{
			scanf("%s",t);
			del(t);
		}
		else
		{
			for(int i=0;i<cnt;i++)
				fprintf(fpout,"%-50s%-20s%-30s%-10s\n",a[i].title,a[i].author,a[i].publisher,a[i].date);
			break;
		}
	}
	return 0;
} 