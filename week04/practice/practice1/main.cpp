#include<iostream>
#include<thread>
#include<Windows.h>
/*void test() {
	std::cout << "try" << std::endl;
}*/

/*main()函数中创建两个子线程，然后定义1个全局变量，定义一个局部变量*/

int global = 10;

void globalAdd() {
	int i = 0;
	while (i < 5) {
		global++;
		Sleep(1000);
		i++;
	}
	std::cout << global << std::endl;
}

void localAdd(int local) {
	local++;
	std::cout << local << std::endl;
}
 


int main() {
	//std::thread test1(test);	//若只创建线程但是不做处理会导致程序被断言函数中断
	int local = 1;

	std::thread test1(globalAdd);		//创建线程1
	test1.join();
	std::thread test2(localAdd, local);			//创建线程2
	test2.join();
	//test1.swap(test2);
	std::cout << "no preoblem" << std::endl;
	Sleep(15000);
	return 0;
}