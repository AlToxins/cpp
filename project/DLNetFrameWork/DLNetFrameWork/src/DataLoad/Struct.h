#ifndef _STRUCT_H_
#define _STRUCT_H_

#define full 0
#define same 1
#define valid 2

//数据加载结构体
typedef struct MinstImg {
	int r;
	int c;
	float** ImgData;	//图像数据的二维动态数组，二维分别表示行数据和列数据
}MinstImg;

typedef struct MinstImgArr {
	int ImgNum;
	MinstImg* ImgPtr;
}*ImgArr;

typedef struct MinstLabel {
	int l;
	float* LabelData;
}MinstLabel;

typedef struct MinstLabelArr {
	int LabelNum;
	MinstLabel* Labelptr;
}*LabelArr;


#endif