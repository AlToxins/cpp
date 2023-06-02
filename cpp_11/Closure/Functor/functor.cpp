#include<iostream>


class Functor {
public:
	Functor() {
		std::cout << "Functor" << std::endl;
	}

	void operator()() {
		std::cout << "���Էº������÷�" << std::endl;
	}

	int operator()(int a, int b) {
		return a > b ? 1 : 0;
	}
};

template<typename T>
void compare(int a, int b, T& func) {
	if (func(a, b))	std::cout << "x > y" << std::endl;		//����Functor���еĶ�()�����غ���
	else std::cout << "x < y" << std::endl;
}

int main() {
	Functor fun;
	fun();	//����fun.operator()���ڴ˴����õ���û�в������Ǹ�operator()
	compare(1, 2, fun);		//�ڴ˴������в�����operator()
	return 0;
 