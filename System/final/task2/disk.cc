#include <iostream>
#include <algorithm>
using namespace std;

const int start = 90;
void FCFS()
{
    int Find[14] = { 30,50,100,180,20,90,150,70,80,10,160,120,40,110 };
    int sum = 0;
    cout << "当前磁盘号为90";
    cout << "FCFS算法的遍历路径为:" << endl;
    cout << start << "-->";
    for (int i = 0; i <= 13; i++)
    {
        if (i == 0)
        {
            sum += abs(start - Find[i]);
            cout << Find[i] << "-->";
        }
        else
        {
           sum += abs(Find[i - 1] - Find[i]);
           if (i == 13)
               cout << Find[i] << endl;
           else
               cout << Find[i] << "-->";
        }
    }
    cout << "FSFC算法的平均移动道数为：" << sum/14 << endl;
}

void SSTF()
{
    int Find[14] = { 30,50,100,180,20,90,150,70,80,10,160,120,40,110 };
    struct P
    {
        int location;
        int flag;
    } Find1[14];
    int sum = 0;
    int now;
    int distance = 0; //记录距离
    for (int i = 0; i <= 13; i++)
    {
        Find1[i].location=Find[i];
        Find1[i].flag = 0;
    }
    now = start;
    cout << "SSTF算法的遍历路径为:" << endl;
    cout << start << "-->";

    for (int k = 0; k <= 13; k++)
    {
        int size = 1000; //
        int num = -999;
        for (int i = 0; i <= 13; i++)
        {
            distance = abs(now - Find1[i].location);
            if (Find1[i].flag != 1)
            {
                if (size > distance) //记录最短距离
                {
                    size = distance;
                    num = i;  //记录最短距离的是第几个
                }
            }
        }
        now = Find1[num].location;
        Find1[num].flag = 1;
        sum += size;
        if (k == 13)
            cout << Find1[num].location << endl;
        else
            cout << Find1[num].location << "-->";
    }
    cout << "SSTF算法的平均移动道数为：" << sum /14 << endl;
}
bool cmp_high(int a, int b)
{
    return a < b;
}
bool cmp_low(int a, int b)
{
    return a > b;
}
void SCAN()
{
    int Find[14] = { 30,50,100,180,20,90,150,70,80,10,160,120,40,110 };
    int sum = 0, now;
    int sstart=start;
    int high[15];
    int a = 0;
    int low[15];
    int b = 0;
    for (int i = 0; i <= 14; i++)
    {
       
        if (Find[i] >= start)//比start大的
        {
            high[a++] = Find[i];
        }
        else
        {
            low[b++] = Find[i];//比start小的
        }
    }
    sort(high , high + a-1, cmp_high);  //排序
    sort(low , low + b-1, cmp_low);


    cout << "SCAN算法的遍历路径为:" << endl;
    cout << sstart << "-->";

    for (int i = 0; i < a; i++)
    {
        cout << high[i] << "-->";
        sum += abs(sstart - high[i]);
        sstart = high[i];
    }
    for (int i = 0; i < b-1; i++)
    {
        if (i == b - 2)
            cout << low[i] << endl;
        else
            cout << low[i] << "-->";
        sum += abs(sstart - low[i]);
        sstart = low[i];
    }
    cout << "SCAN算法的磁头平均移动道数为：" << sum /14<< endl;
}

int main()
{
    FCFS();
    SSTF();
    SCAN();
    return 0;
}


