#include<stdio.h>
#include<stdlib.h>

int n,i;
double m,sum=0;

struct Node
{
	double p,w,p_w;
}a[100];

int cmp(const void *p1,const void *p2)
{
	return (*(Node *)p2).p_w > (*(Node *)p1).p_w ? 1 : -1;
}

int main()
{
	scanf("%d%lf",&n,&m);
	for(i=0;i<n;i++)
	{
		scanf("%lf%lf",&a[i].p,&a[i].w);//a[i][0],a[i][1]分别为p和w
		a[i].p_w=a[i].p/a[i].w;
	}
	qsort(a,n,sizeof(a[0]),cmp);
	for(i=0;i<n;i++)
	{
		if(a[i].w>m)break;
		m-=a[i].w;
		sum+=a[i].p;
	}
	if(i<n)sum+=a[i].p*m/a[i].w;
	printf("max number is %lf\n",sum);
	return 0;
}
