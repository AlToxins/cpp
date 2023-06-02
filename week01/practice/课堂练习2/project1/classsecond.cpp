#include<iostream>
#include"classsecond.h"
using namespace std;

TryClassSecond::TryClassSecond():m_val(10) {
	cout << "TryClassSecond()" << endl;
}

TryClassSecond::~TryClassSecond() {
	cout << "~TryClassSecond()" << endl;
}

int TryClassSecond::getVal() const {
	return m_val;
}
 
TryClassSecond & getClassObj() {
	static TryClassSecond g_secondObj;
	return g_secondObj;
}