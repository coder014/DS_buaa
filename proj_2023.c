//#pragma GCC optimize ("O3")
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFSIZE (64*1024*1024)
#define min(a,b) ((a)<(b)?(a):(b))
#define isAlpha(c) (((c)>='a' && (c)<='z')||((c)>='A' && (c)<='Z'))

typedef struct _TRIE {
	struct _TRIE *next[26];
	int cnt;
} Trie;
typedef struct _Document {
	char *name;
	Trie *m;
	int hash[128];
} Document;
typedef struct _Sample {
	char *name;
	Trie *m;
	int hash[128];
	int ids[5][128];
	int cnts[5];
} Sample;
typedef struct _Vector {
	char *name;
	int w;
} Vector;

char *buffer, *buffer1;
int N,M;
Trie *swords, *all;
Document docs[20480];int idcnt;
signed char hash[10000][128];
Vector vec[1048576];int veccnt;
Sample sample;
FILE *out;

inline Trie *InitTrie()
{
	Trie *t=(Trie*)malloc(sizeof(Trie));
	memset(t,0,sizeof(Trie));
	return t;
}
inline char *TrieInsertOrAdd(Trie *t, char *s)
{
	for(;isAlpha(*s);s++)
	{
		*s|=32;
		if(!(t->next[*s-'a']))
			t->next[*s-'a']=InitTrie();
		t=t->next[*s-'a'];
	}
	t->cnt+=1;
	return s;
}
inline char *TrieInsertOrAddInternal(Trie *t, char *s)
{
	for(;*s && *s!='\n';s++)
	{
		if(!(t->next[*s-'a']))
			t->next[*s-'a']=InitTrie();
		t=t->next[*s-'a'];
	}
	t->cnt+=1;
	return s;
}
inline int TrieQuery(Trie *t, char *s)
{
	for(;isAlpha(*s);s++)
	{
		*s|=32;
		if(!(t->next[*s-'a']))
			return 0;
		t=t->next[*s-'a'];
	}
	return t->cnt;
}
inline int TrieQueryInternal(Trie *t, char *s)
{
	for(;*s;s++)
	{
		if(!(t->next[*s-'a']))
			return 0;
		t=t->next[*s-'a'];
	}
	return t->cnt;
}

int cmp(const void* pL, const void* pR)
{
	Vector *L=(Vector*)pL,*R=(Vector*)pR;
	if(L->w == R->w)
		return strcmp(L->name, R->name);
	return L->w > R->w ? -1 : 1;
}

inline void prepare()
{
	buffer=(char*)malloc(BUFSIZE);
	buffer1=(char*)malloc(BUFSIZE);
	char tmp[256];
	swords=InitTrie();
	all=InitTrie();
	FILE *in;
	in=fopen("stopwords.txt", "r");
	setvbuf(in, buffer, _IOFBF, BUFSIZE);
	while(fscanf(in, "%s", tmp)!=EOF) {
		TrieInsertOrAddInternal(swords, tmp);
	}
	in=fopen("hashvalue.txt","r");
	setvbuf(in, buffer, _IOFBF, BUFSIZE);
	for(int i=0; i<N; i++) {
		fscanf(in, "%s", tmp);
		for(int j=0; j<M; j++)
			hash[i][j]=tmp[j] == '0' ? -1 : 1;
	}
	out=fopen("result.txt", "w");
	setvbuf(out, NULL, _IOFBF, 1048576);
}

inline char *ReadChapter(char *buf)
{
	while(*buf<'0' || *buf>'9') buf++;
	char *p=buf;
	while((*p>='0' && *p<='9') || *p=='-') p++;
	*p='\0';
	Document *doc=&docs[idcnt];
	doc->m=InitTrie();
	doc->name=buf;
	++idcnt;
	return p;
}
inline char *ReadSample(char *buf)
{
	while(*buf!='S') buf++;
	char *p=buf;
	while((*p>='0' && *p<='9') || *p=='-' || isAlpha(*p)) p++;
	*p='\0';
	sample.m=InitTrie();
	sample.name=buf;
	memset(sample.cnts, 0, sizeof(sample.cnts));
	memset(sample.hash, 0, sizeof(sample.hash));
	return p;
}

void genVecs(Trie *trie, int depth)
{
	for(int i=0;i<26;i++)
		if(trie->next[i])
		{
			buffer1[depth]='a'+i;
			genVecs(trie->next[i], depth+1);
		}
	if(trie->cnt) {
		buffer1[depth]='\0';
		vec[veccnt].w=trie->cnt;
		vec[veccnt].name=(char*)malloc(depth);
		strcpy(vec[veccnt++].name, buffer1);
	}
}

inline void printSample()
{
	for(int k=0; k<N; k++) {
		int tmp=TrieQueryInternal(sample.m, vec[k].name);
		for(int j=0; j<M; j++)
			sample.hash[j]+=hash[k][j]*tmp;
	}
	for(int j=0; j<M; j++)
		sample.hash[j]=sample.hash[j] > 0 ? 1 : 0;
	for(int i=0; i<idcnt; i++) {
		int sum=0;
		for(int j=0; j<M; j++)
			if(sample.hash[j]!=docs[i].hash[j])
				sum++;
		if(sum<=3)
			sample.ids[sum][sample.cnts[sum]++]=i;
	}
	fputs(sample.name, out); fputc('\n', out);
	for(int i=0; i<=3; i++) {
		if(sample.cnts[i]) {
			fprintf(out,"%d:", i);
			for(int j=0; j<sample.cnts[i]; j++) {
				fputs(docs[sample.ids[i][j]].name, out);
				fputc(' ', out);
			}
			fputc('\n', out);
		}
	}
}

int main(int argc, char **argv)
{
	//N=1000,M=16;
	sscanf(argv[1], "%d", &N);
	sscanf(argv[2], "%d", &M);
	prepare();
	FILE *in=fopen("article.txt","rb");
	int len=fread(buffer,1,BUFSIZE,in);
	char *p=buffer;
	p=ReadChapter(p);
	Document *doc=&docs[0];
	while(p-buffer<len) {
		if(*p=='\f') {
			p=ReadChapter(p+1)+1;
			doc=&docs[idcnt-1];
		} else if(isAlpha(*p)) {
			if(!TrieQuery(swords,p)) {
				TrieInsertOrAdd(all, p);
				p=TrieInsertOrAdd(doc->m,p);
				continue;
			}
			while(isAlpha(*p)) p++;
		} else p++;
	}
	genVecs(all, 0);
	qsort(vec, veccnt, sizeof(Vector), cmp);
	for(int i=0; i<idcnt; i++) {
		for(int k=0; k<N; k++) {
			int tmp=TrieQueryInternal(docs[i].m, vec[k].name);
			for(int j=0; j<M; j++)
				docs[i].hash[j]+=hash[k][j]*tmp;
		}
		for(int j=0; j<M; j++)
			docs[i].hash[j]=docs[i].hash[j] > 0 ? 1 : 0;
	}

	in=fopen("sample.txt","rb");
	len=fread(buffer1,1,BUFSIZE,in);
	p=buffer1;
	p=ReadSample(p);
	while(p-buffer1<len) {
		if(*p=='\f') {
			printSample();
			if(p+1-buffer1>=len) break;
			p=ReadSample(p+1)+1;
		} else if(isAlpha(*p)) {
			if(!TrieQuery(swords,p)) {
				p=TrieInsertOrAdd(sample.m,p);
				continue;
			}
			while(isAlpha(*p)) p++;
		} else p++;
	}
	fclose(out);
	return 0;
}
