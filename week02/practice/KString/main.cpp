#include"kstring.h"
#include<string>

int main() {
	const char* str = "hello";
	int len = strlen(str);
	KString str1(str, len);
	KString str2 = std::move(str1);		//move����ֵstr1ת��Ϊ��ֵ����
	cout << str2.getString();	
	return 0;
}