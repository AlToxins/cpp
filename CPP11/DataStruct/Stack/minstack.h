#ifndef __MINSTACK_H__
#define __MINSTACK_H__

#include<iostream>

struct Node {
	Node* nxt;
	Node* lst;
	int data;
};

class MinStack {
public:
	MinStack();
	void push(int val);
	int pop();
	int top();
	int getMin();
private:
	Node* m_node;
	Node* m_head;
};

#endif