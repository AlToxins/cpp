#ifndef __KSTRING_H__
#define __KSTRING_H__
#include<iostream>
class KString {
public:
	KString(const char* memoryVal);
	KString(const KString& t);
	~KString();
	//void increment();
	//void decrement();
	KString& operator = (KString& t);
	void setString(const char* memoryVal);
	void display();
private:
	
	int* m_count = nullptr;
	char* m_str = nullptr;
};

#endif