#include"minstack.h"

int main() {
	MinStack stk;
	std::cout << "����ջ�����ֵ, ����-999ֹͣ���" << std :: endl;
	int stkData;
	std::cin >> stkData;
	while (stkData != -999) {
		stk.push(stkData);
		std::cin >> stkData;
	}
	std::cout << stk.getMin() << std::endl;
	std::cout << stk.getMin(stk) << std::endl;
	//std::cout << stk.getMin() << std::endl;
	return 0;
}