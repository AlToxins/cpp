#include <iostream>
#include <math.h>
using namespace std;
#define PI 3.1415926

float** tMultiMatrix(float **a, float **b)
{
	float **c = new float*[1];
	c[0] = new float[4];
	for (int j = 0; j < 4; j++)
	{
		for (int k = 0; k < 4; k++)
		{
			c[0][j] += a[0][k] * b[k][j];
		}
		return c;
	}
}

void tTranslation(float &x, float &y,float &z, float xi, float yi,float zi)
{
	x += xi;
	y += yi;
	z += zi;
}

void tRotation(float &x, float &y,float &z, int a,string type) //ÈÆÖ¸¶¨ÖáÐý×ªa½Ç
{
	if (type == "z")
	{
		float temp = x*cos(a) - y*sin(a);
		y = x*sin(a) + y*cos(a);
		x = temp;
	}
	if (type == "x")
	{
		float temp = y*cos(a) - z*sin(a);
		z = y*sin(a) + z*cos(a);
		y = temp;
	}
	if (type == "y")
	{
		float temp = z*sin(a) + x*cos(a);
		z = z*cos(a) - x*sin(a);
		x = temp;
	}
}

void tZoom(float &x, float &y,float &z, float Sx, float Sy,float Sz)
{
	x *= Sx;
	y *= Sy;
	z *= Sz;
}

void tSymmetry(float &x, float &y,float &z, string type)
{
	if (type == "x")
	{
		y = -y;
		z = -z;
	}
	if (type == "y")
	{
		x = -x;
		z = -z;
	}
	if (type == "z")
	{
		x = -x;
		y = -y;
	}
	if (type == "O")
	{
		x = -x;
		y = -y;
		z = -z;
		\
	}
	if (type == "xoy")
		z = -z;
	if (type == "yoz")
		x = -x;
	if (type == "xoz")
		y = -y;
}

void tShear(float &x, float &y,float &z,float d,float g,float b,float h,float c,float f)
{
	float temp = x + d*y + g*z;
	float _temp = b*x + y + h*z;
	z = c*x + f*y + z;
	x = temp;
	y = _temp;
}
