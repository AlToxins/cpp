#include <iostream>
#include <math.h>
#include <string>
using namespace std;
#define PI 3.1415926

float** MultiMatrix(float **a, float **b)
{
	float **c=new float* [1];
	c[0] = new float[3];
	for (int j = 0; j < 3; j++)
	{
		for (int k = 0; k < 3; k++)
		{
			c[0][j] += a[0][k] * b[k][j];
		}
	}
	return c;
}

void Translation(float &x,float &y,float xi, float yi)
{
	x += xi;
	y += yi;
}

void Rotation(float &x, float &y,int a) //绕原点逆时针旋转a角
{
	float temp = x*cos(a*PI / 180) - y*sin(a*PI / 180);
	y = x*sin(a*PI/180) + y*cos(a*PI/180);
	x = temp;
}

void Zoom(float &x, float &y, float Sx, float Sy)
{
	x *= Sx;
	y *= Sy;
}

void Symmetry(float &x, float &y, string type)
{
	if (type == "x")
		y = -y;
	if (type == "y")
		x = -x;
	if (type == "O")
	{
		x = -x;
		y = -y;
	}
	if (type == "y=x")
		swap(x, y);
	if (type == "y=-x")
	{
		float temp = -x;
		x = -y;
		y = temp;
	}
}

void Shear(float &x, float &y, float b, float c)
{
	float temp = x + c*y;
	y = b*x + y;
	x = temp;
}