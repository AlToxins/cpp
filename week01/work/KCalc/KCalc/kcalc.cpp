#include"kcalc.h"
using std::cout;
using std::endl;


KCalc::KCalc(int x, int y) {
	m_x = x;
	m_y = y;
}

void KCalc::add(int a, int b) {
	s_sum += a + b;		//静态成员函数可以直接访问静态变量，但是由于静态成员函数无this指针，需要通过指定对象访问成员变量
}

void KCalc::sub(int a, int b) {
	s_sum += a - b;
}

void KCalc::mul(int a, int b) {
	s_sum += a * b;
}

void KCalc::div(int a, int b) {
	s_sum += a / b;
}

void KCalc::displaySum()const {
	cout << s_sum << endl;
}

int KCalc::getX() const {
	return m_x;
}

int KCalc::getY() const {
	return m_y;
}