#include <iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;
char filename[50];
int fd;
bool opened = false;
char* pargv[4] = { "ls", "-l", NULL, NULL };
void create_open_file() {
    cout<<"请输入文件名"<<endl;
    cin>> filename;
    umask(0000);
    fd = open(filename, O_RDWR | O_CREAT, 0666);
    pargv[2] = (char*)malloc(50);
    strcpy(pargv[2], filename);
    if (fd < 0) {
        cout<<"打开失败"<<endl;
    }
    else {
        opened = 1;
        cout << "打开成功" << endl;;
    }
}
void write_file() {
    if (opened == 0) {
        cout<<"首先需要打开文件"<<endl;
        return;
    }
    char buffer[1 << 10];
    cout << "请输入文件内容" << endl;
    cin>> buffer;
    int returnnum = write(fd, buffer, strlen(buffer));
    if (returnnum != -1) {
        cout << "写入成功！" << endl;
    }
    else {
        cout << "写入失败！" << endl;
    }
}
void  mode_file() {
    if (opened == 0) {
        cout << "首先需要打开文件" << endl;
        return;
    }
    int mode;
    printf("输入新的模式\n");
    scanf("%d", &mode);
    int mode_u = mode / 100;
    int mode_g = mode / 10 % 10;
    int mode_o = mode % 10;
    mode = (mode_u * 8 * 8) + (mode_g * 8) + mode_o;   
    int returnnum = chmod(filename, mode);
    if (returnnum == -1) {
        cout << "改变模式失败！" << endl;
    }
    else {
        cout << "改变模式成功！" << endl;
    }
}
void read_file() {
    if (opened == 0) {
        cout << "首先需要打开文件" << endl;
        return;
    }
    char buffer[1 << 10];
    memset(buffer, 0, sizeof(buffer));
    lseek(fd, 0, SEEK_SET);
    int returnnum = read(fd, buffer, 1024);
    if (returnnum != -1) {
        cout << "文件内容为：" << endl;
        cout << buffer << endl;
    }
    else {
        cout << "读取失败" << endl;
    }

}
void view_mode() {
    if (opened == 0) {
        cout << "首先需要打开文件" << endl;
        return;
    }
    cout << "文件权限为" << endl;
    int returnnum = execv("/bin/ls", pargv);
    if (returnnum == -1) {
        cout << "查看失败" << endl;
    }
    else {
        cout << "文件权限为" << endl;
    }

}
int main()
{
    int choice;
    while (1) {
        cout << "请选择文件操作" << endl;
        cout << "1.新建（不存在）或者打开文件" << endl;
        cout << "2.读文件" << endl;
        cout << "3.写文件" << endl;
        cout << "4.给文件权限修改" << endl;
        cout << "5.查看文件权限" << endl;
        cout << "6.关闭文件" << endl;
        cout << "" << endl;
        cin >> choice;
        switch (choice) {
        case 1:create_open_file();
            break;
        case 2:read_file();
            break;
        case 3:write_file();
            break;
        case 4:mode_file();
            break;
        case 5:view_mode();
            break;
        case 6:close(fd);
            opened = 0;
            break;

        }
    }
    return 0;
}
