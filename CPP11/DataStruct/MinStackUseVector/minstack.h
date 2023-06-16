#ifndef __MINSTACK_H__
#define __MINSTACK_H__

#include<vector>
#include<iostream>
using std::vector;

class MinStack {
public:
	MinStack();
	void push(const int val);
	int pop();
	int top();
	int getMin(const MinStack& stk);
	int getMin();
private:
	vector<int> m_stk;
};

#endif