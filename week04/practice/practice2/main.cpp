/*互斥锁*/

#include<string>
#include<iostream>
#include<thread>
#include<mutex>
std::string str;

int flag = 1;
std::mutex mtx;

void writeHelloThread() {
	while (flag) {
		//std::lock_guard<std::mutex>lk(mtx);	//使用智能锁当该对象的生命周期结束时，该对象的析构函数会自动对互斥锁对象进行解锁。lock_guard是比unique_lock更加重量级的智能锁
		std::unique_lock<std::mutex>lk(mtx);	//这也是智能锁
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