#include<iostream>
#include"struct.h"


//����ת180��
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

//����ز���
//��������ѡ��full��same��valid���ֱ��ʾ��
//fullָ��ȫ������������СΪinSize+��mapSize-1��
//sameָ����������С��ͬ
//validָ��ȫ������Ĵ�С��һ��ΪinSize-��mapSize-1����С���䲻��Ҫ������������0

float** correlation(float** map, nSize mapSize, float** inputData, nSize inSize, int type) {
	//��������ں��򴫲�ʱ���ã������ڽ�Map��ת180���پ��
	//Ϊ�˷�����㣬������Ҫ��ͼ������һȦ
	//����ľ��Ҫ�ֳ�������ż��ģ��ͼ���ģ��
	float** outputData = new float* ();
	return outputData;
}