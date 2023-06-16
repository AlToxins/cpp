#include<iostream>
using namespace std;
struct node{
	node*nxt;
	node*lst;
	int d;
};
int main(){
	node*a;
	node*b;
	node*c;
	a=new node();
	b=new node();
	c=new node();
	a->d=1;
	b->d=2;
	c->d=3;
	a->nxt=b;
	b->lst=a;
	b->nxt=c;
	c->lst=b;
	b->lst->nxt=b->nxt;
	b->nxt=NULL;
	cout<<a->d<<endl;
	cout<<b->d<<endl;
	cout<<a->nxt->d<<endl;
	//cout<<b->nxt->d<<endl;
	if(b->nxt->nxt->nxt==NULL) cout<<"ok"<<endl;

	return 0;
	
}
