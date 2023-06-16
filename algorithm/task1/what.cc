#include<iostream>
#include"math.h"
#include<iomanip>
#include<algorithm>
using namespace std;


int fact(int a){	//!
	int b=1;
	while(1){
		b=b*a;
		a--;
		if(a==0)break;
	}
	return b;
}
int main(){
	//give the first line
	int n, m, d;
	cout<<"input the number of n, m, d"<<endl;
	cin>>n;
	//cout<<"input the number of m"<<endl;
	cin>>m;
	//cout<<"input the number of d"<<endl;
	cin>>d;
	if(n<1||n>5||m<1||m>5||d<1||d>100){
		cout<<"no result"<<endl;
		return 0;
	}

	//give the second and third line
	int matn[5], matm[5];
	int a=n;
	int b=m;
	int c=0;
	cout<<"input the stone number of each heap (n)"<<endl;
	while(c<n){
		cin>>matn[c];
		if(matn[c]<1||matn[c]>6){
			cout<<"no result"<<endl;
			return 0;
		}
		c++;
	}
	c=0;
	cout<<"input the stone number of each heap (m)"<<endl;
	while(c<m){
		cin>>matm[c];
		if(matm[c]<1||matm[c]>6){
			cout<<"no result"<<endl;
			return 0;
		}
		c++;
	}
	sort(matm, matm+m-1);
	sort(matn, matn+n-1);
	c=0;
	int all=0;
	while(c<m){
		all+=matm[c];
		c++;
	}
	int allm=all;
	c=0;
	while(c<n){
		all+=matn[c];
		c++;
	}
	float p;
	if(d>=all){
		cout<<"case 1: p=1";
		return 0;
	}
	else if(d<allm){
		cout<<"case 2: p=0";
		return 0;
	}
	else{
		/*float x=fact(all);
		float y=fact(allm);
		float z=fact(all-allm);
		p=1/(x/y/z)*n*m;
		//p=1/(fact(all)/(fact(allm)*fact(all-allm)))*allm;
		cout<<"case 3: p="<<fixed<<setprecision(4)<<p;*/
		if(d==allm){
			p=1;
			int k=0;
			int m1=m;
			int k1=m+n;
			while(1){
				p=p*pow((float)m/k1,matm[k]);
				k1--;
				m--;
				k++;
				if(k==m1)break;
			}
			cout<<"case 3: p="<<fixed<<setprecision(4)<<p;
			
		}
		else if(d>allm){
		
			float p2=1;
			float p1=1;
			int k11=0;
			int m1=m;
			int k111=m+n;
			while(1){
				p1=p1*pow((float)m/k111,matm[k11]);
				k111--;
				m--;
				k11++;
				if(k11==m1)break;
			}
			int d1=d-allm;
			if(d1>*min_element(matn,matn+n-1)){
				p2=p1+p1*pow((float)n/(m+n),d1);
				cout<<"case 3: p="<<fixed<<setprecision(4)<<p2;
			}	
			else return 0;
		}
		return 0;
	}
	

}

/*#include <iostream>
#include <algorithm>

using namespace std;

int n, m, u, v;
int alr, total;
long long ans;

const int MAXN = 5005;
const int MAXM = 200005;

int f[MAXN];

struct edge {
    int fr;
    int to;
    int val;
}e[MAXM];

inline int find(int x) {
    while (x != f[x]) x = f[x] = f[f[x]];
    return x;
}

inline void kruskal() {
    for (int i = 0; i < m; i++) {
        u = find(e[i].fr);
        v = find(e[i].to);
        if (u == v) continue;
        ans += e[i].val;
        f[u] = v;
        total++;
        if (total == m-1) break;
    }
}
      
bool comp(edge a, edge b) {
    return a.val < b.val;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        f[i] = i;
    }

    for (int i = 0; i < m; i++) {
        cin >> e[i].fr >> e[i].to >> e[i].val;
    }
    sort(e, e+m, comp);
    kruskal();
    cout << ans << endl;
}*/
