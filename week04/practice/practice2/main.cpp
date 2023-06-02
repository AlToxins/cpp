/*������*/

#include<string>
#include<iostream>
#include<thread>
#include<mutex>
std::string str;

int flag = 1;
std::mutex mtx;

void writeHelloThread() {
	while (flag) {
		//std::lock_guard<std::mutex>lk(mtx);	//ʹ�����������ö�����������ڽ���ʱ���ö���������������Զ��Ի�����������н�����lock_guard�Ǳ�unique_lock������������������
		std::unique_lock<std::mutex>lk(mtx);	//��Ҳ��������
		str.clear();
		str = "hello";
		//lk.unlock();
		std::cout << str << std::endl;
		//lk.unlock();
	}
}

void writeCThread() {
	while (flag) {
		//std::lock_guard<std::mutex>lk(mtx);
		std::unique_lock<std::mutex>lk(mtx);
		str.clear();
		str[0] = 'C';
		//lk.unlock();
		std::cout << "str C: " << str <<std::endl;
	}
}

int main() {
	std::thread writeHelloObject(writeHelloThread);
	std::thread writeCObject(writeCThread);

	std::this_thread::sleep_for(std::chrono::microseconds(100000));
	flag = 0;

	writeCObject.join();
	writeHelloObject.join();

	return 0;
}