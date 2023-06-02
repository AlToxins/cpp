#include"movesemantics.h"

#define ASSERT(x) if(!(x)) __debugbreak();\
	//std::cout<<"复制字符串为空"<<std::endl;

//下面实现一个字符串拷贝函数，作用是将第二个字符串拷贝给第一个字符串
//在使用该函数之前是否应该确保两个字符串对象的长度相等？
void String:: strcopy(char* str1, const char* str2) {
	int i = 0;
	while (str2[i] != '\0') {
		str1[i] = str2[i];
		i++;
	}
	str1[i] = '\0';
}

String::String(const char* str) {
	std::cout << "构造函数调用" << std::endl;
	m_size = strlen(str);
	m_str = new char[m_size+1];		//拷贝构造在此处会重新分配空间
	//m_str = str;
	//strcpy(m_str, str);
	strcopy(m_str, str);
}

//函数的参数传递是按值传递的，即函数会创建一个新的对象作为参数的副本，然后在函数内部使用该副本（将实参的值复制给形参，在函数内部使用形参，保护实参不被函数修改），
// 此时会调用拷贝构造函数来创建副本，
//即该函数会自己调用自己，导致无限递归
//但是如果函数的参数是左值引用，则函数不需要创建参数的副本，即不需要创建新的对象，而是直接使用原有的对象
//综上，拷贝构造函数的参数必须是一个常量的左值引用，常量表示源对象不会被修改，左值引用表示直接使用原有的对象
String::String(const String& str) {
	std::cout << "拷贝构造函数调用" << std::endl;
	m_size = str.m_size;
	m_str = new char[m_size + 1];
	strcopy(m_str, str.m_str);
}

//移动构造函数要用noexcept，有以下几个原因：
//noexcept可以指示函数不会抛出异常，提高函数的安全性和效率。
//noexcept可以使得移动构造函数在某些情况下被优先选择，比如在容器中插入或删除元素时，如果移动构造函数是noexcept的，容器会使用移动语义，否则会使用拷贝语义。
//noexcept可以避免在移动构造函数中抛出异常导致程序终止，因为如果移动构造函数抛出异常，而且没有被捕获，那么std::terminate会被调用，终止程序的执行。
String::String(String&& str) noexcept{
	std::cout << "移动构造函数调用" << std::endl;
	m_size = str.m_size;
	//右值引用可以直接转移指针，而左值引用不行，
	//是因为右值引用绑定的是一个临时的、即将销毁的对象，它的资源或状态没有其他对象需要，
	//所以可以直接转移给当前对象，而不会影响其他对象。
	//而左值引用绑定的是一个有名字的、持久的对象，它的资源或状态可能还有其他对象需要，所以不能直接转移给当前对象，而要进行拷贝操作，以保证源对象的完整性。
	m_str = str.m_str;
	str.m_str = nullptr;
	str.m_size = 0;
}

String& String::operator=(const String& str) {
	std::cout << "拷贝运算符调用" << std::endl;
	if (this != &str) {		//避免自赋值
		delete[] m_str;	 //释放原有资源 
		m_size = str.m_size;
		m_str = new char[m_size + 1];
		strcopy(m_str, str.m_str);
	}
	return *this;
}

String& String::operator=(String&& str) noexcept{
	std::cout << "移动运算符调用" << std::endl;
	if (this != &str) {
		delete[] m_str;
		m_size = str.m_size;
		m_str = new char[m_size + 1];
		m_str = str.m_str;
		str.m_size = 0;
		str.m_str = nullptr;
	}
	return *this;
}

String::~String() {
	if (m_str != nullptr) {
		delete[] m_str;
		m_size = 0;
	}
}

void String::display(const String& str) {
	std::cout << str.m_str << std::endl;
}

