#include"kstring.h"


int main() {
	KString s1("WPS");
	KString s2(s1);
	s1.display();
	s2.display();
	std::cout << "------------------------" << std::endl;
	s1.setString("Welecome");
	s1.display();
	s2.display();
	std::cout << "========================" << std::endl;
	KString s3(s1);
	s1.display();
	s3.display();
	std::cout << "------------------------" << std::endl;
	s1.setString("Hello");
	s1.display();
	s3.display();
	return 0;
}