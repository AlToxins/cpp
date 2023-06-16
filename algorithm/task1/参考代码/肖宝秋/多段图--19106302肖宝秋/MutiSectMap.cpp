#include<iostream.h>
#include<fstream.h>
#include<stdlib.h>
int n,k,*P,*D,*COST,**E;  //p是最小成本路径。d是决策,E是图的矩阵，n是节点个数，k是段的数
int Mymalloc()
{
	int returnvalue=1;
	if((E=(int **)malloc((n+1)*sizeof(int *)))==NULL)
	{
		cout<<"空间申请失败!";
		returnvalue=0;
	}
    for(int i=1;i<n+1;i++)
	{
		if((E[i]=(int *)malloc((n+1)*sizeof(int)))==NULL)
		{
			cout<<"空间申请失败!";
			returnvalue=0;
		}	
	}
	if((P=(int*)malloc((k+1)*sizeof(int)))==NULL||(D=(int*)malloc(n*sizeof(int)))==NULL||(COST=(int*)malloc((n+1)*sizeof(int)))==NULL)   
	{
		cout<<"空间申请失败!";
		returnvalue=0;
	}
	return returnvalue;
}
void FGRAPH()
{
	COST[n]=0;     //最后一个节点
	cout<<"COST["<<n<<"]="<<COST[n]<<"\n";
    for(int j=n-1;j>0;j--)   //j之前的cost值一定已经计算了
	{
        int r,min=100;
		for(int i=j+1;i<n+1;i++)    //找到r
			if(E[j][i]+COST[i]<min) {min=E[j][i]+COST[i];r=i;}
        COST[j]=E[j][r]+COST[r];
		cout<<"COST["<<j<<"]="<<COST[j]<<"\t";
		D[j]=r;
		cout<<"D["<<j<<"]="<<D[j]<<"\n";
	}
	P[1]=1;P[k]=n;
	for(j=2;j<k;j++)
	{
		P[j]=D[P[j-1]];
	}
	cout<<"最短路径:";
	for(j=1;j<=k;j++)
		cout<<P[j]<<"\t";
	cout<<"\n最短路径长度:"<<COST[1]<<endl;
}
void BGRAPH()
{
	COST[1]=0;     //最后一个节点
	cout<<"COST["<<n<<"]="<<COST[1]<<"\n";
    for(int j=2;j<=n;j++)   //j之前的cost值一定已经计算了
	{
        int r,min=1000;
		for(int i=1;i<j;i++)    //找到r
			if(E[i][j]+COST[i]<min) {min=E[i][j]+COST[i];r=i;}
        COST[j]=E[r][j]+COST[r];
		cout<<"COST["<<j<<"]="<<COST[j]<<"\t";
		D[j]=r;
		cout<<"D["<<j<<"]="<<D[j]<<"\n";
	}
	P[1]=1;P[k]=n;
	for(j=k-1;j>=2;j--)
	{
		P[j]=D[P[j+1]];
	}
	cout<<"最短路径:";
	for(j=1;j<=k;j++)
		cout<<P[j]<<"\t";
	cout<<"\n最短路径长度:"<<COST[12]<<endl;
}
void InputData()
{
	ifstream fin;
	fin.open("data.txt");
	cout<<"段的数目:";
	cin>>k;
	cout<<"节点数目:";
	cin>>n;
	if(Mymalloc()==0)  //空间申请
		return;
	for(int i=1;i<=n;i++)    //图的矩阵
		for(int j=1;j<=n;j++)
			fin>>E[i][j];
}
void Select_Fun()
{
	char select;
	while(1)
	{
		cout<<"请选择方法(f:向前----b:向后---q:退出):";
		cin>>select;
		if(select=='f'||select=='F') FGRAPH();
		else if(select=='b'||select=='B') BGRAPH();
		else if(select=='q'||select=='Q') break;
		cout<<endl;
	}
}
void main()
{
	InputData();
	Select_Fun();
}
