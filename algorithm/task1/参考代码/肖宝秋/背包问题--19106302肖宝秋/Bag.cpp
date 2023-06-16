#include<iostream.h>
int p[3]={25,24,15};
int w[3]={18,15,10};
void ValueSort()   //sort
{
  float res[3];
  for(int i=0;i<3;i++)
	  res[i]=(float)p[i]/w[i];
  int flag=1;
  float temp;
  for(i=1;i<3&&flag==1;i++)
  {
	  flag=0;
	  for(int j=0;j<3-i;j++)
		  if(res[j]<res[j+1])
		  {
			  flag=1;
			  temp=p[j];p[j]=p[j+1];p[j+1]=temp;
              temp=w[j];w[j]=w[j+1];w[j+1]=temp;
              temp=res[j];res[j]=res[j+1];res[j+1]=temp;
		  }
  }
}
void main()
{
	int n=3,m=20; 
    ValueSort();
	float X[3]={0};
	int cu=m;

	cout<<"作业排序结果："<<endl;
	for(int i=0;i<3;i++)
		cout<<p[i]<<"\t";
	cout<<endl;
	for(i=0;i<3;i++)
		cout<<w[i]<<"\t";
	cout<<endl;

	for(i=0;i<3;i++)
	{
      if(w[i]>cu) break;
	  X[i]=1;
	  cu=cu-w[i];
	}
	if (i<=n) X[i]=(float)cu/w[i];
	cout<<"结果："<<endl;
	for(i=0;i<3;i++)
		cout<<X[i]<<"\t";
	cout<<endl;
}