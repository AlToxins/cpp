#include"abstractperson.h"
#include"proxy.h"
#include"realperson.h"

int main() {
	AbstractPerson* person = new RealPerson;
	AbstractPerson* proxy = new Proxy(person);
	proxy->rentHouse();
	return 0;
}