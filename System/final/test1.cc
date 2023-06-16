#include<iostream>
using namespace std;
struct node{
	node*nxt;
};

int main(){
	node *test = new node(2);
	test(0)->nxt=test(1);
	return 0;
}
