#include<iostream>
#include<thread>
#include<Windows.h>
/*void test() {
	std::cout << "try" << std::endl;
}*/

/*main()�����д����������̣߳�Ȼ����1��ȫ�ֱ���������һ���ֲ�����*/

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
	//std::thread test1(test);	//��ֻ�����̵߳��ǲ�������ᵼ�³��򱻶��Ժ����ж�
	int local = 1;

	std::thread test1(globalAdd);		//�����߳�1
	test1.join();
	std::thread test2(localAdd, local);			//�����߳�2
	test2.join();
	//test1.swap(test2);
	std::cout << "no preoblem" << std::endl;
	Sleep(15000);
	return 0;
}