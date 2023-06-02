#pragma once
/*
This program can be used to create 2D graphics
*/
#define number 999		//the max number of Lines
#define randomnumber 99999		//the max number of random points
#define PI 3.1415926
int line[number][4];	//储存线段两端点的坐标
int random[randomnumber][4];
int circle[number][4];
int kLine = 0;		//记录直线的条数
int kRandom = 0;	//记录任意线条的条数
int kCircle = 0;	//记录圆形的数目
int WindowWidth = 0;
int WindowHeight = 0;
int selection = 0;
int w;
int ifPushLeftButton = 0;
//int num = 0;


