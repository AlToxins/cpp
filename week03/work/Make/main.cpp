#include"factory.h"

int main() {
	Make* train = Factory::createProduct("��");
	Make* plane = Factory::createProduct("�ɻ�");
	train->make();
	plane->make();
	return 0;
}