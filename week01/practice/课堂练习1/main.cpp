#include"practice1.h"
#include<iostream>
using namespace std;
int main() {
    int b;
    cout << "�������ݵ�������";
    cin >> b;
    KIntArray a(b);
    a.inputArray();
    a.outputArray();
    int c;
    cout << "����ɾ��������0~9����" << endl;
    cin >> c;
    a.deleteData(c);
}