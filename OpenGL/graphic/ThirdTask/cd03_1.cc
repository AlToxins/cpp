#include <GL/glut.h>
#include <Windows.h>
#include <math.h>

#define PI 3.1415926535897932384626433832795

// 三维几何变换类
class CTransform3D
{
protected:
double mm[4][4]; // 变换矩阵
public:
CTransform3D(){Identity();} // 构造函数
CTransform3D(double nn[4][4]){memcpy(mm, nn, sizeof(mm));}
// 设置为单位矩阵
void Identity(){memset(mm, 0.0, sizeof(mm));  mm[0][0]=mm[1][1]=mm[2][2]=mm[3][3]=1.0;}
void Translate(double tx=0.0, double ty=0.0, double tz=0.0){}// 平移变换
void Scale(double sx=1.0, double sy=1.0, double sz=1.0){} // 比例变换
void Symmetric(int nType=0){} // 对称变换
void Shear(double sh[6]){} // 错切变换

void Rotate(double degree, int nAxis=0) // 旋转变换
{
double cosA=cos(degree*PI/180.0), sinA=sin(degree*PI/180.0);
double nn[4][4] = {0.0}; 
nn[0][0]=nn[1][1]=nn[2][2]=nn[3][3]=1.0;
switch (nAxis)
{
case 0: // X轴
nn[1][1] = cosA, nn[1][2] = sinA;
nn[2][1] = -sinA, nn[2][2] = cosA;
break;
case 1: // Y轴
nn[0][0] = cosA, nn[0][2] = -sinA;
nn[2][0] = sinA, nn[2][2] = cosA;
break;
case 2: // Z轴
nn[0][0] = cosA, nn[0][1] = sinA;
nn[1][0] = -sinA, nn[1][1] = cosA;
break;
default:
break;
}

Transf(nn);
}

void Transf(double nn[4][4]) // 矩阵右乘
{
double cc[4][4];
for (int i=0; i<4; i++)
{
for(int j=0; j<4; j++)
{
cc[i][j] = 0.0;
for(int k=0; k<4; k++)
cc[i][j] += mm[i][k]*nn[k][j];
}
}
memcpy(mm, cc, sizeof(mm));
}

// 对坐标点进行变换
void Transf(double pos[3])
{
double pt[3]={0.0};
for (int i=0; i<3; i++)
{
pt[i] = pos[0]*mm[0][i] + pos[1]*mm[1][i] + pos[2]*mm[2][i] + mm[3][i];
}
memcpy(pos, pt, sizeof(pt));
}
};

CTransform3D oTransform; // 二维图形变换对象

void Initial()
{
glEnable(GL_DEPTH_TEST);       // 启用深度测试
glClearColor(1.0f, 1.0f, 1.0f, 1.0f ); //背景为白色
}

void ChangeSize(int w, int h)
{
if(h == 0) h = 1;
glViewport(0, 0, w, h);               // 设置视区尺寸
glMatrixMode(GL_PROJECTION);    // 指定当前操作投影矩阵堆栈
glLoadIdentity();                   // 重置投影矩阵

GLfloat fAspect;
fAspect = (float)w/(float)h;            // 计算视区的宽高比
gluPerspective(45.0, fAspect, 1.0, 500.0); // 指定透视投影的观察空间
}


void Display(void)
{
static double fElect = 5.0;           // 旋转的小角度
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除颜色和深度缓冲区

glMatrixMode(GL_MODELVIEW);  // 指定当前操作模型视图矩阵堆栈
glLoadIdentity();                  // 重置模型视图矩阵

oTransform.Rotate(fElect, 1); // 每次绕Y轴旋转小角度
double pos[3] = {100.0, 0.0, 100.0};
oTransform.Transf(pos);
gluLookAt(pos[0], pos[1], pos[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // 改变眼睛的位置

glColor3f(1.0f, 0.0f, 0.0f);
glutWireTeapot(20.0);
//glutSolidTeapot(20.0); // 一个在原点的茶壶
{// 绘制位图文本
char c[] = "Teapot";
int n = strlen(c);
glRasterPos3d(0.0, 20.0, 0.0); // 指定文本位置
for (int i=0; i<n; i++)
glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c[i]);
}

glLoadIdentity();                  // 重置模型视图矩阵
double pos1[3] = {100.0, 0.0, 0.0};
oTransform.Transf(pos1);
gluLookAt(0.0, 300.0, 0.0, pos1[0], pos1[1], pos1[2], 0.0, 0.0, 1.0); // 改变Center的位置

glColor3f(0.0f, 1.0f, 0.0f);
glutWireTeapot(20.0);

glutSwapBuffers();
}

bool bRun = true;

void TimerFunc(int value)
{
glutPostRedisplay();
if(bRun)
glutTimerFunc(100, TimerFunc, 1);
}

// 键盘响应函数
void KeyEvent(unsigned char key, int x, int y){
switch(key){
case 's': // 暂停
{
bRun = false;
glutPostRedisplay();
}
break;
case 'a': // 继续
{
bRun = true;
glutTimerFunc(100, TimerFunc, 1); 
glutPostRedisplay();
}
break;
default: break;
}
}

int main(int argc, char* argv[])
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowSize(500, 500);
glutCreateWindow("三维模型视图变换示例");
glutReshapeFunc(ChangeSize);
glutDisplayFunc(Display);
glutTimerFunc(1000, TimerFunc, 1);     //指定定时器回调函数
glutKeyboardFunc(KeyEvent); //指定键盘响应函数
Initial();
glutMainLoop();
return 0;
}
