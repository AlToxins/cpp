#include"kcomparestringlen.h"

int main() {
	string s = "nihao";
	KCompareStringLen m_s(7);
	m_s(s);
	vector<string>str;
	m_s.inputString(str);
	m_s.countStringLen(str);
	//auto str2 = std::find_if(str.begin(), str.end(), [m_s, s](string str3) {return s.size() == str3.size(); });
	//cout << "��һ�����ȵ���" << s.size() << "����" << *str2 << endl;
	return 0;
}