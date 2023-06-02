#include"ksmartpointuni.h"


template<typename T>
KSmartPointUni<T>::KSmartPointUni(T* ptr) 
	:m_ptr(ptr)		//”√ptr≥ı ºªØm_ptr
{
	cout << "KSmartPointUni(T* ptr)" << endl;
}

template<typename T>
KSmartPointUni<T>::KSmartPointUni( const KSmartPointUni& ptr){
	cout << "Not allowed" << endl;
}

template<typename T>
KSmartPointUni<T>::~KSmartPointUni() {
	cout << "~KSmartPointUni()" << endl;
	delete m_ptr;
}

template<typename T>
T& KSmartPointUni<T>::operator * () const{
	return *m_ptr;
}

template<typename T> 
T* KSmartPointUni<T>::operator -> () const{
	return m_ptr;
}


template<typename T>
void KSmartPointUni<T>::display() {
	//cout << *m_ptr << endl;
	cout << *m_ptr << endl;
	return;
}


