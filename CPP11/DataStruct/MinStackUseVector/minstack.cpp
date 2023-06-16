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

int MinStack::getMin(const MinStack& stk) {		//将传入的对象设置为只读，避免修改原有对象
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

int MinStack::getMin() {		//原有对象会被修改
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

时间复杂度以及空间复杂度分析：
（1）构造函数的时间复杂度和空间复杂度都是O(1), 因为它并没有进行计算或分配内存
（2）MinStack::push(const it val)的时间复杂度和空间复杂度都是O(1)，因为它只调用了vector的push_back，没有做任何其他计算
（3）MinStack::pop()的时间复杂度和空间复杂度都是O(1), 他仅仅调用了vector的back和pop_back操作
（4）MinStack::top()的时间都咋读和空间复杂度都是O(1), 它只调用了vector的back操作
（5）MinStack::getMin(const MinStack& stk)的时间复杂度和空间复杂度都是是O(n),其中n是m_stk中元素的个数。
	该函数需要创建一个stk的拷贝minStk， 需要占用O(n)的空间（此操作的目的已在注释中说明）
	然后需要对minStk进行依次遍历，找出最小值，故需要占用O(n)的时间
（6）MinStack::getMin()的时间复杂度是O(n)，原因同上，其空间复杂度是O(1), 因为相较于上面的代码，它不用创建原对象的拷贝

*/