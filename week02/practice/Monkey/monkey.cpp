#include<iostream>

using std::cout;
using std::endl;
using std::cin;

//����ֱ��ǹ���n�����ӣ�������m�������˳�
//������˳����˵ı�������Ƕ���

int main() {
	int m, n;		//n�����ӣ�������m�������˳�
	cin >> n;
	cin >> m;
	int i = 0;
	int* m_p = new int[n];		//����n�����ӣ�ֵ����ÿ�����ӵı��

	//������
	while (i < n) {
		m_p[i] = i+1;
		i++;
	}

	int m2 = m;		//��¼��ʼ��mֵ
	int temp;		//���ڴ�ŵ�ǰ�˳��ߵı��

	while (n != 1) {
		if (m <= n) {
			cout << m_p[m-1] << " ";		//����˳��ߵı�� 
			temp = m-1;
			while (temp+1 < n) {		//ɾ���˳������
				m_p[temp] = m_p[temp+1];
				temp++;
			}
			n--;	//ʣ�µĺ�������1
			m = m2;		//�ָ�m
		}
		else if (m > n) {
			m = m - n;	//����m
		}
	}
	delete[]m_p;	//�����ڴ�ռ�
	return 0;
}

//1 2 3 4 5 6
//5 6 1 3 2