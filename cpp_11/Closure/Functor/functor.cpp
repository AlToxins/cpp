#include<iostream>


class Functor {
public:
	Functor() {
		std::cout << "Functor" << std::endl;
	}

	void operator()() {
		std::cout << "测试仿函数的用法" << std::endl;
	}

	int operator()(int a, int b) {
		return a > b ? 1 : 0;
	}
};

template<typename T>
void compare(int a, int b, T& func) {
	if (func(a, b))	std::cout << "x > y" << std::endl;		//调用Functor类中的对()的重载函数
	else std::cout << "x < y" << std::endl;
}

int main() {
	Functor fun;
	fun();	//调用fun.operator()，在此处调用的是没有参数的那个operator()
	compare(1, 2, fun);		//在此处调用有参数的operator()
	return 0;
 