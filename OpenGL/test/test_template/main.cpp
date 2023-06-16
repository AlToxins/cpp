#include<iostream>
#include<glut.h>
#include<cmath>
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

using namespace std;



void init() {
	glClearColor(0.0, 0.1, 0.0, 0.0);
	glLineWidth(3.0);
	//glMatrixMode(GL_PROJECTION);
}

void reshape(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);		//设置视区大小
	gluOrtho2D(0, w, 0, h);		//更改窗口坐标系，窗口的左上、左下、右下、右上的坐标分别为(0,h)(0,0)(w,0)(w,h)
	WindowWidth = w;
	WindowHeight = h;
}

void drawLines() {
	int i = 0;
	while (i <= kLine) {
		glBegin(GL_LINES);
		glVertex2i(line[i][0], line[i][1]);
		glVertex2i(line[i][2], line[i][3]);
		i++;
		glEnd();
	}
}



void drawRandom() {
	int i = 0;
	while (i <= kRandom) {
		glBegin(GL_POINTS);
		glVertex2i(random[i][0], random[i][1]);
		glVertex2i(random[i][2], random[i][3]);
		i++;
		glEnd();
	}
}


void mouse(int button, int state, int x, int y) {
	if (selection == 1) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			line[kLine][0] = x;
			line[kLine][1] = WindowHeight - y;
			ifPushLeftButton = 1;
		}
		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			line[kLine][2] = x;
			line[kLine][3] = WindowHeight - y;
			kLine++;
			ifPushLeftButton = 0;
			glutPostRedisplay();
		}
		else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
			line[kLine][0] = line[kLine][2];
			line[kLine][1] = line[kLine][3];
			ifPushLeftButton = 0;
			glutPostRedisplay();
		}
	}
	if (selection == 2) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			random[kRandom][0] = x;
			random[kRandom][1] = WindowHeight - y;
			ifPushLeftButton = 1;
		}
		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			random[kRandom][2] = x;
			random[kRandom][3] = WindowHeight - y;
			ifPushLeftButton = 0;
			glutPostRedisplay();
		}
		else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
			random[kRandom][0] = random[kRandom][2];
			random[kRandom][1] = random[kRandom][3];
			ifPushLeftButton = 0;
			glutPostRedisplay();
		}
	}
	if (selection == 3) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			circle[kCircle][0] = x;
			circle[kCircle][1] = WindowHeight - y;
			ifPushLeftButton = 1;
		}
		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			circle[kCircle][2] = x;
			circle[kCircle][3] = WindowHeight - y;
			kCircle++;
			ifPushLeftButton = 0;
			glutPostRedisplay();
		}
		else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
			circle[kCircle][0] = circle[kCircle][2];
			circle[kCircle][1] = circle[kCircle][3];
			ifPushLeftButton = 0;
			glutPostRedisplay();
		}
	}
}

void motion(int x, int y) {
	if (selection == 1 && ifPushLeftButton != 0) {
		line[kLine][2] = x;
		line[kLine][3] = WindowHeight - y;
		glutPostRedisplay();
	}
	if (selection == 2 && ifPushLeftButton != 0) {
		random[kRandom][2] = x;
		random[kRandom][3] = WindowHeight - y;
		glutPostRedisplay();
		kRandom++;
	}
	if (selection == 3 && ifPushLeftButton != 0) {
		circle[kCircle][2] = x;
		circle[kCircle][3] = WindowHeight - y;
		glutPostRedisplay();
	}
}

void drawCircle() {
	int i = 0;
	float ox, oy, r = 0;
	float array[1440];
	while (i <= kCircle) {
		ox = ((circle[i][0] + circle[i][2]) / 2);
		oy = ((circle[i][1] + circle[i][3]) / 2);
		r = sqrt((circle[i][0] - circle[i][2]) * (circle[i][0] - circle[i][2]) + (circle[i][1] - circle[i][3]) * (circle[i][1] - circle[i][3])) / 2;
		int j = 0;
		float a = 0;	//角度
		while (j <= 1438) {
			array[j] = ox - cos(a) * r;
			array[j + 1] = oy + sin(a) * r;
			j += 2;
			a += 0.5;
		}
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 2 * sizeof(float), array);
		glDrawArrays(GL_LINE_STRIP, 0, 360);
		i++;
	}
	//num = 4;
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.9, 0.5, 0.7);

	drawLines();

	drawRandom();

	drawCircle();

	glutSwapBuffers();
}


void menufunc(int data) {
	//getcurrentmenu();
	//glClear(GL_COLOR_BUFFER_BIT);
	switch (data) {
	case 1:
		selection = 1;
		break;
	case 2:
		selection = 2;
		break;
	case 3:
		selection = 3;
		break;
	}
}



int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(1000, 750);
	w = glutCreateWindow("test");
	init();
	int menu;
	menu = glutCreateMenu(menufunc);
	glutAddMenuEntry("item 1", 1);
	glutAddMenuEntry("item 2", 2);
	glutAddMenuEntry("item 3", 3);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);		//背景菜单栏

	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	glutMainLoop();



	return 0;
}