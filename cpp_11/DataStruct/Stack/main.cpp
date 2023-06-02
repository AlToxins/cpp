#include"minstack.h"

int main() {
	MinStack stack;
	int stack_size = 10;		//将输入的十个数入栈
	int i = 0;
	int data;
	while (i < k) {
		std::cin >> data;
		stack.push(data);
		i++;
	}
	stack.getMin();
	return 0;
}