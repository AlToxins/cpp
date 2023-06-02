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

class BBT {  //创建平衡二叉树，输入-1停止创建 
public:
	BBT() {
		root = new node();
		root->balance = 0;
		cout << "初始化完成" << endl;
	}

	void createnode() {
		cout << "可输入最大节点数: " << maxsize << endl;
		cout << "按递增顺序输入节点，输入-1停止" << endl;
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
			if (what != NULL) {		//若发现异常 
				if (Lrotation(what) == true) {
					updatebalance2(root);
				}
			}
			create(nxt);		//递归 
		}
	}

	node* updatebalance1(node* curr) {		//该函数是在添加节点后更新该节点到根节点路径上所有节点的平衡因子 ,该函数非递归 
		node* curr1;
		curr1 = curr;
		curr1->balance = 0;
		node* pre;
		pre = curr1->par;
		curr1 = pre;
		while (1) {
			if (curr1 != root) {
				curr1->balance++;
				if (abs(curr1->balance) > 1) {		//发现异常节点 并返回从该异常节点向下三个节点中的第二个节点 
					return curr1->Rchild;
				}
				pre = curr1->par;
				curr1 = pre;
			}
			else {
				root->balance++;
				if (abs(curr1->balance) > 1) {		//发现异常节点 并返回从该异常节点向下三个节点中的第二个节点 
					return curr1->Rchild;
				}
				else
					break;
			}
		}
		return NULL;
	}
	int updatebalance2(node* curr) {		//该函数是在进行左旋操作后得到新的平衡因子，旋转后的树一定是平衡树,该函数是一个递归函数，参数是根节点，该函数在求左子树的最大高度时用了取巧的办法 
		if (curr == NULL) return 0;

		int Rdepth = -1;		//右子树的最大深度
		int Ldepth = -1;		//左子树的最大深度
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
			root = curr;		//重置根节点 
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
		if (curr->Lchild != NULL || curr->Rchild != NULL)cout << "根节点" << curr->data << endl;
		if (curr->Lchild != NULL) {
			cout << "左孩子" << curr->Lchild->data << endl;
		}
		if (curr->Rchild != NULL) {
			cout << "右孩子" << curr->Rchild->data << endl << endl;
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
	int time = 1;//记录递归次数
	int max = 0;//记录节点容量 
};