#ifndef __KCALC_H__
#define __KCALC_H__
#include<iostream>


class KCalc {
public:
	KCalc(int x, int y);
	static void add(int a, int b);
	static void sub(int a, int b);
	static void mul(int a, int b);
	static void div(int a, int b);
	void displaySum() const;	//输出s_sum的值
	int getX() const;
	int getY() const;
private:
	int m_x;
	int m_y;
	static int s_sum;	//所有类的对象公用一份，在内存中只有一份拷贝，可以实现多个对象之间的数据共享
};

#endif