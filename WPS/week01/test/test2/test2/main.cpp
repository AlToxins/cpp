#include<iostream>
#include"test2.h"


int main() {
	test a(10, 20);
	test b(a);	//����ʱ�û���д��Ӧ�Ĺ��캯���������Ĭ�ϵĹ��캯�� test b =a;
	a.displayVal();
	b.displayVal();
	std::cout << "------------------" << std::endl;
	a.setVal(888, 999);
	a.displayVal();
	b.displayVal();
	return 0;
}