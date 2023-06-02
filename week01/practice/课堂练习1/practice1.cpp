#include"practice1.h"
#include<iostream>
using namespace std;

KIntArray::KIntArray(int n) {
	m_array = new int[n];
	m_len = n;
}

KIntArray::~KIntArray() {
	delete m_array;
}

void KIntArray::inputArray() {
	cout << "请输入数据";
	int n = 0;
	while (n < m_len) {
		cin >> m_array[n];
		n++;
	}
}

void KIntArray::outputArray() {
	int n = 0;
	cout << "你输入的数据为：";
	while (n < m_len) {
		cout << m_array[n];
		n++;
	}
	cout << endl;
}

void KIntArray::deleteData(int data) {
	int n = 0;
	while (n < m_len) {
		if (data == m_array[n]) {
			int i = n;
			while (i < m_len - 1) {
				m_array[i] = m_array[i + 1];
				i++;
			}
			m_len--;
		}
		n++;
	}
	cout << "新的data: " << endl;
	n = 0;
	while (n < m_len) {
		cout << m_array[n];
		n++;
	}
}