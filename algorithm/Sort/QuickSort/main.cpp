#define datatype int
#include<iostream>
#include<algorithm>
#include<chrono>
#include"random.h"
using namespace std;



datatype mat[15] = {
	6,3,6,5,4,1,9,8,7,11,54,32,3,87,45
};

void quickSort(datatype *mat,int start, int end) {
	bool stop = false;
	int size1=0, size2;
	//int size = sizeof(&mat)/sizeof(mat[0]);
	int pos=start;
	int k = pos;
	int size = end - start + 1;
	start++;
	while (stop != true) {
		while (mat[pos] <= mat[end] && end != start) {
			end--;
		}
		if (end == start) {
			if (mat[end] >= mat[pos]) {
				stop = true;		//已经分好，全部在标准数的右边
			}
			else {		//完成else后已经分好，全部在标准数的右边
				datatype temp = mat[pos];
				mat[pos] = mat[end];
				mat[end] = temp;
				stop = true;
				pos = end;
			}

		}
		else {
			while (mat[pos] > mat[start] && start != end) {
				start++;
			}
			if (start == end) {//已经分好，全部在标准数的左边
				datatype temp = mat[pos];
				datatype temp2 = pos;
				mat[pos] = mat[end];
				mat[end] = temp;
				stop = true;
				pos = end;
			}
			else {
				datatype temp = mat[start];
				mat[start] = mat[end];
				mat[end] = temp;
			}
			if (end - start == 1) {
				datatype temp2 = mat[pos];
				mat[pos] = mat[start];
				mat[start] = temp2;
				stop = true;
				pos = start;
			}
		}
	}
	size1 = pos-k;
	size2 = size - size1-1;
	if (size1 > 1) quickSort(mat, pos-size1,pos-1);
	if (size2 > 1)quickSort(mat, pos+1, pos+size2);
}

//ctrl + shift + / 

void show(datatype* mat, int size) {
	//int size = sizeof(&mat) / sizeof(mat[0]);
	cout << size << endl;
	int n = 0;
	while (n <= size - 1) {
		cout << mat[n] << " ";
		n++;
	}
	cout << endl;
}

int main() {
	Random<int, 1000>a;
	int* mat = a.genRandom(1, 200);
	a.show(mat, 1000);
	auto start = chrono::steady_clock::now();
	quickSort(mat, 0, 999);
	auto end = chrono::steady_clock::now();
	//秒级
	double duration_second = chrono::duration<double>(end - start).count();
	//毫秒级
	double duration_millsecond = chrono::duration<double, milli>(end - start).count();
	//微秒级
	double duration_microsecond = chrono::duration<double, micro>(end - start).count();
	//纳秒级
	double duration_nanosecond = chrono::duration<double, nano>(end - start).count();
	cout << duration_second << endl;
	show(mat, 1000);
	
}