//This program can give you some choices about handling your excel file
//本程序用于处理CSV文件，使用前将xlsx文件提前转换为CSV文件存储，具体方法为打开xlsx文件->点击另存为->修改文件类型为csv
// 要在QuantyView3DView中使用该代码需要先将两个.h文件存储到\QuantyView3d\文件夹下，然后在stdafx.h中添加：#include<sstream> #include"..\..\build\3DFrame\QuantyView3d\readfile.h"
// 然后在该代码的excel类中声明你当前的类为友元类，例如要在QuantyView3DView类中使用该代码，则声明：friend class QuantyView3DView
// 完成以上操作后即可在QuantyView3D中使用该代码
//本程序包含的所有接口及注释见类定义
// 
//-------------------------------------------------------------------------------------------------------------------------
// 本程序的数据结构如下：
// 1、链表结构体"node"包含三个属性数据，其中：hdata用于记录每一个链表的第一个数据；ndata[maxnode]用于记录每一个链表的
// 除了第一个数据外的其他数据，maxnode为自定义的最大列数
// 2、使用链表结构体"node"存储CSV文件的每一行数据，为node结构体指针head申请maxhead个空间，表示最大可存储maxhead行数据
// 3、在refresh_link()函数中实现对链表进行初始化，将每个链表(head[0]、head[1]、head[2].....)的hdata值以及ndata值初始化为空
// ------------------------------------------------------------------------------------------------------------------------
// 本程序的使用方法如下：
// 1、首先在该代码的excel类中声明你当前的类为友元类，例如要在QuantyView3DView类中使用该代码，则声明：friend class QuantyView3DView
// 2、创建excel类型的对象excelFile(filepath)，括号中的参数为要读取的CSV文件地址，对象创建完成后CSV文件内的数据已经存储到excelFile的head链表当中
// 
// 3、通过excelFile.head[n]可以访问所选文件的第n-1行数据，例如excelFile.head[n].hdata是访问第n+1行的第一列数据，excelFile.head[n].ndata[n]是访问第n+1行的第n+2个数据
// 数据存储类型都是string
// 
// 4、通过excelFile拥有的maxcolumnnum以及linenum可以查看所选文件的最大行数以及最大列数，通过excelFile.head[n].columnnum可以查看第n+1行的列数
// 5、各个功能的退出方法都是输入"quit"
// 6、其他函数使用方法见函数定义的注释
//



#pragma once
#include<iostream>
#include<cstring>
#include<fstream>
#include<vector>
#define maxnode 100	//最多列数（不包含第一列）
#define maxhead 1400	//最多行数
using namespace std;
//总的列数应该是node数+1

struct node {

	string hdata;	//第一列数据
	string ndata[maxnode];	//其他列数据
	int columnnum;	//记录每一行数据有多少列
};
class excel {
public:
	excel(string filePath);
	~excel();

	int addline(int line);	//在指定行的后面添加新的行
	void ReadFile(fstream& a);	//读取文件内容，将文件内容赋值给指定链表
	void ShowData();	//处理链表，在控制台输出链表中的文件内容
	void deleteline(int line);	//删除指定行内容
	void deleteall();		//delete all file conetents
	void search1(int a, int b);		//search in row and column
	void search2(int a);		//search in row
	void search3(int a);		//search in column
	bool search4(string a);		//search in content, return row and column
	void alert1(int a, int b);	//alert in row and column
	int alert2(int a);		//alert in row
	int alert3(int a);		//alert in column, type quit to finish
	void WriteIn();		//Write from link to file
	void refresh_file();		//refresh file
	void refresh_link();		//refresh link
	int menu();	//菜单

private:
	//int function;
	string path;
	//vector<node*>v1;
	int maxcolumnnum;
	int linenum;
	int ifopen;	//判断文件是否打开
	node* head;
};
