#ifndef __MAKEPLANE_H__
#define __MAKEPLANE_H__

#include"make.h"

class MakePlane :public Make {
public:
	void make() override {
		cout << "�ҿ�������ɻ�" << endl;
	}
};

#endif