#include <GL/glut.h>
#include <iostream>
using namespace std;
struct point //建立点结构体
{
float x;
float y;
};
struct tpoint //建立三维点结构体
{
float x;
float y;
float z;
};
int edge = 0;  //用于记录多边形的边数
point* points; //用于存储点的信息
tpoint* tpoints;//存储三维点的信息
void Run()
{
glClear(GL_COLOR_BUFFER_BIT);
glBegin(GL_LINES);
glColor3f(0.0, 0.0, 0.0);	//draw x y z
glVertex2i(-800, 0);
glVertex2i(800, 0);
glVertex2i(0, -600);
glVertex2i(0, 600);
glEnd();
glLineWidth(3);
glColor3f(0.0, 1.0, 0.0);
glBegin(GL_LINES);
for (int i = 1; i < edge; i++)
{
for (int j = i; j < edge; j++) {
glVertex2i(points[i - 1].x, points[i - 1].y);
glVertex2i(points[j].x, points[j].y);
}
}
for (int i = edge + 1; i < edge * 2; i++)
{
for (int j = i; j < edge * 2; j++) {
glVertex2i(points[i - 1].x, points[i - 1].y);
glVertex2i(points[j].x, points[j].y);
}
}
for (int i = edge * 2 + 1; i < edge * 3; i++)
{
for (int j =i; j < edge*3; j++) {
glVertex2i(points[i - 1].x, points[i - 1].y);
glVertex2i(points[j].x, points[j].y);
}
}
glEnd();
glFlush();
}
void initial(void)
{
glClearColor(1.0, 1.0, 1.0, 0.0);
glMatrixMode(GL_PROJECTION);
gluOrtho2D(-800.0, 800.0, -600.0, 600.0);
}
void glut(int argc, char* argv)
{
glutInit(&argc, &argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowPosition(200, 100);
glutInitWindowSize(800, 600);
glutCreateWindow("Three demention");
initial();
glutDisplayFunc(Run);
glutMainLoop();
}
int main(int argc, char* argv)
{
cout << "give the points of graphic:";
edge = 0;
cin >> edge;
points = new point[edge*3];
tpoints = new tpoint[edge];
for (int i = 0; i < edge; i++)
{
cout << "input the x y z of point" << i + 1 << endl;
cin >> tpoints[i].x;
cin >> tpoints[i].y;
cin >> tpoints[i].z;
}
for (int i = 0; i < edge; i++)
{
points[i].x = -tpoints[i].x;
points[i].y = -tpoints[i].y;
}
for (int i = 0; i < edge; i++)
{
points[i + edge].x = -tpoints[i].x;
points[i + edge].y = tpoints[i].z;
}
for (int i = 0; i < edge; i++)
{
points[i + edge * 2].x = tpoints[i].y;
points[i + edge * 2].y = tpoints[i].z;
}
glut(argc, argv);
return 0;
}
