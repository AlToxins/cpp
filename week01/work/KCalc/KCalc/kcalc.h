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
	void displaySum() const;	//���s_sum��ֵ
	int getX() const;
	int getY() const;
private:
	int m_x;
	int m_y;
	static int s_sum;	//������Ķ�����һ�ݣ����ڴ���ֻ��һ�ݿ���������ʵ�ֶ������֮������ݹ���
};

#endif