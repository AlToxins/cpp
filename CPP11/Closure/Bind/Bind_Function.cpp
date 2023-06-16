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
	auto test = std::bind(fun, std::placeholders::_1, 2);		//若使用auto比较方便， 但是不能将auto类型的对象test当作函数的参数或者返回值， 且auto不能推断函数模板
	test(99);
	ClassFun obj1;
	auto test2 = std::bind(&ClassFun::fun2, obj1, std::placeholders::_1, 3);
	test(991);

	std::function<void(int, int)>normalFunAddr = std::bind(fun, std::placeholders::_1, std::placeholders::_2);		
	normalFunAddr(1, 2);

	ClassFun obj2;
	std::function<void(int)>classMemberFunAddr = std::bind(&ClassFun::fun2, obj2, std::placeholders::_1, 2);		//关于第二个参数， 因为成员函数需要一个成员对象来调用，所以传递obj2是有必要的
	classMemberFunAddr(100);
	return 0;

}

