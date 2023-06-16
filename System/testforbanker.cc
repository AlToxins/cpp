#include<iostream>
using namespace std;

class node{
	public:
	int a;
};

class test{
	public:
	void c(){
		node*b;
		b=new node[3];
		node *d = &b[1];
		d->a=1;
		cout<<d->a;
	}
};

int main(){
	test use;
	use.c();
	return 0;
}

