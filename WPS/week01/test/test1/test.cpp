#include"test.h"
#include<iostream>

KReferenceCount::KReferenceCount(int memoryVal) {
	std::cout << "case1" << std::endl;
	m_paddr = new int(memoryVal);
}

KReferenceCount::KReferenceCount(const KReferenceCount& t) {
	std::cout << "case2" << std::endl;
	//m_paddr = new int();
	//*m_paddr = *t.m_paddr;
	this->m_paddr = new int(*t.m_paddr);		//此处m_paddr的地址是新建的，只是将引用参数t的对象m_paddr的值赋给了m_paddr
	std::cout << *t.m_paddr << std::endl;
}

KReferenceCount::~KReferenceCount() {
	delete m_paddr;
	m_paddr = nullptr;
	m_count = 0;
}

void KReferenceCount::test() {
	std::cout << *m_paddr << std::endl;
}

KReferenceCount& KReferenceCount::operator=(const KReferenceCount& t) {
	if (this != &t) {
		delete m_paddr;
		//m_paddr = new int();
		//*m_paddr = *t.m_paddr;
		m_paddr = new int(*t.m_paddr);
		std::cout << t.m_paddr << std::endl;
		std::cout << m_paddr << std::endl;
		std::cout << *m_paddr << std::endl;
	}
	return *this;
}

void KReferenceCount::increment() {
	++m_count;
}

void KReferenceCount::decrement() {
	--m_count;
	if (m_count == 0) {
		std::cout << "Free Space addr = " << static_cast<void*>(m_paddr) << std::endl;
	}
}

void KReferenceCount::displayValue() {
	std::cout << "*m_memory = " << *m_paddr << ", addr = " << static_cast<void*>(m_paddr) << std::endl;
}
