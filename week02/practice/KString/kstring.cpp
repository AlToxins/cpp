#include"kstring.h"

KString::KString() {
	m_data = nullptr;
	m_size = 0;
}

KString::KString(const char* str, int len) {
	m_data = new char[len + 1];		//��������ʱ��Ҫ��len+1����Ϊ�ַ���������һ��\n
	int i = 0;
	while (i < len + 1) {
		m_data[i] = str[i];
		i++;
	}
	*m_data = *str;
	m_size = len;
}

KString::KString(KString&& str) {
	if (str.m_data != nullptr) {
		m_data = str.m_data;
		m_size = str.m_size;
		str.m_data = nullptr;
	}
}

KString::~KString() {
	delete m_data;
	m_size = 0;
}

char* KString::getString() {
	return m_data;
}