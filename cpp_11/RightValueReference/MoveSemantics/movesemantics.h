//--------------------------------------
// 定义一个String类，
// 用于展示右值引用所具有的移动语义
//--------------------------------------

#ifndef __MOVESEMANTICS_H__
#define __MOVESEMANTICS_H__

#include<string>
#include<iostream>

class String {
public:
	//构造函数
	String(const char* str);
	//拷贝构造函数
	String(const String& str);
	//移动构造函数
	String(String&& str) noexcept;
	//拷贝赋值运算符
	String& operator=(const String& str);
	//移动赋值运算符
	String& operator=(String&& str) noexcept;
	~String();

	static void display(const String& str);
	static void strcopy(char* str1, const char* str2);


private:
	char*m_str;
	int m_size;
};

#endif