#include"minstack.h"

MinStack::MinStack() {
	std::cout << "��ʼ��ʼ��" << std::endl;
	m_node = nullptr;	//����һ��Ԫ�س�ʼ��Ϊ��ֵ��ֱ����һ��pushʱ��Ϊ�����ռ�
	m_head = m_node;
}
void MinStack::push(int val) {
	if (m_head == nullptr) {
		m_node = new Node();
		m_head = m_node;		//ʼ�ս�m_headָ��ջ��
		m_head->data = val;
	}
	else {
		m_head->nxt = new Node();
		m_head->nxt->lst = m_head;
		m_head = m_head->nxt;
		m_head->data = val;
	}
}

int MinStack::pop() {
	if (m_head != nullptr) {
		int topData = m_head->data;
		Node* temp = m_head->lst;
		delete m_head;
		m_head = temp;
		return topData;
	}
	else {
		std::cout << "Stack is empty" << std::endl;
		return 0;
	}
}

int MinStack::top() {
	if (m_head != nullptr)return m_head->data;
	else {
		std::cout << "Stack is empty" << std::endl;
		return 0;
	}
}

int MinStack::getMin() {
	int minData;
	if (m_head != nullptr) {
		int curData = pop();
		if(m_head->lst!=nullptr)
		while (m_head != nullptr) {
			int temp = pop();
			minData = (curData < temp ? curData : temp);
			curData = minData;
		}
		std::cout << "ջ����С��Ԫ��Ϊ��" << minData << std::endl;
		return minData;
	}

	else {
		std::cout << "Stack is empty" << std::endl;
		return 0;
	}
}