#include<iostream>

using std::cout;
using std::endl;
using std::cin;

//输入分别是共有n个猴子，报到第m个猴子退出
//输出是退出的人的编号依次是多少

int main() {
	int m, n;		//n个猴子，报到第m个猴子退出
	cin >> n;
	cin >> m;
	int i = 0;
	int* m_p = new int[n];		//创建n个猴子，值代表每个猴子的编号

	//分配编号
	while (i < n) {
		m_p[i] = i+1;
		i++;
	}

	int m2 = m;		//记录初始的m值
	int temp;		//用于存放当前退出者的编号

	while (n != 1) {
		if (m <= n) {
			cout << m_p[m-1] << " ";		//输出退出者的编号 
			temp = m-1;
			while (temp+1 < n) {		//删掉退出的序号
				m_p[temp] = m_p[temp+1];
				temp++;
			}
			n--;	//剩下的猴子数减1
			m = m2;		//恢复m
		}
		else if (m > n) {
			m = m - n;	//调整m
		}
	}
	delete[]m_p;	//回收内存空间
	return 0;
}

//1 2 3 4 5 6
//5 6 1 3 2