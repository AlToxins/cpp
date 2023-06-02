#ifndef _READIMG_H_
#define _READIMG_H_

#define ASSERT(x) if(x==1) __debugbreak()


#include"Struct.h"
#include<iostream>
//#include"../BasicFunction/BasicData.h"



ImgArr readImg(const char* filename) {
	FILE* fp = NULL;
	errno_t err;
	err = fopen_s(&fp, filename, "rb");
	ASSERT(err);
	int magic_number = 0;
	int image_number = 0;
	int n_rows = 0;
	int n_cols = 0;

	//从文件中读取sizeof(magic_number)个字符到&magic_number
	fread((char*)&magic_number, sizeof(magic_number), 1, fp);
	magic_number = bd::reverseInt(magic_number);

	//获取训练或测试图像的个数
	fread((char*)&image_number, sizeof(image_number), 1, fp);
	image_number = bd::reverseInt(image_number);

	//获取训练或测试图像的高度
	fread((char*)&n_rows, sizeof(n_rows), 1, fp);
	n_rows = bd::reverseInt(n_rows);

	//获取训练或测试图像的宽度
	fread((char*)&n_cols, sizeof(n_cols), 1, fp);
	n_cols = bd::reverseInt(n_cols);


	//图像数组初始化
	ImgArr imgArr = (ImgArr)_malloca(sizeof(MinstImgArr));
	imgArr->ImgNum = image_number;
	imgArr->ImgPtr = (MinstImg*)_malloca(sizeof(MinstImg) * image_number);


	//读取图像数据到图像数组中
	int i = 0;
	while (i <= image_number - 1) {
		imgArr->ImgPtr[i].c = n_cols;
		imgArr->ImgPtr[i].r = n_rows;
		imgArr->ImgPtr[i].ImgData = (float**)_malloca(sizeof(float*) * n_rows);
		int r = 0;
		while (r <= n_rows - 1) {
			imgArr->ImgPtr[i].ImgData[r] = (float*)_malloca(sizeof(float) * n_cols);
			int c = 0;
			while (c <= n_cols - 1) {
				unsigned char temp = 0;
				fread((char*)&temp, sizeof(temp), 1, fp);
				imgArr->ImgPtr[i].ImgData[r][c] = (float)temp / 255;		//归一化
				//std::cout << imgArr->ImgPtr[i].ImgData[r][c] << std::endl;
				c++;
			}
			r++;
		}
		i++;
	}
	fclose(fp);

	return imgArr;
}

LabelArr readLabel(const char* filename) {
	FILE* fp = NULL;
	errno_t err = fopen_s(&fp, filename, "rb");
	ASSERT(err);

	int magic_number = 0;
	int items_number = 0;
	int label_long = 10;

	fread((char*)&magic_number, sizeof(magic_number), 1, fp);
	magic_number = bd::reverseInt(magic_number);

	fread((char*)&items_number, sizeof(items_number), 1, fp);
	items_number = bd::reverseInt(items_number);

	int i, l;

	LabelArr labelArr = (LabelArr)_malloca(sizeof(MinstLabelArr));
	labelArr->LabelNum = items_number;
	labelArr->Labelptr = (MinstLabel*)_malloca(sizeof(MinstLabel));

	for (i = 0; i < items_number; ++i) {
		labelArr->Labelptr[i].l = 10;
		labelArr->Labelptr->LabelData = (float*)calloc(label_long, sizeof(float));
		unsigned char temp = 0;
		fread((char*)&temp, sizeof(temp), 1, fp);
		labelArr->Labelptr[i].LabelData[(int)temp] = 1.0;
	}

	fclose(fp);
	return labelArr;
}

void saveImg(ImgArr imgArr, const char* filedir) {
	int img_number = imgArr->ImgNum;
	int i, r;
	for (i = 1; i < 2; i++) {
		const char* filename = bd::combineChar(filedir, bd::combineChar(bd::intToChar(i), ".gray"));
		FILE* fp = NULL;
		errno_t err = fopen_s(&fp, filename, "wb");
		ASSERT(err);
		for (r = 0; r < imgArr->ImgPtr[i].r; r++) {
			fwrite(imgArr->ImgPtr[i].ImgData, sizeof(float), imgArr->ImgPtr[i].c, fp);
			fclose(fp);
		}
	}
	std::cout << "Finish" << std::endl;
}



#endif