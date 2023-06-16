//This program can give you some choices about handling your excel file
//���������ڴ���CSV�ļ���ʹ��ǰ��xlsx�ļ���ǰת��ΪCSV�ļ��洢�����巽��Ϊ��xlsx�ļ�->������Ϊ->�޸��ļ�����Ϊcsv
// Ҫ��QuantyView3DView��ʹ�øô�����Ҫ�Ƚ�����.h�ļ��洢��\QuantyView3d\�ļ����£�Ȼ����stdafx.h����ӣ�#include<sstream> #include"..\..\build\3DFrame\QuantyView3d\readfile.h"
// Ȼ���ڸô����excel���������㵱ǰ����Ϊ��Ԫ�࣬����Ҫ��QuantyView3DView����ʹ�øô��룬��������friend class QuantyView3DView
// ������ϲ����󼴿���QuantyView3D��ʹ�øô���
//��������������нӿڼ�ע�ͼ��ඨ��
// 
//-------------------------------------------------------------------------------------------------------------------------
// ����������ݽṹ���£�
// 1������ṹ��"node"���������������ݣ����У�hdata���ڼ�¼ÿһ������ĵ�һ�����ݣ�ndata[maxnode]���ڼ�¼ÿһ�������
// ���˵�һ����������������ݣ�maxnodeΪ�Զ�����������
// 2��ʹ������ṹ��"node"�洢CSV�ļ���ÿһ�����ݣ�Ϊnode�ṹ��ָ��head����maxhead���ռ䣬��ʾ���ɴ洢maxhead������
// 3����refresh_link()������ʵ�ֶ�������г�ʼ������ÿ������(head[0]��head[1]��head[2].....)��hdataֵ�Լ�ndataֵ��ʼ��Ϊ��
// ------------------------------------------------------------------------------------------------------------------------
// �������ʹ�÷������£�
// 1�������ڸô����excel���������㵱ǰ����Ϊ��Ԫ�࣬����Ҫ��QuantyView3DView����ʹ�øô��룬��������friend class QuantyView3DView
// 2������excel���͵Ķ���excelFile(filepath)�������еĲ���ΪҪ��ȡ��CSV�ļ���ַ�����󴴽���ɺ�CSV�ļ��ڵ������Ѿ��洢��excelFile��head������
// 
// 3��ͨ��excelFile.head[n]���Է�����ѡ�ļ��ĵ�n-1�����ݣ�����excelFile.head[n].hdata�Ƿ��ʵ�n+1�еĵ�һ�����ݣ�excelFile.head[n].ndata[n]�Ƿ��ʵ�n+1�еĵ�n+2������
// ���ݴ洢���Ͷ���string
// 
// 4��ͨ��excelFileӵ�е�maxcolumnnum�Լ�linenum���Բ鿴��ѡ�ļ�����������Լ����������ͨ��excelFile.head[n].columnnum���Բ鿴��n+1�е�����
// 5���������ܵ��˳�������������"quit"
// 6����������ʹ�÷��������������ע��
//



#pragma once
#include<iostream>
#include<cstring>
#include<fstream>
#include<vector>
#define maxnode 100	//�����������������һ�У�
#define maxhead 1400	//�������
using namespace std;
//�ܵ�����Ӧ����node��+1

struct node {

	string hdata;	//��һ������
	string ndata[maxnode];	//����������
	int columnnum;	//��¼ÿһ�������ж�����
};
class excel {
public:
	excel(string filePath);
	~excel();

	int addline(int line);	//��ָ���еĺ�������µ���
	void ReadFile(fstream& a);	//��ȡ�ļ����ݣ����ļ����ݸ�ֵ��ָ������
	void ShowData();	//���������ڿ���̨��������е��ļ�����
	void deleteline(int line);	//ɾ��ָ��������
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
	int menu();	//�˵�

private:
	//int function;
	string path;
	//vector<node*>v1;
	int maxcolumnnum;
	int linenum;
	int ifopen;	//�ж��ļ��Ƿ��
	node* head;
};
