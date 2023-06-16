#include "stdio.h"
#include<iostream> 
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp> 
using namespace cv;
int main()
{
    Mat img = imread("D://1.bmp");
    namedWindow("≤‚ ‘opencv");
    imshow("≤‚ ‘opencv", img);
    cvWaitKey(1);
}