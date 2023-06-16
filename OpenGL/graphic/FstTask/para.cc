#include<GL/glut.h>
#include<cmath>
void MidBhparabola(){
	int x, y;
	float d1, d2;
	x=0; y=0;	//initial point
	d1=49.0;		//d10
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	while(y<=49){
		if(d1<=0){
			d1+=100-(2*y+3);
			x++;
			y++;
		}
		else{
			d1-=(2*y+3);
			y++;
		}
		glVertex2i(x,y); glVertex2i(x,-y);

	}
	
	d2=100*(x+1)-(y+0.5)*(y+0.5);
	while(y<=300){
		if(d2<=0){
			d2=d2+100;
			x++;
		}
		else{
			d2=d2+100-2*y-2;
			x++;
			y++;
		}
		glVertex2i(x,y); glVertex2i(x,-y);
	}
	glEnd();	
}
void test(){
	glBegin(GL_POINTS);
	int x, y;
	x=0;
	y=0;
	while(x<=100){
		x++;
		y++;
		glVertex2i ( x,  y );
	}
	glEnd();
}
// 初始化OpenGL场景
void Initial( ){
      glClearColor(1.0f, 1.0f, 1.0f, 1.0f);                  //设置窗口背景颜色为白色
      glMatrixMode(GL_PROJECTION);            //设置投影参数
      gluOrtho2D(-400.0, 400.0, -300, 300.0);      // 投影面上的模型坐标范围
}
 
// 显示图形
void Display(void){
      glClear(GL_COLOR_BUFFER_BIT);   //用当前背景色填充窗口
      // 此处需增加调用基本图形生成函数
      // 例如:
	glColor3f(1.0f, 0.0f, 0.0f);            //设置当前的绘图颜色为红色
   //glRectf(50.0f, 100.0f, 150.0f, 50.0f);  //绘制一个矩形
 	MidBhparabola();
	//test();
      glFlush();      //处理所有的OpenGL程序
}
 
int main(int argc, char* argv[ ]){
      glutInit(&argc, argv);                  // glut初始化
      glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//初始窗口显示模式
      glutInitWindowSize(800, 600);                  //设置窗口的尺寸
      glutInitWindowPosition(200, 200);            //设置窗口的位置
      glutCreateWindow("graphic");      //创建一个窗口
      glutDisplayFunc(Display);            //设置当前窗口的显示回调函数
      Initial();                        //完成窗口初始化
      glutMainLoop();            //启动主GLUT事件处理循环
      return 0;
}
