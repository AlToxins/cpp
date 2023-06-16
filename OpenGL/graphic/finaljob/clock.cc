/*#include"time.h"
#include<iostream>
using namespace std;
int main(){
	time_t lt,lt2;
	lt=time(NULL);
	cout<<lt<<endl;
	lt2=time(NULL);
	cout<<lt2;
	return 0;
}*/
#include <GL/glut.h>
#include <cmath>

#define HOURHAND (handtype)0
#define MINUTEHAND (handtype)1
#define SECONDHAND (handtype)2
typedef unsigned handtype;

const double Pi = 3.1415926535;
bool leftmousedown = false;
bool clockloop = false; //时钟开始走
int winwidth = 800;
int winheight = 800;
const int CLOCKRADIUS = 120;
const int HOURWIDTH = 5;
const int HOURLENGTH = 55;
const int MINUTEWIDTH = 3;
const int MINUTELENGTH = 80;
const int SECONDWIDTH = 2;
const int SECONDLENGTH = 105;
double hourdegree = 0.0;
double minutedegree = 0.0;
double seconddegree = 0.0;
int xlast = 0, ylast = 0;

void Timer(int);
void Mouse(int, int, int, int);
void Motion(int, int y);
void DrawCircle(int, int x = round(winwidth / 2), int y = round(winheight / 2));
void DrawHand(handtype, int x = round(winwidth / 2), int y = round(winheight / 2));
void Display();
void ChangeSize(int, int);

void Display() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, winwidth, 0, winheight);
	glViewport(0, 0, winwidth, winheight);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	DrawCircle(100);
	DrawHand(HOURHAND); //移动时针
	DrawHand(MINUTEHAND); //移动分针
	DrawHand(SECONDHAND); //移动秒针
	glFlush();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100); //距屏幕左端100px，上端100px
	glutInitWindowSize(winwidth, winheight);
	glutCreateWindow("Clock");
	glutDisplayFunc(Display);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutReshapeFunc(ChangeSize);
	glutMainLoop();
	return 0;
}

void Timer(int value) {
	if (value == 0) { //value用来区别是哪一个定时器. 本程序中只有一个定时器，写不写if没有区别
		minutedegree += 0.1;
		seconddegree += 6;
		hourdegree += (double)1 / 120;
		glutPostRedisplay(); //重新绘制
	}
	if (clockloop) {
		glutTimerFunc(1000, Timer, 0);
	}
}
void Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			leftmousedown = true;
			clockloop = false;
		}
		else
			leftmousedown = false;
	}
	if (button == GLUT_RIGHT_BUTTON) {
		if (state == GLUT_DOWN) {
			if (!clockloop) {
				clockloop = true;
				glutTimerFunc(1000, Timer, 0);
			}
		}
		else
			leftmousedown = false;
	}
}
void Motion(int x, int y) {
	if (leftmousedown) {
		if (y > ylast) {
			minutedegree += 0.1;
			seconddegree += 6;
			hourdegree += (double)1 / 120;
			glutPostRedisplay();
			xlast = x;
			ylast = y;
		}
		else {
			minutedegree -= 0.1;
			seconddegree -= 6;
			hourdegree -= (double)1 / 120;
			glutPostRedisplay();
			xlast = x;
			ylast = y;
		}
	}
}
void DrawCircle(int n, int x, int y) {
	glColor4f(1.0, 0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; ++i)
		glVertex2i(CLOCKRADIUS * cos(2 * Pi / n * i) + x, CLOCKRADIUS * sin(2 * Pi / n * i) + y);
	glEnd();
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glLineWidth(3);
	glBegin(GL_LINES);
	int m = 60;
	for (int i = 0; i < 60; i++) {
		if (m % 12 == 0)
			continue;
		glVertex2i((CLOCKRADIUS - 10) * cos(2 * Pi / m * i) + x, (CLOCKRADIUS - 10) * sin(2 * Pi / m * i) + y);
		glVertex2i(CLOCKRADIUS * cos(2 * Pi / m * i) + x, CLOCKRADIUS * sin(2 * Pi / m * i) + y);
	}
	glEnd();
	glLineWidth(5);
	m = 12;
	glBegin(GL_LINES);
	for (int i = 0; i < 60; i++) {
		glVertex2i((CLOCKRADIUS - 20) * cos(2 * Pi / m * i) + x, (CLOCKRADIUS - 20) * sin(2 * Pi / m * i) + y);
		glVertex2i(CLOCKRADIUS * cos(2 * Pi / m * i) + x, CLOCKRADIUS * sin(2 * Pi / m * i) + y);
	}
	glEnd();
}
void DrawHand(handtype type, int x, int y) {
	glLoadIdentity();
	gluOrtho2D(0, winwidth, 0, winheight); //正交投影
	glViewport(0, 0, winwidth, winheight);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glPushMatrix();
	switch (type)
	{
	case HOURHAND:
		//先将坐标系旋转，再移动至中心位置。所以先写平移矩阵，再写旋转矩阵
		glRotatef(hourdegree, 0, 0, -1);
		glColor4f(0.0, 0.0, 1.0, 1.0);
		glLineWidth(HOURWIDTH);
		glBegin(GL_LINES);
		glVertex2i(0, 0);
		glVertex2i(0, 0 + HOURLENGTH);
		glEnd();
		break;
	case MINUTEHAND:
		glRotatef(minutedegree, 0, 0, -1);
		glColor4f(0.0, 0.0, 1.0, 1.0);
		glLineWidth(MINUTEWIDTH);
		glBegin(GL_LINES);
		glVertex2i(0, 0);
		glVertex2i(0, 0 + MINUTELENGTH);
		glEnd();
		break;
	case SECONDHAND:
		glRotatef(seconddegree, 0, 0, -1);
		glColor4f(0.0, 0.0, 1.0, 1.0);
		glLineWidth(SECONDWIDTH);
		glBegin(GL_LINES);
		glVertex2i(0, 0);
		glVertex2i(0, 0 + SECONDLENGTH);
		glEnd();
		break;
	default:
		break;
	}
	glPopMatrix();
	glPopMatrix();
}
void ChangeSize(int w, int h) {
	winwidth = w;
	winheight = h;
	glViewport(0, 0, w, h);
}

