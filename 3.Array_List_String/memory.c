#include <stdio.h>
#include <stdlib.h>

typedef struct _mem_list {
	struct _mem_list *next;
	int addr;
	int size;
} mem_list;

mem_list *head;

int main()
{
	int n;
	mem_list *cur=head;
	scanf("%d", &n);
	for(int i=0; i<n; i++) {
		int a,s;
		scanf("%d%d",&a,&s);
		mem_list *tmp = (mem_list *)malloc(sizeof(mem_list));
		tmp->addr = a; tmp->size = s;
		if(cur) {
			cur->next = tmp;
			cur = cur->next;
		}
		else {
			cur=head=tmp;
		}
	}
	cur->next = head;
	while (1) {
		int t;
		scanf("%d",&t);
		if (t==-1) break;
		cur = head;
		mem_list *best = NULL;
		for(int i=0; i<n; i++,cur=cur->next) {
			if (cur->size < t)
				continue;
			if (cur->size == t) {
				best = cur;
				break;
			}
			if (!best)
				best = cur;
			else if (cur->size < best->size)
				best = cur;
		}
		if (best) {
			best->size -= t;
			head = best;
		}
	}
	cur = head;
	for(int i=0; i<n; i++,cur=cur->next)
		if (cur->size)
			printf("%d %d\n", cur->addr, cur->size);
	return 0;
}