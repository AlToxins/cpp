#include<iostream>

using std::cout;
using std::endl;
using std::cin;

int main() {
	int n;
	cin >> n;
	int num;
	int i;
	while (i < n) {
		cin >> num;
		
		//�����num�����ж�
		test(num);

		i++;
	}

}

void test(int n) {
	int last = 0, curr = n;
	int time = 0;
	while (last != 0 || curr == 1) {
		last = curr % 2;
		curr = curr / 2;
		time++;
	}

	if (time>1) {

	}
}