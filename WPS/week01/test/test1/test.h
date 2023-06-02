#ifndef __TEST_H__
#define __TEST_H__

#include<iostream>

class KReferenceCount {
public:
	KReferenceCount(const KReferenceCount& t);
	KReferenceCount(int memoryVal);
	~KReferenceCount();
	KReferenceCount& operator=(const KReferenceCount& t);		//÷ÿππ
	void increment();
	void decrement();
	void displayValue();
	void test();
	int m_count = 0;
private:
	int* m_paddr = nullptr;
	//int m_count = 0;
};

#endif