#include"test2.h"
#include<iostream>

test::test(int memoryVal, int val){
	m_memory = new int(memoryVal);
	m_val = val;
}

test::test(const test& t){
	this->m_memory = new int(*t.m_memory);
	this->m_val = t.m_val;
}

test::~test(){
	delete m_memory;
}

void test::setVal(int memoryVal, int val){
	*m_memory = memoryVal;
	this->m_val = val;
}

void test::displayVal() const{
	std::cout<<"*memory = "<<*m_memory<<" , Val = "<<m_val<<std::endl;
}
