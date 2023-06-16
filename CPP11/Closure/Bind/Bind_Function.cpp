#include<iostream>
#include<functional>

void fun(int a, int b) {
	std::cout << "This is a " << a << " and this is b " << b << std::endl;
}

class ClassFun {
public:
	void fun2(int a, int b) {
		std::cout << "This is a in Class " << a << " and this is b in class" << b << std::endl;
	}
};

int main() {
	auto test = std::bind(fun, std::placeholders::_1, 2);		//��ʹ��auto�ȽϷ��㣬 ���ǲ��ܽ�auto���͵Ķ���test���������Ĳ������߷���ֵ�� ��auto�����ƶϺ���ģ��
	test(99);
	ClassFun obj1;
	auto test2 = std::bind(&ClassFun::fun2, obj1, std::placeholders::_1, 3);
	test(991);

	std::function<void(int, int)>normalFunAddr = std::bind(fun, std::placeholders::_1, std::placeholders::_2);		
	normalFunAddr(1, 2);

	ClassFun obj2;
	std::function<void(int)>classMemberFunAddr = std::bind(&ClassFun::fun2, obj2, std::placeholders::_1, 2);		//���ڵڶ��������� ��Ϊ��Ա������Ҫһ����Ա���������ã����Դ���obj2���б�Ҫ��
	classMemberFunAddr(100);
	return 0;

}

