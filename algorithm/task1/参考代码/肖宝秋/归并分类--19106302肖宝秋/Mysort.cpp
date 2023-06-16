#include<iostream.h>
#include<fstream.h>
#include<time.h>
#include<stdlib.h>
#define NUM 500
char filename[]="data500.txt"; 
int data[NUM+1];
int LINK[NUM+1]={0};
#define INFINITE 10000  
void Readdata()   //文件读入数据
{
	ifstream fin;
	fin.open(filename);
	for(int i=1;i<NUM+1;i++)
		fin>>data[i];
	cout<<"初始数据:\n";
	for(i=1;i<NUM+1;i++)
	{
		cout.width(4);
		cout<<data[i]<<" ";
	}
	cout<<endl;
}
//将low--high中元素按非降序排列
void INSERTSORT(int low,int high,int &p)   //直接插入排序
{
	int MIN=data[low],item=INFINITE;
	p=low;                                 //初始化必须的
	for(int i=low;i<high;i++)
	{
        item=INFINITE;LINK[i]=0;
		if(data[i]<MIN) {p=i;MIN=data[i];}
		for(int j=low;j<high;j++)
		{
			if(data[i]<data[j] && data[j]<item)
			{
				 LINK[i]=j;
				 item=data[j];
			}
		}
	}
}
void MERGE1(int q,int r,int &p)
{
	int i=q,j=r,k=0;
	while(i!=0&&j!=0)            //到0表示结束
	{ 
		if(data[i] <= data[j]) 	 //找较小关键字
		{
			LINK[k]=i;
			k=i;
			i=LINK[i];
		}                       //加一个新的关键字到此表
		else  
		{
			LINK[k]=j;
			k=j;
			j=LINK[j];
		}
	}
	if(i==0) LINK[k]=j;
	else LINK[k]=i;
	p=LINK[0];
}
void MERGESORT1(int low,int high,int &p)
{
	int mid,q,r;
	if(high-low<=10)
		INSERTSORT(low,high,p);
	else 
	{
		mid=(low+high)/2;
		MERGESORT1(low,mid,q);
		MERGESORT1(mid,high,r);
		MERGE1(q,r,p);
	}
}
void main()
{	
	ofstream fout;
	fout.open("result.txt");   //结果文件
	int p;
	Readdata();
	MERGESORT1(1,NUM+1,p);
	//cout<<"p值:"<<p<<endl;
	//cout<<"LINK数组值:"<<endl;
	//for(int i=1;i<NUM+1;i++)
	//	cout<<LINK[i]<<"\t";
	//cout<<endl;
	cout<<"排序后值:"<<endl;
	for(int i=1;i<NUM+1;i++)
	{
        cout<<data[p]<<"\t";
		p=LINK[p];
        fout<<data[p]<<"\t";
	}
}