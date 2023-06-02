#include<iostream>
#include<cmath>
#define maxsize 20
typedef int datatype;
using namespace std;

struct node {
	datatype data;
	node* par;
	node* Lchild;
	node* Rchild;
	int balance;
};

class BBT {  //����ƽ�������������-1ֹͣ���� 
public:
	BBT() {
		root = new node();
		root->balance = 0;
		cout << "��ʼ�����" << endl;
	}

	void createnode() {
		cout << "���������ڵ���: " << maxsize << endl;
		cout << "������˳������ڵ㣬����-1ֹͣ" << endl;
		datatype a;
		int b = 0;
		while (cin >> a) {
			nodedata[max] = a;
			max++;
			if (a == -1) break;
		}
		root->data = nodedata[0];
	}

	int create(node* curr) {
		if (time == max - 2) return 0;
		node* nxt;
		nxt = new node();
		curr->data = nodedata[time];
		if (root->Rchild == NULL) {
			root->Rchild = curr;
			curr->par = root;
			updatebalance1(curr);
			create(curr);
		}
		else {
			time++;
			nxt->data = nodedata[time];
			curr->Rchild = nxt;
			nxt->par = curr;
			node* what;
			what = updatebalance1(nxt);
			if (what != NULL) {		//�������쳣 
				if (Lrotation(what) == true) {
					updatebalance2(root);
				}
			}
			create(nxt);		//�ݹ� 
		}
	}

	node* updatebalance1(node* curr) {		//�ú���������ӽڵ����¸ýڵ㵽���ڵ�·�������нڵ��ƽ������ ,�ú����ǵݹ� 
		node* curr1;
		curr1 = curr;
		curr1->balance = 0;
		node* pre;
		pre = curr1->par;
		curr1 = pre;
		while (1) {
			if (curr1 != root) {
				curr1->balance++;
				if (abs(curr1->balance) > 1) {		//�����쳣�ڵ� �����شӸ��쳣�ڵ����������ڵ��еĵڶ����ڵ� 
					return curr1->Rchild;
				}
				pre = curr1->par;
				curr1 = pre;
			}
			else {
				root->balance++;
				if (abs(curr1->balance) > 1) {		//�����쳣�ڵ� �����شӸ��쳣�ڵ����������ڵ��еĵڶ����ڵ� 
					return curr1->Rchild;
				}
				else
					break;
			}
		}
		return NULL;
	}
	int updatebalance2(node* curr) {		//�ú������ڽ�������������õ��µ�ƽ�����ӣ���ת�����һ����ƽ����,�ú�����һ���ݹ麯���������Ǹ��ڵ㣬�ú������������������߶�ʱ����ȡ�ɵİ취 
		if (curr == NULL) return 0;

		int Rdepth = -1;		//��������������
		int Ldepth = -1;		//��������������
		node* curr1 = curr;
		node* curr2 = curr;
		while (curr1 != NULL) {
			Rdepth++;
			curr1 = curr1->Rchild;
		}
		while (curr2 != NULL) {
			Ldepth++;
			curr2 = curr2->Lchild;
		}
		curr->balance = abs(Rdepth - Ldepth);
		updatebalance2(curr->Rchild);
	}

	bool Lrotation(node* curr) {
		if (curr == NULL) return false;
		if (curr->par->par == NULL && curr->Lchild == NULL) {
			curr->par->Rchild = NULL;
			curr->Lchild = curr->par;
			curr->par == NULL;
			root = curr;		//���ø��ڵ� 
			root->par = NULL;
			return true;
		}
		else if (curr->par->par == NULL && curr->Lchild != NULL) {
			node* currLchild;
			node* currpar;
			currpar = curr->par;
			currLchild = curr->Lchild;
			curr->Lchild = curr->par;
			currpar->par = curr;
			currpar->Rchild = currLchild;
			curr->par = NULL;
			root = curr;
			return true;
		}
		else if (curr->par->par != NULL && curr->Lchild == NULL) {
			node* currpar;
			currpar = curr->par->par;
			curr->par->Rchild = NULL;
			curr->Lchild = curr->par;
			curr->par = NULL;
			curr->par = currpar;
			currpar->Rchild = curr;
			return true;
		}
		else if (curr->par->par != NULL && curr->Lchild != NULL) {
			node* currparpar;
			currparpar = curr->par->par;
			node* currLchild;
			currLchild = curr->Lchild;
			curr->Lchild = curr->par;
			curr->par->par = curr;
			curr->Lchild->Rchild = currLchild;
			currparpar->Rchild = curr;
			curr->par = currparpar;
			return false;
		}
	}

	int printBST(node* curr) {
		if (curr == NULL) return 0;
		if (curr->Lchild != NULL || curr->Rchild != NULL)cout << "���ڵ�" << curr->data << endl;
		if (curr->Lchild != NULL) {
			cout << "����" << curr->Lchild->data << endl;
		}
		if (curr->Rchild != NULL) {
			cout << "�Һ���" << curr->Rchild->data << endl << endl;
		}
		printBST(curr->Lchild);
		printBST(curr->Rchild);
	}

	node* returnroot() {
		return root;
	}

private:
	node* root;
	datatype nodedata[maxsize];
	int time = 1;//��¼�ݹ����
	int max = 0;//��¼�ڵ����� 
};