#include<iostream>
using namespace std;

void ascsort(int *a, int len)
{
	for (int j=1; j<len; j++)
	{
		int key = a[j];
		int i = j-1;
		while (i>=0 && a[i]>key)
		{
			a[i+1] = a[i];
			i--;
		}
		a[i+1] = key;
	}
}

void dessort(int *a, int len)
{
	for (int j=1; j<len; j++)
	{
		int key = a[j];
		int i = j-1;
		while (i>=0 && a[i]<key)
		{
			a[i+1] = a[i];
			i--;
		}
		a[i+1] = key;
	}
}

int main(){
	int len=8;
	int a[len]={1,3,4,5,2,4,2,4};
	ascsort(a, 8);
	
	int e=0;
		while(e+1<len){	//remove the same floor
			if(a[e]==a[e+1]){
				int f=e;
				while(1){
					if(f+1==len){
						break;
					}
					a[f]=a[f+1];
					f++;
				}
				len--;
				e--;
			}
			e++;
		}
	int k=0;
	while(k<len){
		cout<<a[k]<<" ";
		k++;
	}
	return 0;
} 
