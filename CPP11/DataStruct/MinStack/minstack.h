#ifndef __MINSTACK_H__
#define __MINSTACK_H__

#include<iostream>
#include<stack>
using std::cout;
using std::endl;
using std::cin;
using std::stack;

class MinStack {
public:
	MinStack(const stack<int>& stk);
	int getMin();
private:
	stack<int>m_stk;

};

#endif