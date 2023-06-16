#include<iostream>
using namespace std;

struct node{
	double p;
	double w;
	double stan; //stan=p/w
	node*nxt;
	node*lst;
};

class bp{
	public:
		bp();
		~bp();
		//void backpack();
		void sort();
		void show();
	private:
		double m;
		int n;
		node*head;
		node*end;
};

bp::bp(){
	cout<<"start"<<endl;
	cout<<"give n: ";
	cin>>n;
	cout<<"give m: ";
	cin>>m;
	int i=1;
	head=new node();
	end=new node();
	node*a=head;
	while(i<=n){
		node*b=new node();
		a->nxt=b;
		b->lst=a;
		cout<<"give p of n"<<i<<": ";
		cin>>b->p;
		cout<<"give w of n"<<i<<": ";
		cin>>b->w;
		b->stan=b->p/b->w;
		i++;
		a=a->nxt;
	}
	a->nxt=end;
	cout<<"link has created"<<endl;
}

bp::~bp(){
	node*a=head->nxt;
	while(a!=NULL){
		delete a->lst;
		a=a->nxt;
	}
	cout<<endl<<"finish"<<endl;
}

void bp::show(){
	cout<<"the link is: ";
	node*a=head->nxt;
	while(a!=end){
		cout<<a->stan<<" ";
		a=a->nxt;
	}
}
void bp::sort(){
	node*a=head->nxt;
	while(1){
		node*a1=a->nxt;
		if(a==end)break;
		node*b=a->nxt;
		while(1){
			node*b1=b->nxt;
			if(b==end)break;
			if(b->stan>a->stan){
				b->lst->nxt=b->nxt;
				b->nxt->lst=b->lst;
				b->lst=a->lst;
				a->lst->nxt=b;
				b->nxt=a;
				a->lst=b;
			}
			b=b1;
		}
		a=a1;
	}
}



int main(){
	bp a;
	a.sort();
	a.show();
	return 0;
}
