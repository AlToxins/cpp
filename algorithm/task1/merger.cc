#include<iostream>
using namespace std;

const int num=16;

class merger{
	public:
		void createmat();
		int start(int a, int b);
		void show();
	private:
		int mat[num];
		int c1=0;
};


void merger::createmat(){
	cout<<"Insert the numper of mat"<<endl;
	int a;
	int b=0;
	while(1){
		cin>>a;
		if(a==0){
			while(1){
				mat[b]=0;
				b++;
				c1++;
				if(b==num)break;
			}
			break;
		}
		mat[b]=a;
		b++;
		if(b==num)break;
	}
}


int merger::start(int n, int time){	

	if(time==0) return 0;
	int d=0;
	int d1=0;
	while(1){
	
	int a=d;
	int a1=a;
	int b=a+n;	//n=1 at beginnig, n=n*2
	int b1=b;
	int k;		//used for translate
	int k1=0;
	while(1){
		if(mat[a]>mat[b]){
			k=mat[b];
			int c=b;
			while(c>=a+1){	//translate
				mat[c]=mat[c-1];
				c--;
			}
				mat[a]=k;
				a++;
				b++;
		}
		else if(mat[a]<=mat[b]){
			a++;
		}
		k1=k1+1;
		if(b>=a1+2*n||a==b){
			d=d+2*n;
			break;
		}
	}
	d1++;
	if(d1>time-1)break;
	}
	n=n*2;
	start(n, num/(2*n));
}

void merger::show(){
	int a=0;
	if(c1!=0)a=c1;
	while(1){
		cout<<mat[a]<<" ";
		a++;
		if(a==num)break;
	}
}

int main(){
	merger q;
	q.createmat();
	q.start(1,(int)num/2);
	q.show();
	return 0;
}
