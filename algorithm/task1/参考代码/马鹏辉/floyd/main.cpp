#include<iostream>
#include <iomanip>
#define N  5//顶点数
#define MAX 10000
using namespace std;
int A[N][N] = { {0,4,MAX,6,1},
               {4,0,5,MAX,3},
               {MAX,2,0,5,4},
               {4,9,3,0,2},
               {7,4,2,9,0}
};
int D[N][N];//D为最短路径长度矩阵
int Path[N][N];//Path为最短路径

void Floyd() {

    int i, j, k;
    for( i=0;i<N;i++)
        for (j = 0; j < N; j++) {
            D[i][j] = A[i][j];
            if (i != j && A[i][j] < MAX) Path[i][j] = i;
            else Path[i][j] = -1;

        }
    for(k=0;k<N;k++)
        for(i=0;i<N;i++)
            for(j=0;j<N;j++)
                if(D[i][k]+D[k][j]<D[i][j])
                {
                    D[i][j] = D[i][k] + D[k][j];
                    Path[i][j] = Path[k][j];
                }

}

int main() {
     Floyd();
     cout << "最短路径长度矩阵D" << endl;
    for (int j = 0; j < N; j++)
    {
        for (int k = 0; k < N; k++)
        {
            cout << setiosflags(ios::left);
            cout<<setw(3) << D[j][k];
        }

        cout << endl;
    }
    cout << "--------------------" << endl;
    cout << "最短路径Path" << endl;
    for (int j = 0; j < N; j++)
    {
        for (int k = 0; k < N; k++)
        {
            cout << setiosflags(ios::left);
            cout << setw(7) << Path[j][k];
        }

        cout << endl;
    }cout << endl;

}
