#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

int main() {
	vector<int> vt;
	int i = 0;
	int num;
	while (i < 8) {
		cin >> num;
		vt.push_back(num);
		i++;
	}
	
	//show vt
	//i = 0;
	//while (i < 8) {
	//	cout << vt[i] << endl;
	//	i++;
	//}

	bool prime = true;
	for (auto v = vt.cbegin(); v != vt.cend();v++) {
		if (*v == 2) cout << *v << " ";
		else if (*v == 1) continue;
		else {
			prime = true;
			for (int i2 = 2; i2 <= sqrt(*v); i2++) {
				if (*v % i2 == 0) {
					prime = false;
					break;
				}
			}
			if (prime == true) cout << *v << " ";
		}
	}

	return 0;
}