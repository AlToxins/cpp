#ifndef __PROXY_H__
#define __PROXY_H__

#include"abstractperson.h"

class Proxy :public AbstractPerson {
public:
	Proxy(AbstractPerson* person);
	virtual void rentHouse() override;
public:
	AbstractPerson* m_person;
};

#endif

