#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
//int link[11],a[100],n;
int link[1000],a[1000],n;

void insert_sort(int low,int high,int *p)
{
	int i,item,pos,qian,pp;
	link[low]=0;
	pp=low;
	for(i=low+1;i<=high;i++)
	{
		item=a[i];
		pos=pp;
		while(item>a[pos])
		{
			qian=pos;
			pos=link[pos];
			if(pos==0)break;
		}
		if(pos==0)   //处于链表尾部
		{
			link[i]=0;
			link[qian]=i;
		}
		else
		{
			if(pos==pp)   //处于链表头部
			{
				link[i]=pp;
				pp=i;
			}
			else         
			{
				link[i]=link[qian];
			    link[qian]=i;
			}
		}
	}
	*p= pp;
}

void merge(int q,int r,int *p)
{
	int i=q,j=r,k=0;
	while(i&&j)
	{
		if(a[i]<=a[j])
		{
			link[k]=i;
			k=i;
			i=link[i];
			
			
		}
		else
		{
			link[k]=j;
			k=j;
			j=link[j];
		}
	}
	if(i==0)link[k]=j;
	else link[k]=i;
	*p=link[0];
}

void merge_sort(int low,int high,int * p)
{
	int mid,q,r;
	if(high-low+1<5)insert_sort(low,high,p);
	else 
	{
		mid=(low+high)/2;
	    merge_sort(low,mid,&q);
	    merge_sort(mid+1,high,&r);
	    merge(q,r,p);
	}
}

int main()
{
	int i,p;
	memset(link,0,sizeof(link));
	scanf("%d",&n);
	for(i=1;i<=n;i++)scanf("%d",&a[i]);
	merge_sort(1,n,&p);
	printf("\n");
	while(1)
	{
		printf("%d ",a[p]);
		if(link[p]==0)break;
		p=link[p];
	}
	printf("\n");
	return 0;
}
