/*设计一个全局的整型输出，创建两个子线程
主函数调用join()来回收两个线程资源。程序运行一会儿，手动结束程序
将最终输出的结果存放到文件中，观察添加互斥锁和不添加互斥锁的区别*/

#include<iostream>
#include<thread>
#include<mutex>

int flag = 1;
std::mutex mtx;

void test1(int* buf) {
	int i = 0;
	while (flag) {
		//std::unique_lock<std::mutex>lk(mtx);
		std::cout << buf[i] << std::endl;
		i++;
		if(i==20)i = 0;
	}
}

void test2(int* buf) {
	int i = 19;
	while (flag) {
		//std::unique_lock<std::mutex>lk(mtx);
		std::cout << buf[i] << std::endl;
		i--;
		if (i == -1)i = 19;
	}
}

int main() {
	int buf[20];
	int i = 0;
	while (i < 20) {
		buf[i] = i + 1;
		i++;
	}
	std::thread thread1(test1, buf);
	std::thread thread2(test2, buf);

	std::this_thread::sleep_for(std::chrono::microseconds(100000));
	flag = 0;
	thread1.join();
	thread2.join();
	return 0;
}