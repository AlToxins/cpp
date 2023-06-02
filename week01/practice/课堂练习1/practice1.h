class KIntArray {
public:
	KIntArray(int n);	//在堆区申请n个int类型的空间大小，地址给m_array， 长度给m_len 
	~KIntArray();	//释放堆区空间 

	void inputArray();		//从键盘输入m_len个数据存放到m_array中
	void outputArray();		//输出数据
	
	void deleteData(int data);		//删除data这个数据
private:
	int* m_array;
	int m_len;

};