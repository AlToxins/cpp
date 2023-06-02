//#include<iostream>
//#include<cstdio>

//int power(unsigned int n) {
//	int result = 10;
//	if (n == 0) return 1;
//	else if (n == 1) return result;
//	else if (n > 1) {
//		unsigned int k = 1;
//		while (k < n) {
//			result = result * 10;
//			k++;
//		}
//		return result;
//	}
//}
//
//char* intToChar(int i) {		//注意传入的参数不能超过int的范围
//		//将整型数转换为字符串
//	int j = i;
//	unsigned int n = 0;
//	while (j != 0) {
//		j = i;
//		n++;
//		j = j / power(n);
//	}
//	char* array = (char*)_malloca(n + 1);
//	j = 0;
//	while (j < n) {
//		array[n - 1 - j] = (char)(i % power(j + 1) / power(j) + 48);
//		//std::cout << (int)&array[n - 1 - j] << " ";
//		j++;
//	}
//	array[n] = '\0';
//	return array;
//}
//
//
//char* combineChar(const char* a, const char* b) {
//	int lena = strlen(a), lenb = strlen(b);
//	//std::cout << lena << std::endl << lenb << std::endl;
//	char* ptr = (char*)_malloca((lena + lenb + 1) * sizeof(char));
//	int i = 0, l = -1;
//	while (i < lena) {
//		l++;
//		ptr[l] = a[i];
//		//std::cout << ptr[l] << " ";
//		i++;
//	}
//	i = 0;
//	while (i < lenb) {
//		l++;
//		ptr[l] = b[i];
//		//std::cout << ptr[l] << " ";
//		i++;
//	}
//	l++;
//	ptr[l] = '\0';
//	return ptr;
//}
//
//int main() {
//	const char *savePath = "D:/code/cpp/project/DLNetFrameWork/DLNetFrameWork/Data/";
//	int number=31023;
//	const char* back = ".gray";
//	while (number <= 59999) {
//		const char* path = combineChar(savePath, intToChar(number));
//		path = combineChar(path, ".gray");
//		//std::cout << path << std::endl;
//		if (remove(path) == 0) std::cout << "success" << std::endl;
//		else std::cout << "failed" << std::endl;
//		number++;
//	}
//	return 0;
//}






#include<iostream>
#include"mat.h"



int main() {
	//首先创建一个二维数组用于测试
	int row = 5;
	int column = 5;
	float** mat;
	mat = (float**)_malloca(sizeof(float*) * row);
	int r = 0;
	while (r < row) {
		mat[r] = (float*)_malloca(sizeof(float) * column);
		r++;
	}
	int c = 0;
	r = 0;
	int i = 0;
	while (r <row) {
		while (c <column) {
			mat[r][c] = i;
			i++;
			std::cout << mat[r][c] << " ";
			c++;
		}
		r++;
		std::cout<< std::endl;
		c = 0;
	}
		//mat已经创建完毕

std::cout << "\n";
	//接下来开始测试翻转矩阵180度，首先设置矩阵的长和宽
	nSize size;
	size.r = 5;
	size.c = 5;
	show(flipMat(mat, size), size);
}