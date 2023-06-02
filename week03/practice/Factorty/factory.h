#ifndef __FACTORY_H__
#define __FACTORY_H__
#include<iostream>


class Factory {
public:
	virtual void engine() = 0;
	virtual void tyre() = 0;
};

class Train :public Factory{
public:
	virtual void engine() override;
	virtual void tyre() override;
};

class Plane :public Factory{
public:
	virtual void engine() override;
	virtual void tyre() override;
};
#endif