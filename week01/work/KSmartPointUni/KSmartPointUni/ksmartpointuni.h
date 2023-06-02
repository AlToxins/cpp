#ifndef __KSMARTPOINTUNI_H__
#define __KSMARTPOINTUNI_H__

#include<iostream>
#include<memory>
using std::cout;
using std::endl;

template<typename T>
class KSmartPointUni {
public:
	//KSmartPointUni();
	KSmartPointUni(T* ptr);
	~KSmartPointUni();
	KSmartPointUni(const KSmartPointUni& ptr);	//不允许拷贝
	T& operator*() const;		//取值，返回*m_ptr对象
	T* operator->() const;		//取指针，返回m_ptr对象
	void display();
private:
	T* m_ptr;
};

#endif