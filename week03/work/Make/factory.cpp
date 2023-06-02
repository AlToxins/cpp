#include"factory.h"

Make* Factory::mk = nullptr;		//静态成员变量只有一个实例，而头文件可能被多个文件包含，因此需要在源文件中定义
Make* Factory::createProduct(std::string select_id) {
	mk = nullptr;
	if (select_id == "火车") {
		mk = new MakeTrain();
	}
	else {
		mk = new MakePlane();
	}
	return mk;
}