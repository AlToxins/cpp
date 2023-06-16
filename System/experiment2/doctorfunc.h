#include<iostream>
#include<pthread.h>
#include<semaphore.h>
using namespace std;

sem_t testresult;
sem_t testsheet;
int resultval;
int sheetval;

pthread_t seeid;
pthread_t testid;
void*test(void*arg);
void see(){	//arg is the position of the process
	//cout<<"position of the see process"<<arg<<endl;
	cout<<"s1. Ask patient do the test"<<endl;
	cout<<"s2. Wait for the result of test"<<endl;
	sem_post(&testsheet);
	pthread_create(&testid,NULL,test,NULL);
	pthread_join(testid,NULL);
	sem_wait(&testresult);
	sem_getvalue(&testresult,&resultval);
	cout<<"s3. Continue diagnose"<<endl;

}


void*test(void*arg){
	sem_getvalue(&testsheet,&sheetval);
	sem_wait(&testsheet);
	//cout<<"position of the test progress"<<arg<<endl;
	cout<<"t1. Do the test"<<endl;
	sem_post(&testresult);
	cout<<"t2. Giving the test result"<<endl;
	return 0;
}
