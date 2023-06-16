#include"movesemantics.h"

#define ASSERT(x) if(!(x)) __debugbreak();\
	//std::cout<<"�����ַ���Ϊ��"<<std::endl;

//����ʵ��һ���ַ������������������ǽ��ڶ����ַ�����������һ���ַ���
//��ʹ�øú���֮ǰ�Ƿ�Ӧ��ȷ�������ַ�������ĳ�����ȣ�
void String:: strcopy(char* str1, const char* str2) {
	int i = 0;
	while (str2[i] != '\0') {
		str1[i] = str2[i];
		i++;
	}
	str1[i] = '\0';
}

String::String(const char* str) {
	std::cout << "���캯������" << std::endl;
	m_size = strlen(str);
	m_str = new char[m_size+1];		//���������ڴ˴������·���ռ�
	//m_str = str;
	//strcpy(m_str, str);
	strcopy(m_str, str);
}

//�����Ĳ��������ǰ�ֵ���ݵģ��������ᴴ��һ���µĶ�����Ϊ�����ĸ�����Ȼ���ں����ڲ�ʹ�øø�������ʵ�ε�ֵ���Ƹ��βΣ��ں����ڲ�ʹ���βΣ�����ʵ�β��������޸ģ���
// ��ʱ����ÿ������캯��������������
//���ú������Լ������Լ����������޵ݹ�
//������������Ĳ�������ֵ���ã���������Ҫ���������ĸ�����������Ҫ�����µĶ��󣬶���ֱ��ʹ��ԭ�еĶ���
//���ϣ��������캯���Ĳ���������һ����������ֵ���ã�������ʾԴ���󲻻ᱻ�޸ģ���ֵ���ñ�ʾֱ��ʹ��ԭ�еĶ���
String::String(const String& str) {
	std::cout << "�������캯������" << std::endl;
	m_size = str.m_size;
	m_str = new char[m_size + 1];
	strcopy(m_str, str.m_str);
}

//�ƶ����캯��Ҫ��noexcept�������¼���ԭ��
//noexcept����ָʾ���������׳��쳣����ߺ����İ�ȫ�Ժ�Ч�ʡ�
//noexcept����ʹ���ƶ����캯����ĳЩ����±�����ѡ�񣬱����������в����ɾ��Ԫ��ʱ������ƶ����캯����noexcept�ģ�������ʹ���ƶ����壬�����ʹ�ÿ������塣
//noexcept���Ա������ƶ����캯�����׳��쳣���³�����ֹ����Ϊ����ƶ����캯���׳��쳣������û�б�������ôstd::terminate�ᱻ���ã���ֹ�����ִ�С�
String::String(String&& str) noexcept{
	std::cout << "�ƶ����캯������" << std::endl;
	m_size = str.m_size;
	//��ֵ���ÿ���ֱ��ת��ָ�룬����ֵ���ò��У�
	//����Ϊ��ֵ���ð󶨵���һ����ʱ�ġ��������ٵĶ���������Դ��״̬û������������Ҫ��
	//���Կ���ֱ��ת�Ƹ���ǰ���󣬶�����Ӱ����������
	//����ֵ���ð󶨵���һ�������ֵġ��־õĶ���������Դ��״̬���ܻ�������������Ҫ�����Բ���ֱ��ת�Ƹ���ǰ���󣬶�Ҫ���п����������Ա�֤Դ����������ԡ�
	m_str = str.m_str;
	str.m_str = nullptr;
	str.m_size = 0;
}

String& String::operator=(const String& str) {
	std::cout << "�������������" << std::endl;
	if (this != &str) {		//�����Ը�ֵ
		delete[] m_str;	 //�ͷ�ԭ����Դ 
		m_size = str.m_size;
		m_str = new char[m_size + 1];
		strcopy(m_str, str.m_str);
	}
	return *this;
}

String& String::operator=(String&& str) noexcept{
	std::cout << "�ƶ����������" << std::endl;
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

