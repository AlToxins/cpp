#ifndef __MAKETRAIN_H__
#define __MAKETRAIN_H__

#include"make.h"

class MakeTrain :public Make {
public:
	void make() override {
		cout << "我可以制造火车" << endl;
	};
};

#endif