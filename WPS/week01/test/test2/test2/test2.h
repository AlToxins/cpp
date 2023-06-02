#ifndef __TEST2_H__
#define __TEST2_H__

class test {
public:
	test(int memoryVal, int val);
	test(const test& t);
	~test();
	void setVal(int memoryVal, int val);
	void displayVal() const;
private:
	int* m_memory = nullptr;
	int m_val;

};


#endif