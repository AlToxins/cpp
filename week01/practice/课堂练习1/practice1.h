class KIntArray {
public:
	KIntArray(int n);	//�ڶ�������n��int���͵Ŀռ��С����ַ��m_array�� ���ȸ�m_len 
	~KIntArray();	//�ͷŶ����ռ� 

	void inputArray();		//�Ӽ�������m_len�����ݴ�ŵ�m_array��
	void outputArray();		//�������
	
	void deleteData(int data);		//ɾ��data�������
private:
	int* m_array;
	int m_len;

};