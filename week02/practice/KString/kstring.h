#ifndef __KSTRING_H__
#define __KSTRING_H__

#include<iostream>
using std::cout;
using std::endl;

class KString {
public:
	//����������ʼ��Ϊ0
	KString();
	//�Ӷ�������len���ռ䣬��str�ַ������ݸ�m_data�������ó���
	KString(const char* str, int len);
	KString(KString&& str);
	//KString(char* str);
	~KString();
	char* getString();
private:
	char* m_data;
	int m_size;
};

#endif