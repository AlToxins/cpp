#include"kcopyable.h"

KCopyable::KCopyable(int memoryVal) {
	m_pRefCount = new KReferenceCount(memoryVal);
	m_pRefCount->increment();
	std::cout << "m_count + 1 = " << m_pRefCount->m_count << std::endl;
}

//用户自定义的拷贝构造函数，在浅拷贝的基础上实现写时拷贝
KCopyable::KCopyable(const KCopyable& t) {
	m_pRefCount = t.m_pRefCount;
	m_pRefCount->increment();
	std::cout << "m_count + 1 = " << m_pRefCount->m_count << std::endl;
}

KCopyable& KCopyable::operator = (const KCopyable& t) {
	if (this != &t) {
		m_pRefCount->decrement();
		this->m_pRefCount = t.m_pRefCount;		//浅拷贝
		m_pRefCount->displayValue();
		m_pRefCount->increment();
		std::cout << "when using operator =, m_pRefCount + 1 = " << m_pRefCount->m_count << std::endl;
	}
	return *this;
}

void KCopyable::displayVal(){
	m_pRefCount->displayValue();
}

KCopyable::~KCopyable() {
	m_pRefCount->decrement();
	std::cout << "m_count - 1 = " << m_pRefCount->m_count<<std::endl;
}