#include"proxy.h"

Proxy::Proxy(AbstractPerson* person):m_person(person) { ; }

void Proxy::rentHouse() {
	m_person->rentHouse();
	std::cout << "通过中介寻找房子" << std::endl;
}