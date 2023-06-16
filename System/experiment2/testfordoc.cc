#include <iostream>
#include <stdlib.h>
#include <pthread.h>
using namespace std;

void* threaddeal(void *arg)
{
cout<<arg<<endl;
pthread_exit(NULL);
}

int main(/*int argc, char *argv[]*/)
{
int i;
pthread_t threadid;	//save thread id

for(i=0;i<10;i++)
{
if(pthread_create(&threadid,NULL,threaddeal,&i)!=0)//pthread_create() function is create the son function
{
cout<<"thread create is failed"<<endl;
exit(0);
}
}
pthread_exit(NULL);
return 0;
}
