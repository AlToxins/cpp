#ifndef __KCOMPARESTRINGLEN_H__
#define __KCOMPARESTRINGLEN_H__
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>


using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::cin;


class KCompareStringLen {
public:
	KCompareStringLen(int len);
	bool operator()(string &s);
	void inputString(vector<string>& str);
	void countStringLen(vector<string>& str);
private:
	int m_len;
};

#endif