#include<iostream>
#include"lift.h"
using namespace std;

elevator::elevator(){
	cout<<"start"<<endl;
	head=new node();
	phead=new node();
	int a=0;
	while(a<maxfloor){	//reset floor
		floor[a]=0;
		a++;
	}
	//cout<<"floor has been reset"<<endl;
	node*b=new node();
	head->nxt=b;
	int d=0;
	while(d<maxlift-1){		//create lifts
		node*c=new node();
		b->nxt=c;
		b=b->nxt;
		d++;
	}
	//d->nxt=head->nxt;		//connect the first and the last elevator
	//cout<<"lifts have been created"<<endl;
	node*e=head->nxt;
	while(e!=NULL){		//reset lift
		int f=0;
		while(f<=maxfloor-1){
			e->mat[f]=0;
			e->backmat[f]=0;
			f++;
		}
		e->currper=0;
		e->currloc=1;
		e->free=1;
		e=e->nxt;
	}
	//cout<<"done"<<endl;
}
elevator::~elevator(){
	int a=0;
	node*b=head;
	while(a<=maxlift){
		node*c=b->nxt;
		delete b;
		b=c;
		a++;
	}
	cout<<"finish";

}

void elevator::ascsort(int*a, int len){
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

void elevator::dessort(int *a, int len)
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

bool elevator::reset(int k){
	if(k>4){
		cout<<"failed"<<endl;
		return false;
	}
	node*a=head->nxt;
	int k1=1;
	while(k1<k){
		a=a->nxt;
		k1++;
	}
	int c=0;
	while(c<maxfloor){	//save old data
		a->backmat[c]=a->mat[c];
		c++;
	}
	int b=0;
	while(b<maxfloor){
		a->mat[b]=0;
		//a->backmat[b]=0;
		floor[b]=0;
		b++;
	}
	a->free=1;
	return true;
}
bool elevator::person(){
	cout<<"How many person?"<<endl;
	int a;
	cin>>a;
	node*b=new node();
	phead->nxt=b;
	b->lst=phead;
	cout<<"where are person1: ";
	int c;
	cin>>c;
	cout<<"where does person1 wants to go: ";
	int d;
	cin>>d;
	if(c>maxfloor||d>maxfloor||c==d)return false;
	b->where=c;
	b->go=d;
	b->carry=0;
	//b->wait=0;
	floor[b->where-1]++;		//add a waiting person
	if(c>d)b->up=0;
	else b->up=1;
	int e=2;
	while(e<=a){
		node*f=new node();
		b->nxt=f;
		f->lst=b;
		cout<<"where are person"<<e<<": ";
		int g;
		cin>>g;
		cout<<"where does person"<<e<<" wants to go: ";
		int h;
		cin>>h;
		if(g>maxfloor||h>maxfloor||g==h) return false;
		f->where=g;
		f->go=h;
		f->carry=0;
		//f->wait=0;
		floor[f->where-1]++;		//add a waiting person
		if(g>h)f->up=0;
		else f->up=1;
		b=b->nxt;
		e++;
	}
	return true;
}

bool elevator::FCFS(node*l, node*p){		//the first reference l is head->nxt, the first reference p is phead->nxt;
	//cout<<"FCFS start"<<endl;
	if(l==NULL){		//after one round, elevator 1 should be free, back to elevator 1
		int m=1;
		while(m<=4){
			reset(m);
			m++;
		}
		l=head->nxt;
	}
	if(p==NULL){
		//cout<<"finish"<<endl;
		return true;
	}
	/*l->mat[b]=p->where;		//first, lift go to person p's floor
	b++;*/
	if(l->currper>=maxperson||l->free==0){		//lift has full, wait for next lift
		FCFS(l->nxt, p);
	}
	int h=0;		//anyone else need to be carried? 0=no, 1=yes
	p->carry=1;
	l->currper++;
	node*a=p->nxt;
	int c=0;		//get how many person need to be carried
	if(a!=NULL){
		while(a!=NULL){		//this is control condition, judge if there was other people need to be carried, h=1 means yes, h=0 means no
			if(p->up==0){		//go down
				//cout<<"godown"<<endl;
				if(a->where<=p->where&&a->up==p->up){
					if(l->currper<maxperson){
						h=1;
						a->carry=1;
						l->currper++;
						c++;
					}
					else{
						FCFS(l->nxt, a);
						//a->wait=1;
						break;
					}
				}
				a=a->nxt; 
			}
			else{		//go up
				//cout<<"goup"<<endl;
				if(a->where>=p->where&&a->up==p->up){
					//cout<<"here2"<<endl;
					if(l->currper<maxperson){
						h=1;
						a->carry=1;
						l->currper++;
						c++;
					}
					else{
						FCFS(l->nxt, a);
						//a->wait=1;
						break;
					}
				}
				a=a->nxt;
			}
		}
	}
	if(h==1){	//case 1, there is other people need been carried
		//cout<<"case1"<<endl;
		c=c+1;
		int len=2*c;
		//cout<<len<<endl;
		int temp[len];	//sort, lift will go to these floors in this serial
		c=0;
		node*d=p;
		while(d!=NULL){		//fill the serial, total length should be len
			if(d->carry==1){
				temp[c]=d->where;
				temp[c+1]=d->go;
				c=c+2;
			}
			d=d->nxt;
		}
		if(p->up==0)	//go down
			dessort(temp,len);		//then sort
		else		//go up
			ascsort(temp,len);		//then sort
		int e=0;
		while(e+1<len){	//remove the same floor
			if(temp[e]==temp[e+1]){
				int f=e+1;
				while(1){
					if(f+1==len)break;
					temp[f]=temp[f+1];
					f++;
				}
				len--;
				e--;
			}
			e++;
		}
		int g=0;
		while(g<len){		//fill l->mat with temp
			l->mat[g]=temp[g];
			g++;
		}	//finish case 1
	}
	else{		//case 2, no another one need to be carried
		//cout<<"case2"<<endl;
		l->mat[0]=p->where;
		l->mat[1]=p->go; 
	}
	node*i=phead->nxt;
	while(i!=NULL){		//remove the person who has been carried
		if(i->nxt!=NULL){
			if(i->carry==1){
				node*j=i->nxt;
				i->lst->nxt=i->nxt;
				i->nxt->lst=i->lst;
				i=j;
			}
			else i=i->nxt;
		}
		else{
			if(i->carry==1){
				i->lst->nxt=NULL;
				break;
			}
			else break;
		}
	}
	l->free=0;
	FCFS(l->nxt, phead->nxt);
}

bool elevator::control(){
	if(person()==true){
		FCFS(head->nxt, phead->nxt);
		return true;
	}
	else return false;
}

void elevator::show(){
	node*a=head->nxt;
	int c=1;
	while(a!=NULL){
		cout<<"lift"<<c<<": ";
		int b=0;
		int d=0, e=0;	//this will check if this lift has old data, e=0 means no, e=1 means yes
		while(d<maxfloor){
			if(a->backmat[d]!=0){
				e=1;
				break;
			}
			d++;
		}
		if(e==1){		//this lift has old data
			int f=0;
			while(f<maxfloor){
				if(/*a->backmat[f]!=0*/1) cout<<a->backmat[f]<<"->";
				f++;
			}
		}
		while(b<maxfloor){
			if(/*a->mat[b]!=0*/1) cout<<a->mat[b]<<"->";
			b++;
		}
		a=a->nxt;
		c++;
		cout<<"->1"<<endl;
	}
}

void elevator::draw(){
	node*l1=head->nxt;
	int z=1;
	while(l1!=NULL){
	cout<<"this is lift"<<z<<endl;
	int n=0;	//find in l->mat[n]
	int f=8;
	int a=0;
	int b=0;
	int y=8;		//tag each floor
	int ifind=0;	//find a and b
	while(a<=maxfloor-1){		//judge the lift is going up or going down
		if(l1->mat[a]==0)a++;
		else{
			b=a+1;
			while(b<=maxfloor-1){
				if(l1->mat[b]==0)b++;
				else{
					ifind=1;
					break;
				}
			}
		}
		if(ifind==1)break;
	}
	//while(f>=0){
		if(l1->mat[a]>l1->mat[b]){	//go down
			//int y=8;	//tag each floor
			int e=1;
			cout<<"go down"<<endl;
			while(f>=1){
				if(f!=l1->mat[n]){
					cout<<"floor"<<y<<"|"<<"           "<<"|"<<endl;
					y--;
					//cout<<f<<" "<<l1->mat[n]<<endl; 
				}
				else{
					cout<<"floor"<<y<<"|"<<" ("<<e<<"time)   |"<<endl;
					y--;
					e++;
					n=n+1;
					while(n<=maxfloor-1){
						if(l1->mat[n]!=0){
							//cout<<"go to "<<l1->mat[n]<<" floor in next step"<<endl;
							break;
						}
						else n++;
					}
				}
				f--;
			}
		}

		else if(l1->mat[a]<l1->mat[b]){		//go up
			int g=0;	//count times
			int h=0;	//count times
			while(h<=maxfloor){
				if(l1->mat[h]==0)h++;
				else{
					g++;
					h++;
				}
			}
			cout<<"go up"<<endl;
			int d=maxfloor-1;
			while(d>=0){
				if(l1->mat[d]!=0)break;
				else d--;
			}
			n=d;
			while(f>=1){
				if(f!=l1->mat[n]){
					cout<<"floor"<<y<<"|"<<"           "<<"|"<<endl;
					y--;
				}
				else{
					cout<<"floor"<<y<<"|"<<" ("<<g<<"time)   |"<<endl;
					y--;
					g--;
					n=n-1;
					while(n>=0){
						if(l1->mat[n]!=0){
							//cout<<"go to"<<l1->mat[n]<<" flooe in next step"<<endl;
							break;
						}
						else n--;
					}
				}
				f--;
			}
		}

		else{
			cout<<"didnt move"<<endl;
			int c=0;
			while(c<maxfloor){
				cout<<"floor"<<y<<"|"<<"           "<<"|"<<endl;
				y--;
				c++;
			}
		}
		l1=l1->nxt;
		z++;
	}
}

int main(){
	elevator a;
	a.control();
	a.show();
	a.draw();
	return 0;
}
