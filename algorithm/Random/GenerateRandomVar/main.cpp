#include<iostream>
#include"random.h"
using namespace std;

int main() {
	Random<int, 100> a;		//创建一个数据类型为int，数据个数为100的随机数组
	a.show(a.genRandom(1, 100), 100);
	//int* mat=a.genRandom(1, 100);
	return 0;
}
