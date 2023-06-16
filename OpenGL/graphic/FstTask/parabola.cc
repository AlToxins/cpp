#include<GL/glut.h>
#include<cmath>
/*void   MidBhellipse ( int  a, int  b){   
      int   x, y;
      float  d1, d2;
      x=0;  y=b;
      d1=b*b+a*a*(-b+0.25);
      glBegin(GL_POINTS);
      glVertex2i ( x, y );     glVertex2i ( -x, -y ); 	
      glVertex2i ( -x, y );    glVertex2i ( x, -y );
      while ( b*b*(x+1)<a*a*(y-0.5)){	//decide the pre part
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
      }   
      d2=b*b*(x+0.5)*(x+0.5)+a*a*(y-1)*(y-1)-a*a*b*b;
      while ( y>0 ){  			//decide thr pst part
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
}*/

void	test(int x, int y){
	while(x<=100){
		x++;
		y++;
		glVertex2i ( x, y );

	}
}
// 初始化OpenGL场景
void Initial( ){
      glClearColor(0.0f, 0.0f, 0.0f, 0.0f);                  //设置窗口背景颜色为白色
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
  // MidBhellipse(50,20);
  test(10, 100);
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




