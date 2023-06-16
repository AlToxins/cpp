#include<iostream>
using namespace std;
struct node{
	node*max;
	node*all;
	node*nee;
	node*ava;
	node*nxt;
	node*lst;
	node*next;
	node*rnxt;
	char name;
	int a;
	int b;
	int c;
};
class banker{
	public:
	banker();
	~banker();
	int mat(node*p);
	int mat2(node*p);
	node*returnp0(){return p0;}
	int bank();
	bool secure(node*p);
	void reboot();
	void test();
	void test2();
	void ask();
	node*p0;
	node*securehead;
	node*head;
	//int Max[3][5];
	//int All[3][5];
	//int Nee[3][5];
	//int Ava[3][1];
	int serial;
	int MAXX[5][3]={
	{7,5,3},
	{3,2,2},
	{9,0,2},
	{2,2,2},
	{4,3,3}
	};
	int ALLL[5][3]={
		{0,1,0},
		{2,0,0},
		{3,0,2},
		{2,1,1},
		{0,0,2}
	};
	int NEEE[5][3]={
		{7,4,3},
		{1,2,2},
		{6,0,0},
		{0,1,1},
		{4,3,1}
	};
	int AVAA[3]={3,3,2};
	int AVAA1[3]={3,3,2};
//void banker::bank(){
	
};

banker::banker(){
	head=new node();
	head->name='h';
	serial=0;
	p0=new node();
	securehead=new node();
	node *curr;
	node *next1;
	curr=p0;
	int num=0;
	while(num<4){		//create 5 programs
		next1=new node();
		curr->nxt=next1;
		next1->lst=curr;
		curr->rnxt=next1;
		curr=next1;
		num++;
	}
	head->nxt=p0;
	p0->lst=head;
	cout<<"structed"<<endl;
	head->nxt->name='0';
	head->nxt->nxt->name='1';
	head->nxt->nxt->nxt->name='2';
	head->nxt->nxt->nxt->nxt->name='3';
	head->nxt->nxt->nxt->nxt->nxt->name='4';
	node*t=head->nxt;
	while(t->nxt!=NULL){
		//cout<<t->name<<endl;
		t=t->nxt;
	}
	//head=new node();
	//cout<<t->name<<endl;
}

banker::~banker(){		//delete programs
	node *curr;
	curr=p0;
	while(curr!=NULL){
		node*next;
		next=curr->nxt;
		delete curr;
		curr =next;
	}
	cout<<"destructed"<<endl;
}

void banker::ask(){
	cout<<"Give these resources to the chosen program: "<<endl;
	cout<<"program: ";
	char a;
	cin>>a;
	int b, c, d;
	cout<<"A resources: ";
	cin>>b;
	cout<<"B resources: ";
	cin>>c;
	cout<<"C resources: ";
	cin>>d;
	char e='0';
	node *thisp=p0;
	while(e!=a){
		//cout<<"what"<<endl;
		thisp=thisp->nxt;
		e++;
	}
	//cout<<"what"<<endl;
	if(b>thisp->nee->a||c>thisp->nee->b||d>thisp->nee->c){
		cout<<"the number of resources you asked is bigger than what you need"<<endl;
	}
	else if(b+thisp->all->a>thisp->max->a||c+thisp->all->b>thisp->max->b||d+thisp->all->c>thisp->max->c)
		cout<<"the number of resources you got is bigger than the max number"<<endl;
	else if(b>AVAA[0]||c>AVAA[1]||d>AVAA[2])
		cout<<"the number of resources you asked is bigger than whatis avalable"<<endl;
	else{
		thisp->all->a+=b;
		thisp->all->b+=c;
		thisp->all->c+=d;
		thisp->nee->a-=b;
		thisp->nee->b-=c;
		thisp->nee->c-=d;
		AVAA[0]-=b;
		AVAA[1]-=c;
		AVAA[2]-=d;
		cout<<"start to give security code"<<endl;
		bank();
	}
}

void banker::test(){
	node*pn;
	pn=p0->nxt;
	cout<<pn->name<<endl;
	cout<<"pn->max->a"<<pn->max->a<<endl;
	cout<<"pn->all->b"<<pn->all->b<<endl;
	cout<<"pn->nee->c"<<pn->nee->c<<endl;
}

int banker::mat(node*p){	//give the first program to this function, make each program linked to the mats
	if(p->nxt==NULL) return 0;
	cout<<"import Max resourses number for p"<<serial<<endl;
	int A, B, C;
	p->max=new node();
	cout<<"A: "; cin>>A; p->max->a=A;
	cout<<"B: "; cin>>B; p->max->b=B;
	cout<<"C: "; cin>>C; p->max->c=C;
	cout<<"import Allocation resourses number for p"<<serial<<endl;
	p->all=new node();
	cout<<"A: "; cin>>A; p->all->a=A;
	cout<<"B: "; cin>>B; p->all->b=B;
	cout<<"C: "; cin>>C; p->all->c=C;
	cout<<"import Needed resourses number for p"<<serial<<endl;
	p->nee=new node();
	cout<<"A: "; cin>>A; p->nee->a=A;
	cout<<"B: "; cin>>B; p->nee->b=B;
	cout<<"C: "; cin>>C; p->nee->c=C;
	serial++;
	mat(p->nxt);
}

int banker::mat2(node*p){
	if(p==NULL) return 0;
	p->max=new node();
	p->all=new node();
	p->nee=new node();
	p->max->a=MAXX[serial][0];
	p->max->b=MAXX[serial][1];
	p->max->c=MAXX[serial][2];
	p->all->a=ALLL[serial][0];
	p->all->b=ALLL[serial][1];
	p->all->c=ALLL[serial][2];
	p->nee->a=NEEE[serial][0];
	p->nee->b=NEEE[serial][1];
	p->nee->c=NEEE[serial][2];
	serial++;
	mat2(p->nxt);
}

void banker::test2(){
	node*t;
	t=head;
	while(t->nxt!=NULL) t=t->nxt;
	cout<<t->name<<endl;
}
int banker::bank(){
	node*p=p0;
	while(1){
		if(p==NULL){
			cout<<"no secure serial number"<<endl;
			return 0;
		}
		if(p->nee->a<=AVAA[0]&&p->nee->b<=AVAA[1]&&p->nee->c<=AVAA[2]){
			securehead->next=p;
			AVAA[0]=AVAA[0]-p->nee->a;
			AVAA[1]=AVAA[1]-p->nee->b;
			AVAA[2]=AVAA[2]-p->nee->c;
			p->all->a+=p->nee->a;
			p->all->b+=p->nee->b;
			p->all->c+=p->nee->c;
			if(secure(p)==true) {
				cout<<"the secure serial is: ";
				node*thisp=securehead->next;
				//if(thisp->nxt->nxt==NULL)cout<<"fuck";
				while(thisp!=NULL){
					cout<<thisp->name<<" ";
					thisp=thisp->next;
				}
				cout<<endl;
				reboot();
			       return 0;	
			}
		}
		p=p->nxt;
		securehead->nxt=NULL;
	}

}


void banker::reboot(){
	//cout<<head->name<<endl;
	node*pp=p0;
	head->nxt=p0;
	while(pp->rnxt!=NULL){
		pp->nxt=pp->rnxt;
		pp->rnxt->lst=pp;
		pp=pp->rnxt;
	}
	AVAA[0]=AVAA1[0];
	AVAA[1]=AVAA1[1];
	AVAA[2]=AVAA1[2];
}
bool banker::secure(node*p){
	/*node*fndp=p0;
	while(1){
		if(fndp==p) break;
		fndp=fndp->nxt;
	}*/
	//securehead->next=p;
	node*thisp;
	if(p->nxt!=NULL)
	{	
		//cout<<"p->lst: "<<p->lst->name<<endl;
		//cout<<"p: "<<p->name<<endl; 
		//cout<<"p->nxt->name: "<<p->nxt->name<<endl;
		p->lst->nxt=p->nxt;
		p->nxt->lst=p->lst;
		//cout<<"head->nxt: "<<head->nxt->name<<endl;
	}
	//cout<<p->name<<endl;
	 if(p->nxt==NULL){
		return true;
	}
	p->nxt=NULL;
	p->lst=NULL;
	//if(head->nxt==NULL) return true;
	//sucurehead->nxt=p;
	AVAA[0]+=p->all->a;
	AVAA[1]+=p->all->b;
	AVAA[2]+=p->all->c;	
	thisp=head->nxt;
	//cout<<"head->nxt="<<thisp->name<<endl;
	//cout<<p->name<<endl;
	//cout<<thisp->name<<endl;
	while(1){
		//cout<<thisp->name<<endl;
		if(thisp==NULL){
			//cout<<"thisp is NULL"<<endl;
			reboot();
			return false;
		}
		//cout<<thisp->name<<endl;
		 if(thisp->nee->a<=AVAA[0]&&thisp->nee->b<=AVAA[1]&&thisp->nee->c<=AVAA[2]){
			 //cout<<thisp->name<<endl;
			//cout<<"thisp is"<<thisp->name<<endl;
			//fndnxp=thisp;
			//cout<<thisp->name<<endl;
			AVAA[0]+=thisp->all->a;
			AVAA[1]+=thisp->all->b;
			AVAA[2]+=thisp->all->c;
			break;
		}
		//cout<<thisp->name<<endl;
		if(thisp->nxt==NULL){
			p->next=thisp;
			return true;
		} 
		thisp=thisp->nxt;
	}
		//cout<<"thisp!=NULL"<<endl;
		//cout<<"p is:"<<p->name<<endl;
		//cout<<"thisp is:"<<thisp->name<<endl<<endl;
		//cout<<thisp->name<<endl;
		p->next=thisp;
		//cout<<thisp->name<<endl;
		secure(thisp);
	/*else{
		return false;
	}*/
	//if(sucurehead->nxt->nxt->nxt->nxt->nxt!=NULL) return true;
}

int main(){
	banker use;
	cout<<"1. give the security code at t0    2.give resources to the program"<<endl;
	int a;
	use.mat2(use.returnp0());
	cin>>a;
	if(a==1) use.bank();
	if(a==2) use.ask();
	//use.bank();
	//use.test2();
	//use.test();
	return 0;
}
