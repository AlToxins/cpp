#include<iostream>
#include<GL/glut.h>
#include<cmath>
using namespace std;
typedef int datatype;

struct node{
	datatype board[3][3]={0, 0, 0, 0, 0, 0, 0, 0, 0};
	node*par;
	node*eld;
	node*sib;
	
};

class ttt{
	public:
		ttt();
		~ttt();
		node* mktree(node*a, int b, int c);		//make a game tree
		void min();		//player o's stragedy
		void max();		//player x's stragedy
		bool minstep(node*a);	//do the step,this func is used in func mktree)
		bool maxstep(node*a);
		node*returnroot();
		void test(node*a);
	private:
		node*root;
};


ttt::ttt(){
	root=new node();
	cout<<"TTT start!"<<endl;
	
}


ttt::~ttt(){
	delete root;
	cout<<"TTT end!"<<endl;
}


bool ttt::minstep(node*a){
	//cout<<"min go"<<endl;
	int i1=0, j1=0;
	while(i1<=2){
		while(j1<=2){
			a->board[i1][j1]=a->par->board[i1][j1];
			j1++;
		}
		i1++;
		j1=0;
	}
	int ifused=1;
	int i=0, j=0;
	while(i<=2){
		while(j<=2){
			if(a->board[i][j]==0){
				ifused=0;
				a->board[i][j]=-1;
				break;
			}
			j++;
		}
		if(ifused==0)break;
		i++;
		j=0;
	}
	if(ifused==0)return true;
	else return false;
}


bool ttt::maxstep(node*a){
	//cout<<"max go"<<endl;
	int i1=0, j1=0;
	while(i1<=2){
		while(j1<=2){
			a->board[i1][j1]=a->par->board[i1][j1];
			j1++;
		}
		i1++;
		j1=0;
	}
	int ifused=1;
	int i=0, j=0;
	while(i<=2){
		while(j<=2){
			if(a->board[i][j]==0){
				ifused=0;
				a->board[i][j]=1;
				break;
			}
			j++;
		}
		if(ifused==0)break;
		i++;
		j=0;
	}
	if(ifused==0)return true;
	else return false;
}

node* ttt::mktree(node*step, int place, int maxormin){	//create gametree, first step is root and place is 9, maxormin is 1, which means max go
	//cout<<"start create gamestree!"<<endl;
	int full=0;
	node*a=new node();
	step->eld=a;
	a->par=step;
	if(maxormin==1){
		if(maxstep(a)==true){
			mktree(a, place-1, 0);
			full++;
		}
		else{
			//cout<<"finish"<<endl;
			return root;
		}
	}
	else if(maxormin==0){
		if(minstep(a)==true){
			mktree(a, place-1, 1);
			full++;
		}
		else{
			//cout<<"finish"<<endl;
			return root;
		}
	}
	 while(1){
		 node*b=new node();
		 a->sib=b;
		 b->par=step;
		 a=b;
		 if(maxormin==1){
		 	if(maxstep(b)==true){
				mktree(b, place-1,0 );
				full++;
			}
			else{
				//cout<<"finish"<<endl;
				return root;
			}
		 }
		 else if(maxormin==0){
		 	if(minstep(b)==true){
				mktree(b, place-1, 1);
				full++;
			}
			else{
				//cout<<"finish"<<endl;
				return root;
			}
		 }
	 	if(full==place){
			//cout<<"gametree has been created!"<<endl;
			return root;
		}
	 }
}

node*ttt::returnroot(){
	return root;
}

void ttt::test(node*root){
	int i=0, j=0;
	while(i<=2){
		while(j<=2){
			cout<<root->eld->eld->sib->sib->board[i][j]<<endl;
			j++;
		}
		i++;
		j=0;
	}
}

int main(){
	ttt a;
	a.mktree(a.returnroot(), 9,1);
	a.test(a.returnroot());
	return 0;
}

