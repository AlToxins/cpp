#include<iostream>
#include<cmath>
using namespace std;

struct node{
	node*lst;
	node*nxt;
	node*alst;
	node*anxt;
	char name;
	int serial;
};

class findisk{
	public:
		findisk();
		~findisk();
		void FIFS();	//first in first serve
		void STS();	//shortest track seeking
		void ES();	//elevator scheduler
	private:
		node*head;
		node*end;
		node*ahead;
		node*aend;
		node*F;
};

findisk::findisk(){
	cout<<"job start"<<endl;
	head=new node();	ahead=new node();
	end=new node();		aend=new node();
	head->serial=0;		ahead->serial=90;
	end->serial=0;		aend->serial=0;
	node *A=new node();
	A->name='A';	A->serial=30;
	node *B=new node();
	B->name='B';	B->serial=50;
	node *C=new node();
	C->name='C';	C->serial=100;
	node *D=new node();
	D->name='D';	D->serial=180;
	node *E=new node();
	E->name='E';	E->serial=20;
	F=new node();
	F->name='F';	F->serial=90;
	node *G=new node();
	G->name='G';	G->serial=150;
	node *H=new node();
	H->name='H';	H->serial=70;
	node *I=new node();
	I->name='I';	I->serial=80;
	node *J=new node();
	J->name='J';	J->serial=10;
	node *K=new node();
	K->name='K';	K->serial=160;
	node *L=new node();
	L->name='L';	L->serial=120;
	node *M=new node();
	M->name='M';	M->serial=40;
	node *N=new node();
	N->name='N';	N->serial=110;
	head->nxt=J;	J->lst=head;
	J->nxt=E;	E->lst=J;
	E->nxt=A;	A->lst=E;
	A->nxt=M;	M->lst=A;
	M->nxt=B;	B->lst=M;
	B->nxt=H;	H->lst=B;
	H->nxt=I;	I->lst=H;
	I->nxt=F;	F->lst=I;
	F->nxt=C;	C->lst=F;
	C->nxt=N;	N->lst=C;
	N->nxt=L;	L->lst=N;
	L->nxt=G;	G->lst=L;
	G->nxt=K;	K->lst=G;
	K->nxt=D;	D->lst=K;
	D->nxt=end;	end->lst=D;
	ahead->anxt=A; 	A->alst=ahead;
	A->anxt=B;	B->alst=A;
	B->anxt=C;	C->alst=B;
	C->anxt=D;	D->alst=C;
	D->anxt=E;	E->alst=D;
	E->anxt=F;	F->alst=E;
	F->anxt=G;	G->alst=F;
	G->anxt=H;	H->alst=G;
	H->anxt=I;	I->alst=H;
	I->anxt=J;	J->alst=I;
	J->anxt=K;	K->alst=J;
	K->anxt=L;	L->alst=K;
	L->anxt=M;	M->alst=L;
	M->anxt=N;	N->alst=M;
	N->anxt=aend;	aend->alst=N;
}

findisk::~findisk(){
	node*i=head->nxt;
	while(1){
		i=i->nxt;
		delete i->lst;
		if(i->serial==0)break;
	}
	cout<<"job finish"<<endl;
}

void findisk::FIFS(){
	node*i=ahead->anxt;
	cout<<i->name<<endl;
	int n=0;
	while(1){
		cout<<i->name<<" ";
		n=n+abs(i->serial-i->alst->serial);
		i=i->anxt;
		if(i->serial==0)break;
	}
	cout<<endl<<n<<endl;

}

void findisk::STS(){
	node*i=F;
	int n=0;
	cout<<F->name<<" ";
	//cout<<F->serial<<" ";
		if(i->lst->serial!=0&&i->nxt->serial!=0){
			if(abs(i->serial-i->lst->serial)>=abs(i->nxt->serial-i->serial)){
				cout<<i->nxt->name<<" ";
				i=i->nxt;
				n=n+i->nxt->serial-i->serial;	
				while(1){
					cout<<i->nxt->name<<" ";
					n=n+i->nxt->serial-i->serial;
					i=i->nxt;
					if(i->nxt->serial==0){
						n=n+i->serial-F->lst->serial;
						i=F->lst;
						while(1){
							cout<<i->name<<" ";
							n=n+i->serial-i->lst->serial;
							i=i->lst;
							if(i->serial==0)break;
						}
						break;
					}	
				}
			}
			else{
				cout<<i->lst->name<<" ";
				i=i->lst;
				n=n+i->serial-i->lst->serial;
			}
		}
		
	cout<<endl<<n<<endl;
}

void findisk::ES(){
	cout<<"Start ES"<<endl;
}

int main(){
	findisk a;
	cout<<"FCFS"<<endl;
	a.FIFS();
	cout<<"SSTF"<<endl;
	a.STS();
	cout<<"SCAN"<<endl;
	a.STS();}
