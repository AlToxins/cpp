#include"classfirst.h"


using namespace std;

//extern TryClassSecond g_secondObj;

TryClassFirst::TryClassFirst() {
	//cout << "ClassSecond m_val = " << g_secondObj.getVal() << endl;
	TryClassSecond& getClassObj();		//����֮ǰ��������
	cout << "ClassSecond m_val =" << getClassObj().getVal() << endl;
}

TryClassFirst::~TryClassFirst() {
	cout << "TryClassFirst::~TryClassFirst()" << endl;
}