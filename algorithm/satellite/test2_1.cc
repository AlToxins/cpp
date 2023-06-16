#include<iostream>
#include<fstream>
using namespace std;
int main(){
	ifstream myfile("D:\\home\\kali\\kaliFiles\\algorithm\\satellite\\satedata\\Sat-1.txt");
	if (!myfile.is_open()){
		cout<<"failed to open"<<endl;
	}
	else cout<<"success"<<endl;
	string temp;
	int k=0;
	while(k<=10){
		getline(myfile,temp);
		cout<<temp<<endl;
		k++;
	}
	myfile.close();
	return 0;
}

