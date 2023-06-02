#include"minstack.h"

MinStack::MinStack() {
	std::cout << "MinStack" << std::endl;
}

void MinStack::push(const int val) {
	m_stk.push_back(val);
}

int MinStack::pop() {
	int topData = m_stk.back();
	m_stk.pop_back();
	return topData;
}

int MinStack::top() {
	return m_stk.back();
}

int MinStack::getMin(const MinStack& stk) {		//������Ķ�������Ϊֻ���������޸�ԭ�ж���
	MinStack minStk = stk;
	if (!minStk.m_stk.empty()) {
		int currData = minStk.pop();
		int minData;
		while (!minStk.m_stk.empty()) {
			minData = (currData < minStk.top() ? currData : minStk.top());
			minStk.pop();
			currData = minData;
		}
		return currData;
	}
	else {
		std::cout << "Stack is empty" << std::endl;
		return -999;
	}
}

int MinStack::getMin() {		//ԭ�ж���ᱻ�޸�
	if (!this->m_stk.empty()) {
		int currData = this->pop();
		int minData;
		while (!this->m_stk.empty()) {
			minData = (currData < this->top() ? currData : this->top());
			this->pop();
			currData = minData;
		}
		return currData;
	}
	else {
		std::cout << "Stack is empty" << std::endl;
		return -999;
	}
}

/*

ʱ�临�Ӷ��Լ��ռ临�Ӷȷ�����
��1�����캯����ʱ�临�ӶȺͿռ临�Ӷȶ���O(1), ��Ϊ����û�н��м��������ڴ�
��2��MinStack::push(const it val)��ʱ�临�ӶȺͿռ临�Ӷȶ���O(1)����Ϊ��ֻ������vector��push_back��û�����κ���������
��3��MinStack::pop()��ʱ�临�ӶȺͿռ临�Ӷȶ���O(1), ������������vector��back��pop_back����
��4��MinStack::top()��ʱ�䶼զ���Ϳռ临�Ӷȶ���O(1), ��ֻ������vector��back����
��5��MinStack::getMin(const MinStack& stk)��ʱ�临�ӶȺͿռ临�Ӷȶ�����O(n),����n��m_stk��Ԫ�صĸ�����
	�ú�����Ҫ����һ��stk�Ŀ���minStk�� ��Ҫռ��O(n)�Ŀռ䣨�˲�����Ŀ������ע����˵����
	Ȼ����Ҫ��minStk�������α������ҳ���Сֵ������Ҫռ��O(n)��ʱ��
��6��MinStack::getMin()��ʱ�临�Ӷ���O(n)��ԭ��ͬ�ϣ���ռ临�Ӷ���O(1), ��Ϊ���������Ĵ��룬�����ô���ԭ����Ŀ���

*/