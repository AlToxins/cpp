#ifndef __MAKEPLANE_H__
#define __MAKEPLANE_H__

#include"make.h"

class MakePlane :public Make {
public:
	void make() override {
		cout << "我可以制造飞机" << endl;
	}
};

#endif