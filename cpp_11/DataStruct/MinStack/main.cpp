#include"minstack.h"

int main() {
	stack<int>stk1;
	cout << "����ջ�����ֵ������-999ֹͣ����" << endl;
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