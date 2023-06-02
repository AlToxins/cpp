#include"product.h"

int main() {
	ProductFactory pf;
	pf.CreateProduct(1)->showProduct();
	pf.CreateProduct(2)->showProduct();
	return 0;
}