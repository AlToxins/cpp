#include"kcomparestringlen.h"

KCompareStringLen::KCompareStringLen(int len) :m_len(len) { ; }

bool KCompareStringLen::operator()(string& s) {
	if (s.size() == m_len) {
		cout << "s.size() 和 m_len 相等" << endl;
		return true;
	}
	else {
		cout << "s.size() 和m_len 不相等" << endl;
		return false;
	}
	//return s.size() == m_len;
}

void KCompareStringLen::inputString(vector<string>& str) {
	int num = 10;
	int i = 0;
	string s;
	while (i < num) {
		cin >> s;
		str.push_back(s);
		i++;
	}
}

void KCompareStringLen::countStringLen(vector<string>& str) {
	int i = 0;
	while (i < 10) {
		cout << "string len = " << str[i].size() << " , " << "cnt = " << i + 1 << endl;;
		i++;
	}
}