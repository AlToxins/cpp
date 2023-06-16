#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define maxweight 100000000
#define max 100

int map[max][max],distance[max],path[max],n,i,j;
bool f[max];//用来标记节点是否计算过

void Dijkstra(int v)   //从节点v到其余的最短路径
{
	int i,j,u;
	for(i=0;i<n;i++)
	{
		distance[i]=map[v][i];
		//f[i]=true;
		if(i!=v&&distance[i]<maxweight)path[i]=v;
		else path[i]=-1;
	}
	f[v]=true;
	for(i=1;i<n;i++)
	{
		int mindis=maxweight;
		for(j=0;j<n;j++)
			if(!f[j]&&distance[j]<mindis)
			{
				u=j;
				mindis=distance[j];
			}
			if(mindis==maxweight)return;
			f[u]=true;
			for(j=0;j<n;j++)
				if(!f[j]&&map[u][j]<maxweight&&(distance[u]+map[u][j]<distance[j]))
				{
					distance[j]=distance[u]+map[u][j];
					path[j]=u;
				}
	}
}

int main()
{
	memset(f,false,sizeof(f));
	scanf("%d",&n);
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)scanf("%d",&map[i][j]);
			Dijkstra(0);
			for(i=1;i<n;i++)printf("%d ",distance[i]);
			printf("\n");
			return 0;
}
