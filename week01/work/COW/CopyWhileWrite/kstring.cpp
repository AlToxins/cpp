#include"kstring.h"


KString::KString(const char* memoryVal) {
	m_str = new char[strlen(memoryVal)+1];
	int i = 0;
	while (i < strlen(memoryVal)+1) {
		m_str[i] = memoryVal[i];
		i++;
	}
	m_count = new int(1);		//ÿ��Ϊ�µĶ���ֵʱ�����ö����m_countֵ��ʼ��Ϊ1
	//std::cout <<"m_count = " << *m_count << std::endl;
}

//�������캯������ǳ����
KString::KString(const KString& t) {
	m_str = t.m_str;
	m_count = t.m_count;
	(*m_count)++;
	//std::cout << "m_count = " << *m_count << std::endl;
}

//���������
KString& KString::operator=(KString& t) {
	if (this != &t) {
		if (--*m_count == 0) {
			delete [] m_str;
			delete m_count;
		}
		m_str = t.m_str;		//δ�漰��д����������ǳ����
		m_count = t.m_count;
		(*m_count)++;		//���ü�����ԭ���Ļ����ϼ�һ
		//std::cout << "m_count = " << *m_count << std::endl;
	}
	return t;
}

//дʱ�·���ռ�
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