#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define Max  999999

void Prim(vector<vector<int> > V)
{
	vector<int> d;  //记录从U到V-U中各点的最短边
	vector<int> U;  //记录被加入到U中的点
	vector<bool> visited;  //记录点是否被加入U中
	vector<int> M;  //记录最终得到的各条边
	d.resize(V.size());
	visited.resize(V.size());
	fill(visited.begin(), visited.end(), false);

	U.push_back(0);
	visited[0] = true;
	fill(d.begin(), d.end(), Max);
	d[0] = 0;
	while (U.size() < V.size())
	{
		int x = U[U.size() - 1];         
		for (int i = 0; i < d.size(); ++i)  //更新从U到V-U中各点的最短边
		{
			if (!visited[i] && V[x][i] < d[i])
			{
				d[i] = V[x][i];
			}
		}
		int min = Max;
		int index = 0;
		for (int i = 0; i < d.size(); ++i)   //寻找从U到V-U的最短边
		{
			if (d[i] < min && !visited[i])
			{
				min = d[i];
				index = i;
			}
		}
		if (index == 0)
		{
			cout << "this path is blocked" << endl;
			return;
		}
		visited[index] = true;
		U.push_back(index);
		M.push_back(min);
	}
	for (int i = 0; i < M.size(); ++i)  //输出所得最小生成树的各条边
	{
		cout << M[i] << "  ";
	}
}

int main()
{
	int n = 0;
	int m = 0;
	int u, v, w;
	cout << "insert the number of node" << endl;
	cin >> n;
	cout << "insert the number of edge" << endl;
	cin >> m;
	vector<vector<int> > V;
	V.resize(n);
	for (int i = 0; i < n; ++i)
	{
		V[i].resize(n);
		for (int j = 0; j < n; ++j)
		{
			V[i][j] = Max;
		}
	}
	cout << "insert the info of each edge" << endl;
	for (int i = 0; i < m; ++i)
	{
		cin >> u >> v >> w;
		V[u][v] = V[v][u] = w;
	}
	Prim(V);

	return 0;
}


