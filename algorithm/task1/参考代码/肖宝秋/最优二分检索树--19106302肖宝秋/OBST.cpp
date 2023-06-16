#include<iostream.h>
#include<fstream.h>
#define N 4
int P[N+1]={0,3,3,1,1};    //成功检索
int Q[N+1]={2,3,1,1,1};    //不成功检索
//二分检索树Tij的成本C[][],Tij的跟R[][],Tij的权值W[][]
int C[N+1][N+1],W[N+1][N+1],R[N+1][N+1];
void OBST()
{
	int i,j,m,k,l,min;
	for(i=0;i<=N-1;i++)
	{
		W[i][i] = Q[i];R[i][i] = 0;C[i][i] = 0;
        W[i][i+1] = Q[i]+Q[i+1]+P[i+1];
        R[i][i+1] = i+1;
        C[i][i+1] = Q[i]+Q[i+1]+P[i+1];
	}
    W[N][N] = Q[N];
	R[N][N] = 0;
	C[N][N] = 0;
	for(m=2;m<=N;m++)                                                                 
		for(i=0;i<=N-m;i++)
		{
			min=100;
			j=i+m;
			W[i][j] = W[i][j-1]+P[j]+Q[j];
			for(l=R[i][j-1];l<=R[i+1][j];l++)   //找使C[i][l-1]+C[l][j]取最小的l值
				if(C[i][l-1]+C[l][j]<min){min=C[i][l-1]+C[l][j];k=l;}
            C[i][j] = W[i][j]+C[i][ k-1]+C[k][j];
			R[i][j] = k;
		}
}
void PrintResult()   //结果输出
{
	cout<<"W[i][j]--C[i][j]--R[i][j]:\n";
	for(int i=0;i<=N;i++)
	{
		cout<<"  i=";
		cout<<i<<"      \t";
	}
	cout<<"------------------------------------------------------------------------\n";
	for(i=0;i<=N;i++)
	{
		cout<<"j="<<i<<"   ";
		for(int j=0;j<=N;j++)
			cout<<W[i][j]<<" "<<C[i][j]<<" "<<R[i][j]<<"    \t";
		cout<<"\n";
	}
	/*for(int i=0;i<=N;i++)
	{
		for(int j=0;j<=N-i;j++)
		{
            cout<<W[j][j+i]<<"\t"<<C[j][j+i]<<"\t"<<R[j][j+i]<<endl;;
			
		}

	cout<<endl;
	}*/
}
void main()
{
	OBST();
    PrintResult();
}