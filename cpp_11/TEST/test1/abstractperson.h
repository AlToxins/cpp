#ifndef __ABSTRACTPERSON_H__
#define __ABSTRACTPERSON_H__
#include<iostream>
class AbstractPerson {
public:
	virtual void rentHouse() = 0;	//租房请求接口
};

#endif