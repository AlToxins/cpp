#include"kcopyable.h"

KCopyable::KCopyable(int memoryVal) {
	m_pRefCount = new KReferenceCount(memoryVal);
	m_pRefCount->increment();
	std::cout << "m_count + 1 = " << m_pRefCount->m_count << std::endl;
}

//�û��Զ���Ŀ������캯������ǳ�����Ļ�����ʵ��дʱ����
KCopyable::KCopyable(const KCopyable& t) {
	m_pRefCount = t.m_pRefCount;
	m_pRefCount->increment();
	std::cout << "m_count + 1 = " << m_pRefCount->m_count << std::endl;
}

KCopyable& KCopyable::operator = (const KCopyable& t) {
	if (this != &t) {
		m_pRefCount->decrement();
		this->m_pRefCount = t.m_pRefCount;		//ǳ����
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