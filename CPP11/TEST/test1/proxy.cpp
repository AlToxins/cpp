#include"proxy.h"

Proxy::Proxy(AbstractPerson* person):m_person(person) { ; }

void Proxy::rentHouse() {
	m_person->rentHouse();
	std::cout << "ͨ���н�Ѱ�ҷ���" << std::endl;
}