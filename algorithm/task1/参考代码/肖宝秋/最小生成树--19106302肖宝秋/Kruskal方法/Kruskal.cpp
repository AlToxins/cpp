#include<iostream.h>
#include<fstream.h>
#define N 6
int mincost=0,COST[N+1][N+1];
int P[N+1]={-1},T[N][3];
struct EDGE        //边集
{
	int sour;      //起点
	int dest;      //终点
	int weight;    //权值
};
EDGE E[(N*N-N)/2+1];
int edgenum=0;   //边数
void InputData()   //读矩阵信息,并建立边集
{
	ifstream fin;
	fin.open("data1.txt");
	for(int i=1;i<=N;i++)    
		for(int j=1;j<=N;j++)
			fin>>COST[i][j];
	for(i=1;i<=N;i++)    
		for(int j=i+1;j<=N;j++)
			if(COST[i][j]>0 && COST[i][j]<100){E[edgenum].sour=i;E[edgenum].dest=j;E[edgenum].weight=COST[i][j];edgenum++;}
}
//head为要要建树的根节点下标，n为总节点数，a[]数组为数据
void CreatHeap(EDGE a[],int n,int head)
{
	int i=head,j=2*i+1,flag=0;EDGE temp=a[i];
	while(j<n && flag!=1)
	{
		if(j<n-1 && a[j].weight>a[j+1].weight) j++;  //寻找左右孩子中较小的节点元素
		if(temp.weight < a[j].weight) flag=1;   //不用调整
		else{a[i]=a[j];i=j;j=2*i+1;}   //调整
	}
	a[i]=temp;   //最初的a[i]赋值给最后的a[j]
}
int FIND(int i)
{
	int j=i,k,t;
	while(P[j]>0)j=P[j];
	k=i;
	while(k!=j){t=P[k];	P[k]=j;	k=t;}
	return j;   
}
////////////////////////////////////
int UNION(int i,int j)
{
	int x=P[i]+P[j];
	if(P[i]>P[j]){P[i]=j; P[j]=x;}
	else{P[j]=i;P[i]=x;}
	return 1;
}
void main()
{
	int u,v,m,n;
    InputData();
	/*cout<<"所有边的信息:\n";
	for(int i=0;i<edgenum;i++)
       cout<<E[i].sour<<"\t"<<E[i].dest<<"\t"<<E[i].weight<<endl;*/
	for(int i=(edgenum-1)/2;i>=0;i--)   //建最小堆
		CreatHeap(E,edgenum,i);
	int j=0;
	cout<<"选择的边信息(起点-终点-权重):"<<endl;
    for(i=edgenum-1;i>=0;i--)  //根据最小堆建立最小生成树
	{
		EDGE temp=E[0];
		E[0]=E[i];
        E[i]=temp;
        CreatHeap(E,i,0);

		m=temp.sour;n=temp.dest;
		u=FIND(m);
		v=FIND(n);
		if(u!=v)   //根节点不同
		{
			T[j][1]=u;T[j][2]=v;
			j++;
           	cout<<m<<"\t"<<n<<"\t"<<temp.weight<<endl;   //被选择的边权值
			mincost=mincost+temp.weight;
            UNION(u,v);
		}
	}
	cout<<"最小生成树路径长度:"<<mincost<<endl;
}
