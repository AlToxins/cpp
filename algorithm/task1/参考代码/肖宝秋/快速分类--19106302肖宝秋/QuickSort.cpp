//一般的快速排序，选取第一个元素参照
#include<iostream.h>
#include<fstream.h>
#define NUM 11
int A[NUM+1+1]={0,125,10,65,70,75,80,85,60,55,50,45,1000};
void PARTITION(int m,int &p)
{
	int v=A[m];   //参考元素
	int i=m,flag=1;
	while(1)
	{
		do{i=i+1;}while(A[i]<=v && i<p);   //保证边缘也正确
		do{p=p-1;}while(A[p]>=v && p>m);
		if(i<p)
		{
			int temp=A[i];
			A[i]=A[p];
			A[p]=temp;
		}
		else break;    //循环到不满足i<p时候截止
	}
	A[m]=A[p];A[p]=v;
}
void QUICKSORT(int p,int q)
{
	int j;
	if(p<q)
	{
		j=q+1;
		PARTITION(p,j);
		QUICKSORT(p,j-1);
		QUICKSORT(j+1,q);
	}
}
void main()
{
	cout<<"原始数据:";
	for(int i=1;i<=NUM;i++)
		cout<<A[i]<<" ";
	cout<<endl;
	QUICKSORT(1,NUM);
	cout<<"结果数据:";
	for(i=1;i<=NUM;i++)
		cout<<A[i]<<" ";
	cout<<endl;
}