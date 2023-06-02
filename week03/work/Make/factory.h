#ifndef __FACTORY_H__
#define __FACTORY_H__

#include"make.h"
#include"maketrain.h"
#include"makeplane.h"
#include"string"


class Factory {
public:
	static Make* createProduct(std::string  select_id);
	~Factory() {
		delete mk;
	}
private:
	static Make* mk;		//静态函数不依赖于对象
};

#endif