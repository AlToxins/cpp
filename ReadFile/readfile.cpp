/*ios::in��������= 0x01,��//�������ļ��������򴴽�(ifstreamĬ�ϵĴ򿪷� ʽ)
ios::out������ = 0x02,��//��д���ļ��������� �������ļ��Ѵ��������ԭ����(ofstreamĬ�ϵĴ򿪷�ʽ)
ios::ate������ = 0x04,��//�ļ���ʱ��ָ�����ļ���󡣿ɸı�ָ���λ�ã�����in��out����ʹ��
ios::app������ = 0x08,��//��д���ļ��������򴴽������ļ��Ѵ�������ԭ�ļ����ݺ�д�� �µ����ݣ�ָ��λ���������
ios::trunc���� = 0x10,��// �ڶ�дǰ�Ƚ��ļ����Ƚض�Ϊ0��Ĭ�ϣ�
ios::nocreate��= 0x20,��//�ļ�������ʱ�������󣬳���in��app����ʹ��
ios::noreplace = 0x40,��//�ļ�����ʱ�������󣬳���out����ʹ��
ios::binary����= 0x80�� //�����Ƹ�ʽ�ļ�
��ios::app|ios::out,���û���ļ��򴴽��ļ���������ļ��������ļ�β׷��
��ios::ate|ios::out�򿪣����û���ļ��򴴽��ļ�������У�������ļ���
��ios::ate|ios::out|ios::in�򿪣����û���ļ������ʧ�ܣ����ļ���λ���ļ�β*/


#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<algorithm>
#include"readfile.h"
using namespace std;

excel::excel(string filePath)
	:maxcolumnnum(0), linenum(0), ifopen(0)
{
	cout << "Program Begin" << endl;

	//head = new node[maxhead];
	refresh_link();
	cout << "Enter The Filepath Which You Want To Use: ";
	//cin >> path;
	//path = "D:\\kaliFiles\\minGW\\Statistics\\test6.csv";
	//path="/media/kail/7A3C0A3F3C09F743/kaliFiles/minGW/Statistics/test6.csv";
	//path="D:\\�ۺϿ�̽\\����\\�����ʵ����.xls";
	path = filePath;
	fstream file(path.c_str(), ios::out | ios::app);
	if (file) {
		cout << endl << "File Has Opened" << endl;
		file.close();
		ifopen = 1;
		fstream file2(path.c_str(), ios::in | ios::out);
		ReadFile(file2);
		file2.close();
	}

	else {
		cout << "Can't find this file" << endl;
	}
}

int excel::menu() {
	if (ifopen == 1) {
		int k;
		while (1) {
			cout << endl;
			cout << "1.��ָ���к�����µ���" << endl<<endl;
			cout << "2.��ʾ�ļ�����" << endl<<endl;
			cout << "3.ͨ�������к��в�������" << endl<<endl;		//search1
			cout << "4.ͨ�������в�������" << endl<<endl;		//search2
			cout << "5.ͨ�������в�������" << endl<<endl;		//search3
			cout << "6.ͨ���������ݶ�λ���������к���" << endl<<endl;		//search4
			cout << "7.�޸�ָ�����еĵ�������" << endl<<endl;		//alert1
			cout << "8.�޸�ָ���е�����" << endl<<endl;		//alert2
			cout << "9.�޸�ָ���е�����" << endl<<endl;		//alert3
			cout << "10.ɾ��ָ���е�����" << endl<<endl;
			cout << "11.ɾ����������" << endl<<endl;
			cout << "12.�����˳�" << endl;
			cin >> k;
			if (k == 12)break;
			else if (k == 1) {
				cout << " Add Line" << endl << endl;
				int line;
				int column;
				cout << "Which Line: ";
				cin >> line;
				addline(line);
			}
			else if (k == 2) {
				cout << " Read File" << endl << endl;
				ShowData();
			}
			else if (k == 10) {
				cout << " Delete Line" << endl << endl;
				int a;
				cout << "Which Line: ";
				cin >> a;
				if (a > linenum) {
					cout << "Couldn't Find Line" << endl;
				}
				else deleteline(a);
			}
			else if (k == 11) {
				cout << " Delete All" << endl << endl;
				deleteall();
			}
			else if (k == 3) {
				cout << "Search in row and column" << endl << endl;	//search1
				int line, column;
				cout << "Search row: ";
				cin >> line;
				cout << "Search column: ";
				cin >> column;
				if (line > linenum || column > head[line - 1].columnnum) {
					cout << "Couldn't find it" << endl;
				}
				else search1(line, column);
			}
			else if (k == 7) {
				cout << "Alert in row and column" << endl << endl;
				int line, column;
				cout << "Alert row: ";
				cin >> line;
				cout << "Alert column: ";
				cin >> column;
				if (line > linenum || column > head[line - 1].columnnum) {
					cout << "Couldn't find it" << endl;
				}
				else alert1(line, column);
			}
			else if (k == 5) {
				cout << "Search in column" << endl << endl;
				int column;
				cout << "Search column: ";
				cin >> column;
				if (column > maxcolumnnum) {
					cout << "Couldn't find it" << endl;
				}
				else search3(column);
			}
			else if (k == 4) {
				cout << "Search in row" << endl << endl;
				int row;
				cout << "Search row: ";
				cin >> row;
				if (row > linenum) {
					cout << "Couldn't find it" << endl;
				}
				else search2(row);
			}
			else if (k == 8) {
				cout << "Alert in row" << endl << endl;
				int row;
				cout << "Alert in row: ";
				cin >> row;
				if (row > linenum) {
					cout << "Couldn't find it" << endl;
				}
				else alert2(row);
			}
			else if (k == 9) {
				cout << "Alert in column" << endl << endl;
				int column;
				cout << "Alert in column: ";
				cin >> column;
				if (column > maxcolumnnum) {
					cout << "Couldn't find it" << endl;
				}
				else alert3(column);
			}
			else if (k == 6) {
				cout << "Search in content" << endl << endl;
				string content;
				cout << "Search Content: ";
				cin >> content;
				search4(content);
			}
		}
		return 0;
	}
	else {
		cout << "Didn't change anything" << endl;
		return 0;
	}
	cout << "hello";
	return 0;
}

bool excel::search4(string content) {
	int times = 0;
	int mat[maxhead][maxnode + 1];
	int e = 0;
	while (e < maxhead) {
		int f = 0;
		while (f < maxnode + 1) {
			mat[e][f] = 0;
			f++;
		}
		e++;
	}
	int a = 0;
	while (a <= linenum - 1) {
		if (content == head[a].hdata) {
			mat[a][0] = 1;
			times++;
		}
		int b = 0;
		while (b <= head[a].columnnum - 2) {
			if (content == head[a].ndata[b]) {
				mat[a][b + 1] = 1;
				times++;
			}
			b++;
		}
		a++;
	}
	if (times == 0) {
		cout << "No result" << endl;
		return false;
	}
	else {
		int c = 0;
		while (c < maxhead) {
			int d = 0;
			while (d < maxnode + 1) {
				if (mat[c][d] == 1) {
					cout << "��" << c + 1 << "�У���" << d + 1 << "��" << endl;
				}
				d++;
			}
			c++;
		}
		return true;
	}
}

int excel::alert3(int column) {
	refresh_file();
	if (column == 1) {
		cout << "Data1: ";
		string a;
		cin >> a;
		if (a == "quit") {
			cout << "Nothing Changed" << endl;
			return 0;
		}
		else {
			head[0].hdata = a;
			int k = 1;
			while (k <= linenum - 1) {
				cout << "Data" << k + 1 << ": ";
				cin >> a;
				if (a == "quit") {
					break;
				}
				head[k].hdata = a;
				k++;
			}
		}
	}
	else {
		cout << "Data1: ";
		string a;
		cin >> a;
		if (a == "quit") {
			cout << "Nothing Changed" << endl;
			return 0;
		}
		else {
			head[0].ndata[column - 2] = a;
			int k = 1;
			while (k <= linenum - 1) {
				cout << "Data" << k + 1 << ": ";
				cin >> a;
				if (a == "quit") {
					break;
				}
				head[k].ndata[column - 2] = a;
				k++;
			}
		}
	}
	WriteIn();
	return 0;
}

int excel::alert2(int row) {	//press finish to save
	int k = 0;
	cout << "column1: ";
	string a;
	cin >> a;
	if (a == "quit") {
		cout << "Nothing Changed" << endl;
		return 0;
	}
	else {
		refresh_file();
		int k1 = 0;
		head[row - 1].hdata = "";
		head[row - 1].hdata = a;
		while (k1 <= head[row - 1].columnnum - 2) {		//empty link
			head[row - 1].ndata[k1] = "";
			k1++;
		}
		string b;
		int k2 = 2;
		while (1) {
			cout << "column" << k2 << ": ";
			cin >> b;
			if (b == "quit")break;
			else {
				head[row - 1].ndata[k2 - 2] = b;
				k2++;
			}
			if (k2 == maxnode + 2) {
				cout << "This row is full" << endl;
				break;
			}
		}
		WriteIn();
		fstream file(path.c_str(), ios::in | ios::out);
		ReadFile(file);
		file.close();
	}
	return 0;
}

void excel::search2(int row) {
	int k = 0;
	cout << head[row - 1].hdata << " ";
	while (k <= head[row - 1].columnnum - 2) {
		cout << head[row - 1].ndata[k] << " ";
		k++;
	}
	cout << endl << "Row " << row << " has " << k + 1 << " column in total" << endl;
}

void excel::search3(int column) {
	int k = 0;
	if (column == 1) {
		while (k <= linenum - 1) {
			cout << head[k].hdata << endl;
			k++;
		}
		int k1 = k - 1;
		while (k1 >= 0) {
			if (head[k1].hdata == "")k--;
			k1--;
		}
	}
	else {
		while (k <= linenum - 1) {
			cout << head[k].ndata[column - 2] << endl;
			k++;
		}
		int k1 = k - 1;
		while (k1 >= 0) {
			if (head[k1].ndata[column - 2] == "")k--;
			k1--;
		}
	}
	cout << "Column " << column << " has " << k << " rows in total" << endl;
}

void excel::alert1(int line, int column) {
	refresh_file();
	string a;
	cout << "Alert to: ";
	cin >> a;
	if (column != 1) {
		head[line - 1].ndata[column - 2] = a;
	}
	else head[line - 1].hdata = a;
	WriteIn();
}



void excel::search1(int line, int column) {
	if (column != 1)cout << "Row " << line << " column " << column << " is " << head[line - 1].ndata[column - 2] << endl;
	else cout << "Row " << line << " column 1 " << "is " << head[line - 1].hdata << endl;

}

int excel::addline(int line) {	//���ļ�����һ������,��ָ���еĺ�������,����quitֹͣ�������,Ŀǰ�����⣬��������ӵ�����û�����⣬��Ҫ�����ǽ������е�������ӵ��ļ�����

	if (linenum == maxhead) {
		cout << "�Ѵ������ޣ����ʧ��" << endl;
	}
	else {
		refresh_file();
		int n2 = linenum;
		int n1 = linenum - 1;
		while (n1 >= line) {	//�ƶ���������,��line�Ѿ������һ�У�����line=n2>n1,�ʸ���䲻��ִ��
			head[n2] = head[n1];
			n2--;
			n1--;
		}
		string h;	//��һ������
		//string content;	//��������
		cout << "First Data: ";	//��ʼ�������
		cin >> h;
		head[line].hdata = "";
		head[line].hdata = h;
		int n = 0;
		while (n < head[line].columnnum - 1) {	//��ո��е�����
			head[line].ndata[n] = "";
			n++;
		}
		head[line].columnnum = 1;
		if (h == "quit")return 0;
		n = 0;
		while (n <= maxnode) {
			string content;	//��������
			cout << "Data" << n + 2 << ": ";
			cin >> content;
			if (content == "quit") break;
			head[line].ndata[n] = content;
			head[line].columnnum++;
			n++;
		}
		if (maxcolumnnum < n + 1) {
			maxcolumnnum = n + 1;	//�����������
		}
		linenum++;	//�����������
		WriteIn();
	}
	return 0;
}

void excel::deleteline(int line) {
	refresh_file();
	int a = 0;
	while (a <= head[line - 1].columnnum - 2) {
		head[line - 1].ndata[a] = "";
		a++;
	}
	head[line - 1].hdata = "";
	if (head[line - 1].columnnum == maxcolumnnum) {
		head[line - 1].columnnum = 0;
		int c[maxhead];
		int b = 0;
		while (b <= linenum - 1) {
			c[b] = head[b].columnnum;
			b++;
		}
		maxcolumnnum = *max_element(c, c + linenum);
	}
	int d = line - 1;
	while (d < linenum) {
		head[d] = head[d + 1];
		d++;
	}
	d = 0;
	while (line != linenum && d <= head[linenum - 1].columnnum - 2) {	//ɾ��ĳһ�к����������ƶ���������һ����Ҫ��ɾ��
		head[linenum - 1].ndata[d] = "";
		d++;
	}
	linenum--;
	WriteIn();
}

void excel::deleteall() {
	fstream file;
	file.open(path.c_str(), ios::ate | ios::out);
	file.close();
	int a = 0;

	while (a < linenum) {
		int b = 0;
		while (b <= head[a].columnnum - 2) {
			head[a].ndata[b] = "";
			b++;
		}
		head[a].hdata = "";
		head[a].columnnum = 0;
		a++;
	}
	linenum = 0;
	maxcolumnnum = 0;
}


void excel::ReadFile(fstream& file) {
	string temp1;
	int n1 = 0;	//mark head
	int n2[maxhead];	//mark node
	int n3 = 0;
	while (n3 < maxhead) {	//Ϊÿһ�е��еĸ������г�ʼ��
		n2[n3] = 0;
		n3++;
	}
	while (getline(file, temp1)) {
		//n1++;
		stringstream ss(temp1);
		string temp2;
		getline(ss, temp2, ',');
		head[n1].hdata = temp2;	//��ȡĳ�е�һ�е�����

		while (getline(ss, temp2, ',')) {	//��ȡĳ�������е�����
			head[n1].ndata[n2[n1]] = temp2;
			n2[n1]++;
		}
		n2[n1]++;
		int k = n2[n1];
		int k1 = 0;
		while (k1 < k - 1) {
			if (head[n1].ndata[k1] == "") {
				n2[n1]--;
				n2[n1]++;
			}
			k1++;
		}
		head[n1].columnnum = n2[n1];	//��¼��ǰ�е�������
		//cout<<"Line "<<n1+1<<"'s column number is"<<head[n1].columnnum<<endl;
		n1++;
	}
	linenum = n1;
	if (*max_element(n2, n2 + n1) != 0)maxcolumnnum = *max_element(n2, n2 + n1);	//��˼������n1��n2������һ������n2
	else maxcolumnnum = 0;
	int k = 0;
}

void excel::ShowData() {
	int n1 = 0;
	while (n1 < linenum) {
		cout << head[n1].hdata << " ";
		int n2 = 0;
		while (n2 < maxcolumnnum - 1) {
			cout << head[n1].ndata[n2] << " ";
			n2++;
		}
		//cout << "����" << head[n1].columnnum<< "��";
		cout << endl;
		n1++;
	}
	cout << "Line: " << linenum << endl;
	cout << "MaxColumn: " << maxcolumnnum << endl;
}

void excel::WriteIn() {
	fstream file;
	file.open(path.c_str(), ios::ate | ios::out);
	int n = 0;
	while (n < linenum) {
		int nn = 0;
		file << head[n].hdata << ",";
		while (nn < head[n].columnnum) {
			file << head[n].ndata[nn] << ",";
			nn++;
		}
		n++;
		file << "\n";
	}
	file.close();
}

void excel::refresh_file() {
	fstream file1;
	file1.open(path.c_str(), ios::ate | ios::out);
	file1.close();
}

void excel::refresh_link() {		//��ʼ������ 
	head = new node[maxhead];
	int a = 0;
	while (a < maxhead) {
		head[a].hdata = "";
		int b = 0;
		while (b < maxnode) {
			head[a].ndata[b] = "";
			b++;
		}
		a++;
	}
}


excel::~excel() {
	cout << "Done" << endl;
}
