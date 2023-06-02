/*���һ��ȫ�ֵ���������������������߳�
����������join()�����������߳���Դ����������һ������ֶ���������
����������Ľ����ŵ��ļ��У��۲���ӻ������Ͳ���ӻ�����������*/

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