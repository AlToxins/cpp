#ifndef __PRODUCT_H__
#define __PRODUCT_H__
#include<iostream>

using std::cout;
using std::endl;

class Product {
public:
	virtual void showProduct() {
		cout << "showProduct" << endl;
	};
};

class ProductMouse :public Product {
public:
	void showProduct() {
		cout << "Create Mouse Product" << endl;
	}
};

class ProductKeyBoard :public Product {
public:
	void showProduct() {
		cout << "Create KeyBoard Product" << endl;
	}
};

class ProductFactory {
public:
	ProductMouse* m = new ProductMouse();		
	ProductKeyBoard* k = new ProductKeyBoard();
	
	Product* CreateProduct(int id) {
		if (id == 1)
			return m;
		else if (id == 2)
			return k;
		else return nullptr;
	}
	
	~ProductFactory() {
		delete m;
		delete k;
	}

};

#endif