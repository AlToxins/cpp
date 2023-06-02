#ifndef __KSTRING_H__
#define __KSTRING_H__

#include<iostream>
using std::cout;
using std::endl;

class KString {
public:
	//将变量都初始化为0
	KString();
	//从堆区申请len个空间，把str字符串内容给m_data，并设置长度
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