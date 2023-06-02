#include"practice1.h"
#include<iostream>
using namespace std;
int main() {
    int b;
    cout << "输入数据的数量：";
    cin >> b;
    KIntArray a(b);
    a.inputArray();
    a.outputArray();
    int c;
    cout << "输入删除的数（0~9）：" << endl;
    cin >> c;
    a.deleteData(c);
}