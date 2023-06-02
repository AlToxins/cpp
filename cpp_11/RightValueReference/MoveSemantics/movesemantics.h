//--------------------------------------
// ����һ��String�࣬
// ����չʾ��ֵ���������е��ƶ�����
//--------------------------------------

#ifndef __MOVESEMANTICS_H__
#define __MOVESEMANTICS_H__

#include<string>
#include<iostream>

class String {
public:
	//���캯��
	String(const char* str);
	//�������캯��
	String(const String& str);
	//�ƶ����캯��
	String(String&& str) noexcept;
	//������ֵ�����
	String& operator=(const String& str);
	//�ƶ���ֵ�����
	String& operator=(String&& str) noexcept;
	~String();

	static void display(const String& str);
	static void strcopy(char* str1, const char* str2);


private:
	char*m_str;
	int m_size;
};

#endif