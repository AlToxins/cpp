#include"factory.h"

int main() {
	Make* train = Factory::createProduct("»ğ³µ");
	Make* plane = Factory::createProduct("·É»ú");
	train->make();
	plane->make();
	return 0;
}