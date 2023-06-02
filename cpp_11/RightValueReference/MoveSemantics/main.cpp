#include"movesemantics.h"
using std::cout;
using std::endl;
int main() {
	String str1("h");
	String str2(str1);
	String str3(std::move(str1));
	str2 = str3;
	str2 = std::move(str3);
	return 0;
}