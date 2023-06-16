#include"kstring.h"


KString::KString(const char* memoryVal) {
	m_str = new char[strlen(memoryVal)+1];
	int i = 0;
	while (i < strlen(memoryVal)+1) {
		m_str[i] = memoryVal[i];
		i++;
	}
	m_count = new int(1);		//每次为新的对象赋值时，将该对象的m_count值初始化为1
	//std::cout <<"m_count = " << *m_count << std::endl;
}

//拷贝构造函数，是浅拷贝
KString::KString(const KString& t) {
	m_str = t.m_str;
	m_count = t.m_count;
	(*m_count)++;
	//std::cout << "m_count = " << *m_count << std::endl;
}

//运算符重载
KString& KString::operator=(KString& t) {
	if (this != &t) {
		if (--*m_count == 0) {
			delete [] m_str;
			delete m_count;
		}
		m_str = t.m_str;		//未涉及到写操作，进行浅拷贝
		m_count = t.m_count;
		(*m_count)++;		//引用计数在原来的基础上加一
		//std::cout << "m_count = " << *m_count << std::endl;
	}
	return t;
}

//写时新分配空间
void KString::setString(const char* memoryVal) {
	if (*m_count > 1) {
		(*m_count)--;
		m_str = new char[strlen(memoryVal) + 1];
		int i = 0;
		while (i < strlen(memoryVal) + 1) {
			m_str[i] = memoryVal[i];
			i++;
		}
		m_count = new int(1);
	}
}

void KString::display() {
	std::cout << "m_str = " << m_str << " ,addr = " << static_cast<void*>(m_str) << std::endl;
}

KString::~KString() {
	if (-- * m_count == 0) {
		std::cout << "Delete addr: " << static_cast<void*>(m_str) << std::endl;
		delete[] m_str;
	}
}