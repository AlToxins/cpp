#include"minstack.h"

int main() {
	stack<int>stk1;
	cout << "请向栈中添加值，输入-999停止输入" << endl;
	int numInStk;
	cin >> numInStk;
	while (numInStk != -999) {
		stk1.push(numInStk);
		cin >> numInStk;
	}
	MinStack stk2(stk1);
	cout << stk2.getMin() << endl;
	return 0;
}