#include<iostream>
#include"translator.h"
using namespace std;
int main() {
	BBT use;
	node* curr;
	curr = new node();
	use.createnode();
	use.create(curr);
	use.printBST(use.returnroot());
}