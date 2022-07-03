#pragma GCC optimize ("O3")
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define fequ(a,b) (fabs((a)-(b))<1e-7)
#define min(a,b) ((a)<(b)?(a):(b))

typedef struct _TRIE {
	struct _TRIE *next[26];
	int cnt;
} Trie;
typedef struct _Document {
	int count,id;
	double sim;
	char name[16];
	Trie *m;
} Document;
typedef struct _DNRec {
	int cnt,lastid;
	char *word;
} DNRec;
Trie *dict;
Document *docs[200000];int idcnt;
Trie *DNT;
DNRec DN[10000];int DNcnt;

inline int isAlpha(char c) {
	return ((c>='a' && c<='z')||(c>='A' && c<='Z'));
}

inline Trie *InitTrie() {
	Trie *t=(Trie*)malloc(sizeof(Trie));
	memset(t,0,sizeof(Trie));
	return t;
}
inline char *TrieInsertOrAdd(Trie *t, char *s) {
	for(;isAlpha(*s);s++)
	{
		if(!(t->next[*s-'a']))
			t->next[*s-'a']=InitTrie();
		t=t->next[*s-'a'];
	}
	t->cnt+=1;
	return s;
}
inline char *TrieInsertOrAddn(Trie *t, char *s,int addn) {
	for(;*s;s++)
	{
		if(!(t->next[*s-'a']))
			t->next[*s-'a']=InitTrie();
		t=t->next[*s-'a'];
	}
	t->cnt+=addn;
	return s;
}
inline char *TrieInsertOrAddInternal(Trie *t, char *s) {
	for(;*s>='a' && *s<='z';s++)
	{
		if(!(t->next[*s-'a']))
			t->next[*s-'a']=InitTrie();
		t=t->next[*s-'a'];
	}
	t->cnt+=1;
	return s;
}
inline int TrieQuery1(Trie *t, char *s) {
	for(;isAlpha(*s);s++)
	{
		*s|=32;
		if(!(t->next[*s-'a']))
			return 0;
		t=t->next[*s-'a'];
	}
	return t->cnt;
}
inline int TrieQuery2(Trie *t, char *s) {
	for(;isAlpha(*s);s++)
	{
		if(!(t->next[*s-'a']))
			return 0;
		t=t->next[*s-'a'];
	}
	return t->cnt;
}
inline int TrieQueryInternal(Trie *t, char *s) {
	for(;*s;s++)
	{
		if(!(t->next[*s-'a']))
			return 0;
		t=t->next[*s-'a'];
	}
	return t->cnt;
}
inline char *TrieDelete(Trie *t, char *s) {
	for(;isAlpha(*s);s++)
	{
		if(!(t->next[*s-'a']))
		{
			while(isAlpha(*s)) s++;
			return s;
		}
		t=t->next[*s-'a'];
	}
	t->cnt=0;
	return s;
}

int cmp(const void* pL, const void* pR) {
	Document *L=*(Document**)pL,*R=*(Document**)pR;
	if(fequ(L->sim,R->sim))
		return L->id < R->id ? -1 : 1;
	return L->sim > R->sim ? -1 : 1;
}

inline void prepare() {
	DNT=InitTrie();
	dict=InitTrie();
	char *buffer=(char*)malloc(6291456);
	FILE *in;
	in=fopen("dictionary.txt", "rb");
	int len=fread(buffer,1,6291456,in);
	buffer[len]='\0';
	char *p=buffer;
	while(p-buffer<len)
		p=TrieInsertOrAddInternal(dict,p)+1;
	fclose(in);
	in=fopen("stopwords.txt", "rb");
	len=fread(buffer,1,6291456,in);
	buffer[len]='\0';
	p=buffer;
	while(p-buffer<len)
		p=TrieDelete(dict,p)+1;
	fclose(in);
	free(buffer);
}

inline char *ReadChapter(char *buf) {
	while(*buf<'0' || *buf>'9') buf++;
	char *p=buf;
	while((*p>='0' && *p<='9') || *p=='-') p++;
	*p='\0';
	Document *doc=(Document*)malloc(sizeof(Document));
	doc->count=0;
	doc->sim=0;
	doc->m=InitTrie();
	strcpy(doc->name,buf);
	doc->id=++idcnt;
	docs[idcnt-1]=doc;
	return p;
}

int main(int argc, char **argv) {
	prepare();
	for(int i=2;i<argc;i++)
		if(TrieQueryInternal(dict,argv[i]))
		{
			TrieInsertOrAddn(DNT,argv[i],++DNcnt);
			DN[DNcnt].word=argv[i];
		}
	FILE *in=fopen("article.txt","rb");
	char *buffer=(char*)malloc(64*1024*1024);
	int len=fread(buffer,1,64*1024*1024,in);
	char *p=buffer;
	p=ReadChapter(p);
	Document *doc=docs[idcnt-1];
	while(p-buffer<len) {
		if(*p=='\f') {
			p=ReadChapter(p+1)+1;
			doc=docs[idcnt-1];
		} else if(isAlpha(*p)) {
			if(TrieQuery1(dict,p))
				doc->count++;
			int t=TrieQuery2(DNT,p);
			if(t) {
				p=TrieInsertOrAdd(doc->m,p);
				if(DN[t].lastid!=doc->id)
				{
					DN[t].cnt++;
					DN[t].lastid=doc->id;
				}
				continue;
			}
			while(isAlpha(*p)) p++;
		} else p++;
	}
	fclose(in);//free(buffer);
	for(int i=0;i<idcnt;i++) {
		doc=docs[i];
		for(int k=1;k<=DNcnt;k++)
		{
			int t=TrieQueryInternal(doc->m,DN[k].word);
			if(t)
				doc->sim+=t*100.0/doc->count*log10((double)idcnt/DN[TrieQueryInternal(DNT,DN[k].word)].cnt);
		}
	}
	qsort(docs,idcnt,sizeof(Document*),cmp);
	int num;
	sscanf(argv[1],"%d",&num);
	num=min(num,idcnt);
	FILE *out=fopen("results.txt","wb");
	for(int i=0;i<5;i++)
		printf("%.6lf %d %s\n",docs[i]->sim,docs[i]->id,docs[i]->name);
	p=buffer;
	for(int i=0;i<num;i++) {
		doc=docs[i];
		if(doc->sim==0)
			break;
		p+=sprintf(p,"%.6lf %d %s\n",doc->sim,doc->id,doc->name);
	}
	fwrite(buffer,1,p-buffer,out);
	fclose(out);
	return 0;
}
