#include<stdio.h>
#include<stdlib.h>
#define max 1000  //最大节点数

int parent[max],J[max],f[max];   //每个节点对应的父节点存放在数组中

int n,b,i;


struct zuoye
{
	int p,d;
}task[max];

void Union(int a,int b)        //根为a和b的两个集合，作为参数传入
{
	int x;
	x=parent[a]+parent[b];
	if(parent[a]>parent[b])//a的节点少
	{
		parent[a]=b;//正数
		parent[b]=x;//负数
	}
	else                  //b的节点少
	{
		parent[b]=a;//正数
		parent[a]=x;//负数
	}
	
}

int find(int a)
{
	int j=a,k,t;
	while(parent[j]>0)j=parent[j];
	k=a;
	while(k!=j)
	{
		t=parent[k];
		parent[k]=j;
		k=t;
	}
	return j;    //返回找到的根节点
}


void FJS()
{
	int i,k=0,j,l;
	for(i=0;i<=n;i++)
	{
		f[i]=i;
		parent[i]=-1;
	}
	for(i=1;i<=n;i++)
	{
		if(task[i].d>n)j=find(n);
		else j=find(task[i].d);
		if(f[j]!=0)
		{
			k++;
			J[k]=i;
			l=find(f[j]-1);
			Union(l,j);
			f[j]=f[l];
		}
	}
	for(i=1;i<=k;i++)printf("%d ",J[i]);
	printf("\n");
}

int cmp(const void *a,const void *b)
{
	return (*(zuoye *)b).p>(*(zuoye *)a).p? 1: -1;
}


int main()
{
	scanf("%d",&n);
	for(i=0;i<n;i++)scanf("%d",&task[i].p);
	for(i=0;i<n;i++)scanf("%d",&task[i].d);
	qsort(task,n,sizeof(task[0]),cmp);
	for(i=n+1;i>=1;i--)task[i]=task[i-1];
	FJS();
	return 0;
}