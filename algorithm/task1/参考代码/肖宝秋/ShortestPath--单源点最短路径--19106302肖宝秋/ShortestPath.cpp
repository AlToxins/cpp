#include<iostream>
#include<fstream>
#include"stdlib.h"
#define NUM 7
//filename文件名，n是矩阵大小，data存放矩阵数据
void ReadData(char* filename,int n,int data[NUM][NUM])
{
	ifstream fin;
	fin.open(filename);
	for(int i=0;i<n;i++)     //读入信息
	{
		for(int j=0;j<n;j++)
			fin>>data[i][j];
	}
}
//v表示开始接点，n表示矩阵大小，COST表示成本矩阵，DIST表示v到其他接点的距离
void SHORTEST_PATHS(int v,int n,int COST[NUM][NUM],int DIST[NUM],bool S[NUM])
{
	int index=0;
	for(int i=0;i<n;i++)
	{
		S[i]=0;
        DIST[i]=COST[v][i];
	}
	S[v]=1;
    DIST[v]=0;
	for(int num=1;num<n;num++)     //找v到其余接点的距离
	{
		int min=10001,k=0;
		for(int i=0;i<n;i++)       //找最短的DIST[v]
			if(S[i]!=1&&DIST[v]<min) 
			{min=DIST[v];k=i;}


        S[k]=1;
        for(i=0;i<n;i++)          //更新距离
		{
            if(S[i]!=1&&DIST[k]+COST[k][i]<DIST[i])
				DIST[i]=DIST[k]+COST[k][i];
		}
	}
}
void main()
{
	int start;
	int DIST[NUM];
	bool S[NUM];
	int COST[NUM][NUM];
	char filename[]="data.txt";
	cout<<"初始节点(0--"<<NUM<<"):";
	cin>>start;
	ReadData(filename,NUM,COST);               //数据读入到数组
	SHORTEST_PATHS(start,NUM,COST,DIST,S);
	for(int i=0;i<NUM;i++)
		cout<<DIST[i]<<"\t";
	cout<<"\n";
}
