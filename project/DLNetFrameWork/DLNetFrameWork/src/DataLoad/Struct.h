#ifndef _STRUCT_H_
#define _STRUCT_H_

#define full 0
#define same 1
#define valid 2

//���ݼ��ؽṹ��
typedef struct MinstImg {
	int r;
	int c;
	float** ImgData;	//ͼ�����ݵĶ�ά��̬���飬��ά�ֱ��ʾ�����ݺ�������
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