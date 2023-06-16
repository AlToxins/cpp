#include"doctorfunc.h"
#include<iostream>
#include<pthread.h>
using namespace std;
int main(){
	if(sem_init(&testsheet,0,1)){
		cout<<"initial failed"<<endl;
		return 1;
	}
	else if(sem_init(&testresult,0,1)){
		cout<<"initial failed"<<endl;
		return 1;
	}
	see();
	cout<<"Done"<<endl;
	return 0;
}
