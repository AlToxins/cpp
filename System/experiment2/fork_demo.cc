#include <cstring>
#include <iostream>
#include <unistd.h>
using namespace std;
int main(){
        pid_t pid;
        int i=0;

        pid = fork();//pid is retern number of function fork(); function fork();is to create the son process, when fork() has been called, son process and father process will do the next order
        if(pid == 0){
                while(1){
                        i = i-1;
                        cout<<i<<":"<<"son process return "<<pid<<endl;//when pid==0,fork() return to the son process, function getpid() return the ID serial
			execl("./hello","hello",NULL);
			//exit(1);
			if(i==-100)break;
                        }
                }
        else if(pid>0){
                while(1){
                         i++;
                        cout<<i<<":"<<"<father process return "<<pid<<endl;//when pid>0,fork() return the father process
			if(i==100) break;
                        }
                }
        else cout<<"failed to create process"<<endl;
        return 0;
}

