#include"minstack.h"

MinStack::MinStack(const stack<int>& stk) {
	m_stk = stk;
}


int MinStack::getMin() {
	if (m_stk.empty()) {
		cout << "Stack is empty" << endl;
		return -1;
	}
	else {
		int currData = m_stk.top();
		m_stk.pop();
		int minData;
		while (!m_stk.empty()) {
			minData = (m_stk.top() < currData ? m_stk.top() : currData);
			m_stk.pop();
			currData = minData;
		}
		return currData;
	}
}