#include<iostream>
using namespace std;
struct node{
	node*nxt;
	int data;
	int mat[3][3];
};
int main(){
	node*a=new node();
	a->mat[0][0]=1;
	a->mat[0][1]=2;
	int k=0;
	int k1=0;
	while(1){
		if(k==2)break;
		cout<<a->mat[k1][k]<<endl;
		k++;
	}
	if(a->mat[0][2]==NULL) cout<<"NULL"<<endl;
	return 0;
}
