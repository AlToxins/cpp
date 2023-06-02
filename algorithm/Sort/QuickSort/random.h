#include<iostream>
using namespace std;

template<typename t, int number>
class Random {
public:
	t* genRandom(t start, t end) {
		long long* seed = new long long();
		long long* seed2 = new long long();
		long long seedAddr = (long long)&seed;
		long long seedAddr2 = (long long)&seed2;
		seedAddr = seedAddr * seedAddr2;
		cout << seedAddr2 << endl;
		cout << seedAddr << endl;
		int n = 0;
		t mat[14];
		while (n <= 13) {
			mat[n] = (t)(seedAddr % power(10, n + 1) / power(10,n));
			cout << mat[n] << endl;
			n++;
		}
		t *mat2=new t[number];
		t temp=(t)14;
		n = 0;
		int n2=0;	//n2在0到6之间循环
		int change = 1;
		//while (n <= number - 1) {
		//	if (temp < start)temp = 14;
		//	else if (temp > end)temp = (start + end) / 2;
		//	if (mat[n2] == 0) {
		//		mat2[n] = 0;
		//		change = 0;
		//		n++;
		//		n2++;
		//	}
		//	else if (change == 1&&n2<=6) {
		//		temp *= mat[n2];
		//		mat2[n] = temp;
		//		n++;
		//		n2++;
		//		change = 0;
		//	}
		//	else if (change == 0&&n2<=6) {
		//		temp = temp / mat[n2];
		//		mat2[n] = temp;
		//		n++;
		//		n2++;
		//		change = 1;
		//	}
		//	else if(n2 > 6)n2 = 0;
		//}

		while (n <= number - 1) {
			if (temp < start) {
				temp = start;
				mat2[n] = temp;
				n++;
				temp = (start + end)*2;
			}
			else if (temp > end) {
				temp = end;
				mat2[n] = temp;
				n++;
				temp = (start + end) / 4;
			}
			if (mat[n2] == 0) {
				mat2[n] = (start+end)/2;
				n++;
				n2++;
			}
			else if (temp <= mat[n2] && n2 <= 13) {
				temp *= mat[n2];
				mat2[n] = temp;
				n++;
				n2++;
				temp*=3;
			}
			else if (temp > mat[n2] && n2 <= 13) {
				while (temp > end) {
					temp = temp / mat[n2];
				}
				mat2[n] = temp;
				n++;
				n2++;
				temp=temp--;
			}
			else if (n2 > 13)n2 = 0;

		}
		mat2[0] = -11;
		return mat2;
	}

	long long power(long long a, int b) {
		int n = 1;
		long long result=a;
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
