#include<iostream>
using namespace std;

template<typename t, int number>
class Random {
public:
	t* genRandom(t start, t end) {
		int* seed = new int();
		int seedAddr = (int)&seed;
		//cout << seedAddr << endl;
		int n = 0;
		t mat[7];
		//cout << seedAddr << endl;
		while (n <= 6) {
			mat[n] = (t)(seedAddr % power(10, n + 1) / power(10,n));
			//cout << mat[n] << endl;
			n++;
		}
		t *mat2=new t[number];
		t temp=(t)14;
		n = 0;
		int n2=0;	//n2在0到6之间循环
		int change = 1;
		while (n <= number - 1) {
			if (temp < start)temp = 14;
			else if (temp > end)temp = (start + end) / 2;
			if (mat[n2] == 0) {
				mat2[n] = 0;
				change = 0;
				n++;
				n2++;
			}
			else if (change == 1&&n2<=6) {
				temp *= mat[n2];
				mat2[n] = temp;
				n++;
				n2++;
				change = 0;
			}
			else if (change == 0&&n2<=6) {
				temp = temp / mat[n2];
				mat2[n] = temp;
				n++;
				n2++;
				change = 1;
			}
			else if(n2 > 6)n2 = 0;

		}
		return mat2;
	}

	int power(int a, int b) {
		int n = 1;
		int result=a;
		if (b == 0)return 1;
		while (n < b) {
			result *=a;
			n++;
		}
		return result;
	}

	void show(int* mat, int size) {
		int n = 0;
		while (n <= size - 1) {
			cout << mat[n] << " ";
			n++;
		}
		cout << endl;
	}
};
