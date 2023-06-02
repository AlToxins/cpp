#ifndef __KCOPYABLE_H__
#define __KCOPYABLE_H__
#include"test.h"

class KCopyable {
public:
	KCopyable(int memoryVal);
	KCopyable(const KCopyable& t);
	KCopyable& operator = (const KCopyable& t);
	~KCopyable();
	void displayVal();
private:
	//引用计数类指针
	KReferenceCount* m_pRefCount;
};

#endif