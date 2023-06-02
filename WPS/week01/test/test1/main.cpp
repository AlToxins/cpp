//#include"KCopyable.h"
//#include<iostream>
//int main() {
//	KReferenceCount a(20);
//	KReferenceCount b(30);
//	//KReferenceCount b = a;
//	a.displayValue();
//	b.displayValue();
//	
//	std::cout << "---------------" << std::endl;
//	b = a;
//	a.displayValue();
//	b.displayValue();
//	std::cout << "===============" << std::endl;
//	KCopyable a1(40);
//	KCopyable b1(a1);
//	a1.displayVal();
//	b1.displayVal();
//	KCopyable c1(50);
//	a1 = c1;
//	std::cout << "---------------" << std::endl;
//	a1.displayVal();
//	b1.displayVal();
//	c1.displayVal();
//
//
//	return 0;
//}

#include "kcopyable.h"
#include<iostream>

int main()
{
	KCopyable  obj1(10);
	KCopyable  obj2(obj1); //拷贝对象，等价于 Copyable obj2 = obj1, 执行系统默认的拷贝构造函数

	//问题1：obj3和obj1，obj3并不是使用同一个内存。但是引用计数也是3.
	//根据引用计数的原理，当引用计数变成了0的时候,obj1,obj2对应的空间释放了。
	//obj3的内存空间没有释放。存在内存泄漏
	std::cout << "============================" << std::endl;
	KCopyable  obj3(40);
	obj1.displayVal();
	obj2.displayVal();
	obj3.displayVal();
	std::cout << "=====================" << std::endl;
	obj3 = obj2;
	obj2.displayVal();
	obj3.displayVal();

	

	//obj3 = obj2;  //系统默认会调用operatr=()函数，需要把之前obj3的内存释放掉，再次调用指向obj2的内存。

	//问题2：还是没有解决对应的浅拷贝数据共享的问题。写时新分配空间代码未定
	return 0;
}