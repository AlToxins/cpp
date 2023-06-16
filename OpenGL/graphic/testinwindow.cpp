//#include<iostream>
#include"GL/freeglut.h"
#include"GL/glut.h"
#include"GL/gl.h"
#include"cmath"
//using namespace std;

/*void  DDAline(int  x0, int  y0, int  x1, int  y1){   
int  dx=x1-x0, dy=y1-y0, epsl, k;   // 横向和纵向上的距离
float  x=x0, y=y0, xIncre, yIncre;
if(abs(dx)>abs(dy)) epsl=abs(dx);
else  epsl=abs(dy);
xIncre=(float)(dx)/epsl;
yIncre=(float)(dy)/epsl;
glBegin(GL_POINTS);
for(k=0;k<=epsl;k++){
glVertex2i((int)(x+0.5), (int)(y+0.5)); // 舍入取整
x+= xIncre;   y+= yIncre; // 每次叠加一个增量
}
glEnd();
}*/


void  MidBhline(int  x0, int  y0, int  x1, int  y1){ 
int  dx, dy, d, UpIncre, DownIncre, x, y;
if(x0>x1){
x=x1; x1=x0; x0=x; y=y1; y1=y0; y0=y;
}
x=x0; y=y0; dx=x1-x0; dy=y1-y0; d=dx-2*dy;
UpIncre=2*dx-2*dy;
DownIncre=-2*dy;
glBegin(GL_POINTS);
while(x<=x1){   
glVertex2i(x, y);
x++;
if(d<0) {
y++; 
d+= UpIncre;
}
else 
d+= DownIncre;
}
glEnd();
}


void  Bhline(int  x0, int  y0, int  x1, int  y1){   
int  x, y, dx, dy, e;
if(x0>x1){
x=x1; x1=x0; x0=x; y=y1; y1=y0; y0=y;
}
dx=x1-x0;  dy=y1-y0;  x=x0;  y=y0;
e=-dx;
glBegin(GL_POINTS);
while(x<=x1){   
glVertex2i(x, y);
x++;
e=e+2*dy;
if(e>0) {
y++;
e=e-2*dx;
}
}
glEnd();
}



void   MidBhcircle( int  r){   
int  x=0, y=r, d=1-r;
glBegin(GL_POINTS);
while ( x<=y ){
glVertex2i ( x, y );    glVertex2i ( y, x );   // 八分画圆
glVertex2i ( -y, x );   glVertex2i ( -x, y );
glVertex2i ( -x, -y );  glVertex2i ( -y, -x );
glVertex2i ( y, -x );   glVertex2i ( x, -y );
if ( d<0)
d+=2*x+3;
else{
d+=2*(x-y)+5;
y--;
}
x++;
}
glEnd();
}


void   MidBhellipse ( int  a, int  b){   
int   x, y;
float  d1, d2;
x=0;  y=b;
d1=b*b+a*a*(-b+0.25);
glBegin(GL_POINTS);
glVertex2i ( x, y );     glVertex2i ( -x, -y ); 
glVertex2i ( -x, y );    glVertex2i ( x, -y );
while ( b*b*(x+1)<a*a*(y-0.5)){   
if ( d1<=0 ) {     
d1+=b*b*(2*x+3);
x++;
}
else{   
d1+=b*b*(2*x+3)+a*a*(-2*y+2);
x++; 
y--;
}
glVertex2i ( x, y );     glVertex2i ( -x, -y ); 
glVertex2i ( -x, y );    glVertex2i ( x, -y ); 
}   /* 上半部*/
d2=b*b*(x+0.5)*(x+0.5)+a*a*(y-1)*(y-1)-a*a*b*b;
while ( y>0 ){   
if ( d2<=0) {   
d2+=b*b*(2*x+2)+a*a*(-2*y+3);
x++;  y--; 
}
else  {   
d2+=a*a*(-2*y+3);   y--;   
}
glVertex2i ( x, y );     glVertex2i ( -x, -y ); 
glVertex2i ( -x, y );    glVertex2i ( x, -y ); 
}
glEnd();
}
void Initial( ){
glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //设置窗口背景颜色为白色
glMatrixMode(GL_PROJECTION); //设置投影参数
gluOrtho2D(-400.0, 400.0, -300, 300.0); // 投影面上的模型坐标范围
}

// 显示图形


void Display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f,1.0f,0.0f);

	//DDAline(0,0,20,20);
	Bhline(0,0,20,20);
	MidBhline(0,0,20,20);
	MidBhcircle(20);
	MidBhcircle(30);
	MidBhcircle(40);
	MidBhellipse(80,40);
	glFlush();
	
}




int main(int argc, char* argv[ ]){
glutInit(&argc, argv); // glut初始化
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//初始窗口显示模式
glutInitWindowSize(800, 600); //设置窗口的尺寸
glutInitWindowPosition(200, 200); //设置窗口的位置
glutCreateWindow("create"); //创建一个窗口

glutDisplayFunc(Display);
Initial(); //完成窗口初始化
glutMainLoop(); //启动主GLUT事件处理循环
return 0;
}

