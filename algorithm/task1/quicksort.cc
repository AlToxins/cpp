#include<iostream>
using namespace std;

struct node{
	node*nxt;
	node*lst;
	int data;
};

class sort{
	public:
		sort();
		~sort();
		node* start();
		int quicksort(node*a,  node*e); 
		void show();
		bool ifmin(node*fst);
		node*end();
	private:
		node*head1;
};

sort::sort(){
	cout<<"start quick sort"<<endl;
	head1=new node();
	//head2=new node();
}

sort::~sort(){
	cout<<"job finish"<<endl;
}

node* sort::end(){
	 node*a=head1->nxt;
	 while(a->nxt!=NULL){
		a=a->nxt;
	 }
	 return a;
}
bool sort::ifmin(node*fst){
	node*a=head1->nxt;
	while(a!=NULL){
		if(a->data>fst->data){
			return false;
		}
		a=a->nxt;
	}
	return true;
}

node* sort::start(){
	cout<<"input the serial (press 0 to end): ";
	node*a=new node();
	head1->nxt=a;
	a->lst=head1;
	int b;
	while(1){
		cin>>b;
		if(b==0){
			a->lst->nxt=NULL;
			break;
		}
		a->data=b;
		node*c=new node();
		a->nxt=c;
		c->lst=a;
		a=c;
	}	//bothway linked list has been created
		//next step I will start quicksort
	return head1->nxt;
}

int sort::quicksort(node*a, node*e){	//a is the first num of linked list
	//if(e!=NULL)cout<<"    e="<<e->data<<endl;
	//else cout<<"e=NULL"<<endl;
	node*head=a->lst;
	int ifcontinue=0;
	node*d=head1->nxt;
	while(d->nxt!=e){
		if(d->data>d->nxt->data){
			ifcontinue=1;
		}
		d=d->nxt;
	}
	if(ifcontinue==0)return 0;
	//a=head1->nxt;
	node*b=a->nxt;
	//node*finda=h->nxt;
	int posa=0;
	int n=1;
	while(1){
		if(b==e)break;
		//cout<<"a="<<a->data<<endl;
		//cout<<"b="<<b->data<<endl;
		if(b->nxt!=e&&a->nxt!=e){
			//cout<<"case1"<<endl;
			if(b->data<a->data&&n>posa){
				node*d=b->nxt;
				b->lst->nxt=b->nxt;
				b->nxt->lst=b->lst;
				b->lst=a->lst;
				a->lst->nxt=b;
				b->nxt=a;
				a->lst=b;
				posa++;
				b=d;
				n++;
			}
			else if(b->data>a->data&&n<posa){
				node*c=b->nxt;
				b->lst->nxt=b->nxt;
				b->nxt->lst=b->lst;
				b->nxt=a->nxt;
				a->nxt->lst=b;
				a->nxt=b;
				b->lst=a;
				posa--;
				b=c;
			}
			else{
				b=b->nxt;
				n++;
			}
		}
		else if(b->nxt==e&&a->nxt!=e){
			//node*f=b->nxt;
			//cout<<"case2"<<endl;
			if(b->data<a->data&&n>posa){
				if(e==NULL)b->lst->nxt=NULL;
				else{
					b->lst->nxt=e;
					e->lst=b->lst;
				}
				a->lst->nxt=b;
				b->lst=a->lst;
				b->nxt=a;
				a->lst=b;
				posa++;
				//b=f;
			}
			break;
		}
		else if(b->nxt!=e&&a->nxt==e){
			node*c=b->nxt;
			//cout<<"case3"<<endl;
			if(b->data>a->data&&n<posa){
				b->lst->nxt=b->nxt;
				b->nxt->lst=b->lst;
				a->nxt=b;
				b->lst=a;
				if(e==NULL)b->nxt=NULL;
				else{
					b->nxt=e;
					e->lst=b;
				}
				posa--;
				b=c;
			}
			else{
				b=b->nxt;
				n++;
			}
		}
		
		else if(a==b){
			b=b->nxt;
			n++;
		}
	}
	if(head->nxt!=a) quicksort(head->nxt, a);
	else quicksort(a->nxt, e);
	if(a->nxt!=NULL)quicksort(a->nxt,e);
	//show();
	//cout<<endl;
	return 0;
}


void sort::show(){
	node*a;
	a=head1->nxt;
	while(a!=NULL){
		cout<<a->data<<" ";
		a=a->nxt;
	}
}

int main(){
	sort x;
	x.quicksort(x.start(),NULL);
	x.show();
	return 0;
}
