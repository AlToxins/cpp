#include<iostream>
#include"random.h"
using namespace std;

int main() {
	Random<int, 100> a;		//����һ����������Ϊint�����ݸ���Ϊ100���������
	a.show(a.genRandom(1, 100), 100);
	//int* mat=a.genRandom(1, 100);
	return 0;
}
