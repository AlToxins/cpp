#include<stdio.h>
#define max 100

int cost[max][max],a[max][max],i,j,k,n;

int main()
{
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
		{
			scanf("%d",&cost[i][j]);
			a[i][j]=cost[i][j];
		}

    for(k=1;k<=n;k++)
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
				if(a[i][k]+a[k][j]<a[i][j])a[i][j]=a[i][k]+a[k][j]; 
				printf("\n");

 	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)printf("%d ",a[i][j]);
		printf("\n");
	}
	return 0;
}