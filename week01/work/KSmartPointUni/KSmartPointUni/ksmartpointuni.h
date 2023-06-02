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
	KSmartPointUni(const KSmartPointUni& ptr);	//��������
	T& operator*() const;		//ȡֵ������*m_ptr����
	T* operator->() const;		//ȡָ�룬����m_ptr����
	void display();
private:
	T* m_ptr;
};

#endif