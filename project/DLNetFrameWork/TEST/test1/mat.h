#include<iostream>
#include"struct.h"


//矩阵翻转180度
float** flipMat(float** mat, nSize size) {
	float** output;
	output = (float**)_malloca(sizeof(float*) * size.r);
	int r = 0;
	int c = 0;
	while (r < size.r) {
		output[r] = (float*)_malloca(sizeof(float) * size.c);
		r++;
	}
	r = 0;
	c = 0;
	int a = 0;
	while (r < size.r) {
		while (a < size.c) {
			output[r][a] = mat[size.r - 1 - r][size.c - 1 - a];
			a++;
		}
		r++;
		a = 0;
	}
	return output;
}

void show(float** mat, nSize size) {
	int r = 0, c = 0;
	while (r < size.r) {
		while (c < size.c) {
			std::cout << mat[r][c] << " ";
			c++;
		}
		r++;
		c = 0;
		std::cout << "\n";
	}
}

//互相关操作
//共有三种选择：full、same、valid，分别表示：
//full指完全，操作后结果大小为inSize+（mapSize-1）
//same指输入和输出大小相同
//valid指完全操作后的大小，一般为inSize-（mapSize-1）大小，其不需要将输入后面添加0

float** correlation(float** map, nSize mapSize, float** inputData, nSize inSize, int type) {
	//互相关是在后向传播时调用，类似于将Map翻转180度再卷积
	//为了方便计算，首先需要将图像扩充一圈
	//这里的卷积要分成两拨，偶数模板和技术模板
	float** outputData = new float* ();
	return outputData;
}