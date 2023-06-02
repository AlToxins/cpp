#include<iostream>
#include"test2.h"


int main() {
	test a(10, 20);
	test b(a);	//若此时用户不写对应的构造函数，则调用默认的构造函数 test b =a;
	a.displayVal();
	b.displayVal();
	std::cout << "------------------" << std::endl;
	a.setVal(888, 999);
	a.displayVal();
	b.displayVal();
	return 0;
}