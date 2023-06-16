#include<iostream>
using namespace std;

struct node{
	int num;
};
int main(){
	node *a = new node [8];
	a[0]->num=1;
	cout<<a->num<<endl;
	return 0;
}
