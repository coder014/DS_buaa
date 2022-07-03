//文件压缩-Huffman实现
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode {					//Huffman树结构
	char c;		
	int weight;					//树节点权重，叶节点为字符和它的出现次数
	struct tnode *left,*right;
} ; 
int Ccount[128]={0};			//存放每个字符的出现次数，如Ccount[i]表示ASCII值为i的字符出现次数 
struct tnode *Root=NULL; 		//Huffman树的根节点
char HCode[128][MAXSIZE]={{0}}; //字符的Huffman编码，如HCode['a']为字符a的Huffman编码（字符串形式） 
int Step=0;						//实验步骤 
FILE *Src, *Obj;
	
void statCount();				//步骤1：统计文件中字符频率
void createHTree();				//步骤2：创建一个Huffman树，根节点为Root 
void makeHCode();				//步骤3：根据Huffman树生成Huffman编码
void atoHZIP(); 				//步骤4：根据Huffman编码将指定ASCII码文本文件转换成Huffman码文件

void print1();					//输出步骤1的结果
void print2(struct tnode *p);	//输出步骤2的结果 
void print3();					//输出步骤3的结果
void print4();					//输出步骤4的结果

int main()
{
	if((Src=fopen("input.txt","r"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "input.txt");
		return 1;
	}
	if((Obj=fopen("output.txt","w"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "output.txt");
		return 1;
	}
	scanf("%d",&Step);					//输入当前实验步骤 
	
	statCount();						//实验步骤1：统计文件中字符出现次数（频率）
	(Step==1) ? print1(): 1; 			//输出实验步骤1结果	
	createHTree();						//实验步骤2：依据字符频率生成相应的Huffman树
	(Step==2) ? print2(Root): 2; 		//输出实验步骤2结果	
	makeHCode();				   		//实验步骤3：依据Root为树的根的Huffman树生成相应Huffman编码
	(Step==3) ? print3(): 3; 			//输出实验步骤3结果
	(Step>=4) ? atoHZIP(),print4(): 4; 	//实验步骤4：据Huffman编码生成压缩文件，并输出实验步骤4结果	

	fclose(Src);
	fclose(Obj);

    return 0;
} 

void statCount()
{
	int c;
	while((c=fgetc(Src))!=EOF)
		++Ccount[c&127];
	Ccount[0]=1;
}

int mycmp(const void *pa, const void *pb)
{
	struct tnode *a=*(struct tnode**)pa,*b=*(struct tnode**)pb;
	if(a->weight==b->weight)
		return (a->c > b->c)?-1:1;
	return (a->weight > b->weight)?-1:1;
}
void createHTree()
{
	struct tnode *F[256];
	int Fcnt=0;
	for(int i=0;i<128;i++)
		if(Ccount[i])
		{
			Root=(struct tnode *)malloc(sizeof(struct tnode));
			Root->c=i;
			Root->weight=Ccount[i];
			Root->left=Root->right=NULL;
			F[Fcnt++]=Root;
		}
	qsort(F,Fcnt,sizeof(struct tnode *),mycmp);
	while(Fcnt>1)
	{
		Root=(struct tnode *)malloc(sizeof(struct tnode));
		Root->left=F[Fcnt-1];
		Root->right=F[Fcnt-2];
		Root->weight=F[Fcnt-1]->weight + F[Fcnt-2]->weight;
		F[(--Fcnt)-1]=Root;
		for(int i=Fcnt-1;i>0;i--)
			if(F[i]->weight >= F[i-1]->weight)
			{
				struct tnode *t=F[i];
				F[i]=F[i-1];
				F[i-1]=t;
			}
			else break;
	}
	Root=F[0];
}

void dfs(struct tnode *p, char *s)
{
	if(!p)
		return;
	if((p->left==NULL)&&(p->right==NULL))
	{
		strcpy(HCode[p->c],s);
		return;
	}
	int len=strlen(s);
	char *new_s=(char*)malloc(len+2);
	strcpy(new_s,s);
	new_s[len+1]='\0';
	new_s[len]='0';
	dfs(p->left,new_s);
	new_s[len]='1';
	dfs(p->right,new_s);
	free(new_s);
}
void makeHCode()
{
	dfs(Root,"\0");
} 

void atoHZIP()
{
	int c,len=0;
	unsigned char hc=0;
	fseek(Src,0,SEEK_SET);
	while((c=fgetc(Src))!=EOF)
	{
		for(int i=0;HCode[c][i]!='\0';i++,len=(len+1)%8)
		{
			hc=(hc<<1)|(HCode[c][i]-'0');
			if((len+1)%8==0)
			{
				fputc(hc,Obj);
				printf("%x",hc);
			}
		}
	}
	for(int i=0;HCode[0][i]!='\0';i++,len=(len+1)%8)
	{
		hc=(hc<<1)|(HCode[0][i]-'0');
		if((len+1)%8==0)
		{
			fputc(hc,Obj);
			printf("%x",hc);
		}
	}
	if(len%8)
	{
		hc<<=(8-len);
		fputc(hc,Obj);
		printf("%x",hc);
	}
}

void print1()
{
	int i;
	printf("NUL:1\n");
	for(i=1; i<128; i++)
		if(Ccount[i] > 0)
			printf("%c:%d\n", i, Ccount[i]);
}

void print2(struct tnode *p)
{
	if(p != NULL){
		if((p->left==NULL)&&(p->right==NULL)) 
			switch(p->c){
				case 0: printf("NUL ");break;
				case ' ':  printf("SP ");break;
				case '\t': printf("TAB ");break;
				case '\n':  printf("CR ");break;
				default: printf("%c ",p->c); break;
			}
		print2(p->left);
		print2(p->right);
	}
}

void print3()
{
	int i;
	
	for(i=0; i<128; i++){
		if(HCode[i][0] != 0){
			switch(i){
				case 0: printf("NUL:");break;
				case ' ':  printf("SP:");break;
				case '\t': printf("TAB:");break;
				case '\n':  printf("CR:");break;
				default: printf("%c:",i); break;
			}
			printf("%s\n",HCode[i]);
		}
	}
} 

void print4()
{
	long int in_size, out_size;
	
	fseek(Src,0,SEEK_END);
	fseek(Obj,0,SEEK_END);
	in_size = ftell(Src);
	out_size = ftell(Obj);
	
	printf("\n原文件大小：%ldB\n",in_size);
	printf("压缩后文件大小：%ldB\n",out_size);
	printf("压缩率：%.2f%%\n",(float)(in_size-out_size)*100/in_size);
}
