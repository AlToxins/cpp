#include"kcalc.h"
using std::cout;
using std::endl;


KCalc::KCalc(int x, int y) {
	m_x = x;
	m_y = y;
}

void KCalc::add(int a, int b) {
	s_sum += a + b;		//��̬��Ա��������ֱ�ӷ��ʾ�̬�������������ھ�̬��Ա������thisָ�룬��Ҫͨ��ָ��������ʳ�Ա����
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