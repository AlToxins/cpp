#include"KCalc.h"
using std::cout;
using std::endl;

int KCalc::s_sum = 0;		//��ʼ����̬��Ա����
int main() {		
	KCalc a(20, 10);		//���캯����ʼ����Ա����
	int x = a.getX();		//���ݲ���
	int y = a.getY();
	KCalc::add(x, y);		//ͨ������+::ֱ��ʹ�þ�̬��Ա����
	KCalc::div(x, y);
	KCalc::mul(x, y);
	KCalc::sub(x, y);
	a.displaySum();
	return 0;
}