#include"BasicFunction/BasicData.h"
#include"DataLoad/ReadImg.h"
#include<iostream>


int main(){

	//char* mat=bd::intToChar(7812);
	//char* mat2 = bd::intToChar(6123);
	
	//char*ptr=bd::combineChar(mat, mat2);

	//bd::show(ptr);
	//int a = bd::reverseInt(32767);
	//std::cout << a << std::endl;
	//readImg("MNIST/train-images.idx3-ubyte");
	ImgArr imgArr= readImg("MNIST/train-images.idx3-ubyte");
	saveImg(imgArr, "Data/");
	return 0;
}