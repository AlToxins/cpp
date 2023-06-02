#include"KCalc.h"
using std::cout;
using std::endl;

int KCalc::s_sum = 0;		//初始化静态成员变量
int main() {		
	KCalc a(20, 10);		//构造函数初始化成员变量
	int x = a.getX();		//传递参数
	int y = a.getY();
	KCalc::add(x, y);		//通过类名+::直接使用静态成员函数
	KCalc::div(x, y);
	KCalc::mul(x, y);
	KCalc::sub(x, y);
	a.displaySum();
	return 0;
}