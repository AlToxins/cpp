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
	KCopyable  obj2(obj1); //�������󣬵ȼ��� Copyable obj2 = obj1, ִ��ϵͳĬ�ϵĿ������캯��

	//����1��obj3��obj1��obj3������ʹ��ͬһ���ڴ档�������ü���Ҳ��3.
	//�������ü�����ԭ�������ü��������0��ʱ��,obj1,obj2��Ӧ�Ŀռ��ͷ��ˡ�
	//obj3���ڴ�ռ�û���ͷš������ڴ�й©
	std::cout << "============================" << std::endl;
	KCopyable  obj3(40);
	obj1.displayVal();
	obj2.displayVal();
	obj3.displayVal();
	std::cout << "=====================" << std::endl;
	obj3 = obj2;
	obj2.displayVal();
	obj3.displayVal();

	

	//obj3 = obj2;  //ϵͳĬ�ϻ����operatr=()��������Ҫ��֮ǰobj3���ڴ��ͷŵ����ٴε���ָ��obj2���ڴ档

	//����2������û�н����Ӧ��ǳ�������ݹ�������⡣дʱ�·���ռ����δ��
	return 0;
}