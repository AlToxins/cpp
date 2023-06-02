#include"kstring.h"
#include<string>

int main() {
	const char* str = "hello";
	int len = strlen(str);
	KString str1(str, len);
	KString str2 = std::move(str1);		//move将左值str1转化为右值引用
	cout << str2.getString();	
	return 0;
}