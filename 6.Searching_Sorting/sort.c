#include<stdio.h>
#include<stdlib.h>
int cmp,n;
int k[105];

void swap(int *a,int *b)
{
	int t=*a;
	*a=*b;
	*b=t;
}

void Select()   
{
	int d;
    for(int i=0;i<n-1;i++)
	{
        d=i;
        for(int j=i+1;j<n;j++)
		{
			++cmp;
            if(k[j]<k[d])
                d=j;
		}
        if(d!=i)
            swap(k+d,k+i);
	}
}

void Bubble()
{
	int flag=1;
	for(int i=n-1;i && flag;i--)
	{
		flag=0;
		for(int j=0;j<i;j++)
		{
			++cmp;
			if(k[j]>k[j+1])
			{
				swap(k+j,k+j+1);  
				flag=1;
			}
		}
	}
}

void heap(int i,int nn)
{
    int j=2*i+1,temp=k[i];
    while(j<nn){
        if(j<nn-1 && k[j]<k[j+1])
            j++;
		++cmp;
        if(temp>=k[j]) 
            break;
        k[(j-1)/2]=k[j];
        j=2*j+1;
    }
    k[(j-1)/2]=temp;
}

void Heap()
{
    for(int i=n/2-1;i>=0;i--)
        heap(i,n);
    for(int i=n-1;i>=1;i--)
	{
        swap(k,k+i);
        heap(0,i);
    }
}

void merge(int *tmp,int left,int leftend,int rightend)
{
    int i=left, j=leftend+1, q=left;
    while(i<=leftend && j<=rightend)
    {
		++cmp;
        if(k[i]<=k[j]) 
            tmp[q++]=k[i++];
        else
            tmp[q++]=k[j++];
    }
    while(i<=leftend)
        tmp[q++]=k[i++];
    while(j<=rightend)
        tmp[q++]=k[j++];
    for(i=left; i<=rightend; i++)
        k[i]=tmp[i];
}

void mSort(int *tmp, int left, int right)
{
    int center;
    if(left < right){
        center = (left+right)/2;
        mSort(tmp, left, center);
        mSort(tmp, center+1, right);
        merge(tmp, left,center, right);
    }
}

void Merge()
{
    int *tmp=(int*)malloc(sizeof(int)*n);
    mSort(tmp, 0, n-1);
    free(tmp);
}

void Quick(int left,int right)
{     
    int i, last;
    if(left<right)
	{
        last=left; 
        for(i=left+1;i<=right;i++)
		{
			++cmp;
            if(k[i]<k[left])
                swap(k+(++last),k+i);
		}
        swap(k+left,k+last);
        Quick(left,last-1); 
        Quick(last+1,right);   
    }
}

int main()
{
	int op;
	scanf("%d%d",&n,&op);
	for(int i=0;i<n;i++)
		scanf("%d",k+i);
	switch(op)
	{
	case 1: Select();     break;
	case 2: Bubble();     break;
	case 3: Heap();       break;
	case 4: Merge();      break;
	case 5: Quick(0,n-1); break;
	}
	for(int i=0;i<n;i++)
		printf("%d ",k[i]);
	printf("\n%d",cmp);
	return 0;
}