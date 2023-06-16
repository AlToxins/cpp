#include<iostream.h>
#define MIN(x,y) x>y?y:x
int V[8]={0,35,30,25,20,15,10,5};  //价值
int D[8]={0,4,2,4,3,4,8,3};        //期限
int J[8]={0,0,0,0,0,0,0,0};        //最优解
int P[8];    //父节点
int F[8];    //最接近i的空闲位置
int k=0;
int n=8;     //作业数+1
//////////////////////////////////
int FIND(int i)
{
	int j,k,t;
	j=i;
	while(P[j]>0)
		j=P[j];
	k=i;
	while(k!=j)
	{
		t=P[k];
		P[k]=j;
		k=t;
	}
	return j;   
}
////////////////////////////////////
int UNION(int i,int j)
{
	int x;
	x=P[i]+P[j];
	if(P[i]>P[j])     
	{
		P[i]=j;    //i的节点少
		P[j]=x;
	}
	else
	{
		P[j]=i;     //j的节点少
		P[i]=x;
	}
	return 1;
}
//////////////////////////////////
void FJS()
{
	int j,l;
	for(int i=0;i<n;i++)   //初始化		F[i];P[i]
	{	
		F[i]=i;
		P[i]=-1;
	}
	k=0;
	for(i=1;i<n;i++)                  //贪心规则
	{
		j=FIND(MIN(n,D[i]));
		if(F[j]!=0)                  //选择作业i
		{
			k=k+1;
			J[k]=i;   
			l=FIND(F[j]-1);
			UNION(l,j);
			F[j]=F[l];
		}
	}   
}
////////////////////////////////
void main()
{
	FJS();
	cout<<"选择的作业数:  "<<k<<endl;
	cout<<"选择作业序号:  ";
	for(int i=1;i<n;i++)
		cout<<J[i]<<"\t";
	cout<<endl;
}