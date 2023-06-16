#include <iostream>
#include<algorithm>
#include<list>
#include<vector>
#include<iomanip>
#include<climits>
#include<time.h>
#include<stdio.h>
#include"page.h"


using namespace std;
const int minn = 8;                        //分配给用户的最小页数
const int maxx = 32;                       //分配给用户的最大页数
const int N = 320;                         //最大指令数
int ins[2 * N];                            //用来存储指令访问
double hit = 0;                          //记录页面命中次数
const int wide = 32766;                //即32k-2，最大指令地址

void page::get_input() {
    int cnt = 0;                           //用来记录指令条数
    srand(time(0));                        //获取时间种子
    while (cnt < N) {                      //循环产生指令序列
        int m = rand() % wide + 1;      //在【1，32k-2】范围内选取一起点M
        ins[cnt++] = m;         
        if (cnt >= N) {
            break;
        }
        ins[cnt++] = m + 1;                //顺序访问M+1 
        if (cnt >= N) {
            break;
        }
        int m1 = rand() % m;               //在【1，M-1】中随随机选取M1
        ins[cnt++] = m1;
        if (cnt >= N) {
            break;
        }
        ins[cnt++] = m1 + 1;               //顺序访问M1+1
        if (cnt >= N) {
            break;
        }     
        int m2 = rand() % (wide - 1 - m1) + (m1 + 2);          //在【M1+2，32k-2】中随机选取M2
        ins[cnt++] = m2;
        if (cnt >= N) {
            break;
        }
        ins[cnt++] = m2 + 1;                 //顺序访问M2+1
        if (cnt >= N) {
            break;
        }
    }
    for (int i = 0; i < N; i++) {
        ins[i] = ins[i] / 1024;                //得到每条随机数所在的的页块
    }
}
double page::FIFO(int page) {                        //实现FIFO算法
    hit = 0;                              //初始时页面命中次数为零
    list<int>temp;
    for (int i = 0; i < page; i++) {
        temp.push_back(-1);
    }
    for (int i = 0; i < N; i++) {
        list<int>::iterator it = find(temp.begin(), temp.end(), ins[i]);         
        if (it == temp.end()) {                    //没有找到对应指令
            temp.pop_front();                     //队列先进先出，即删除最后一个页面
            temp.push_back(ins[i]);               //插入当前页号
        }
        else {
            hit++;                          //队列中存在对应页号，则命中次数加一
        }
    }
    hit =hit / N;                      //计算命中率
    hit *= 100;
    return hit;
}

double page::LRU(int page) {
    hit = 0;                             //初始命中率等于零
    list<node>temp;
    for (int i = 0; i < page; i++) {
        temp.push_back(node{ -1,0 });                //对结构体内存储的id和num进行初始化操作
    }
    list<node>::iterator it;
    for (int i = 0; i < N; i++) {
        for (it = temp.begin(); it != temp.end(); it++) {
            it->num++;                             //先根据队列中队列中页面的顺序来初始化他们的不被常用num
        }
        bool flag = false;
        for (it = temp.begin(); it != temp.end(); it++) {
            if (it->id == ins[i]) {                   //如果指令被访问了
                flag = true;                           //这个页面就不是不常用的
                it->num = 0;
                hit++;                             //命中率加一
                break;
            }
        }
        if (!flag) {
            //找到一个最大的
            list<node>::iterator max_it = temp.begin();
            for (it = temp.begin(); it != temp.end(); it++) {             //寻找队列中num的值最大的删掉
                if (it->num > max_it->num) {
                    max_it = it;
                }
            }
            temp.erase(max_it);
            temp.push_back(node{ ins[i],0 });             //加入新的页面，num为零
        }
    }
    hit = hit / N;                                //计算命中率
    hit *= 100;
    return hit;
}
double page::OPT(int page) {
    list<int>temp;
    hit = 0;                                         //初始命中率为零
    for (int i = 0; i < page; i++) {
        temp.push_back(-1);                              //初始化每个页面的访问情况
    }
    for (int i = 0; i < N; i++) {
        list<int>::iterator it = find(temp.begin(), temp.end(), ins[i]);
        if (it == temp.end()) {
            int max_id = -1;                              //首先初始化每个指令在后面出现的位置

            list<int>::iterator ans;
            for (it = temp.begin(); it != temp.end(); it++) {
                int cur = 0x3f3f3f3f;                      //默认下条该指令的位置都在无穷远处
                for (int j = i + 1; j < N; j++) {          //在后面页面的指令中寻找当前这条指令
                    if (ins[j] == *it) {
                        cur = j;                           //找到了给cur赋值
                        break;
                    }
                }
                if (cur > max_id) {
                    max_id = cur;                         //不断的替换max_id的值，直到其为最大值，表示最不常2用到的页面指令
                    ans = it;
                }
            }
            temp.erase(ans);                                 //删除该最不常用到的页面
            temp.push_back(ins[i]);                           //加入新的页面

        }
        else {
            hit++;
        }
    }
    hit = hit / N;                                  //计算命中率
    hit *= 100;
    return hit;
}
int main()
{
    page pag;
    pag.get_input();
    cout << "          以下为三种算法分别的命中率          " << endl;
    cout << "内存页块            FIFO                  LRU                   OPT" << endl;
    for (int i = minn; i <= maxx; i++) {
        cout << i << "\t\t" << pag.FIFO(i) << "%" << "\t\t\t" << pag.LRU(i) << "%" << "\t\t\t" << pag.OPT(i) << "%" << endl;
    }
    return 0;
}
