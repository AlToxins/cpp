#include<iostream>
#include<fstream>
#include<math.h>
#include<string>
using namespace std;
struct poi
{
	double x, y;
	double z, v;
}p[5000], ans[1000];
int numnew = 0, numold = 0;
ifstream readfile, readfile1;
void readold()
{
	readfile.open("test_data_5_2.dat", ios::in);
	if (readfile.is_open())
	{
		char buf[1024] = { 0 };
		readfile >> buf;
		readfile >> buf;
		readfile >> buf;
		readfile >> buf;
		readfile >> buf;
		readfile >> buf;
		while (readfile >> buf)
		{
			numold++;
			for (int i = 1; i <= 4; i++)
			{
				if (i == 1)
				{
					int xx = stod(buf);
					//cout << xx<<endl;
					p[numold].x = xx;
				}
				else if (i == 2)
				{
					readfile >> buf;
					int yy = stod(buf);
					//cout << yy << endl;
					p[numold].y = yy;
				}
				else if (i == 3)
				{
					readfile >> buf;
					double zz = stod(buf);
					//cout << zz << endl;
					p[numold].z = zz;
				}
				else if (i == 4)
				{
					readfile >> buf;
					double vv = stod(buf);
					//cout << vv << endl;
					p[numold].v = vv;
				}
			}
		}
	}
}
void readnew()
{
	readfile1.open("test_data_5_1.dat", ios::in);
	if (readfile1.is_open())
	{
		char buff[1024] = { 0 };
		readfile1 >> buff;
		readfile1 >> buff;
		readfile1 >> buff;
		readfile1 >> buff;
		readfile1 >> buff;
		while (readfile1 >> buff)
		{
			numnew++;
			for (int i = 1; i <= 3; i++)
			{
				if (i == 1)
				{
					int xx = stod(buff);
					ans[numnew].x = xx;
				}
				else if (i == 2)
				{
					readfile1 >> buff;
					int yy = stod(buff);
					ans[numnew].y = yy;
				}
				else if (i == 3)
				{
					readfile1 >> buff;
					double zz = stod(buff);
					ans[numnew].z = zz;
				}

				ans[numnew].v = 0;
			}
		}
	}
}
void cal()
{
	for (int i = 1; i <= numnew; i++)
	{
		double vv = 0, dissum = 0;
		for (int j = 1; j <= numold; j++)
		{
			double dis = 0;
			dis = (ans[i].x - p[j].x) * (ans[i].x - p[j].x) + (ans[i].y - p[j].y) * (ans[i].y - p[j].y) + (ans[i].z - p[j].z) * (ans[i].z - p[j].z);
			vv += 1 / dis * p[j].v;
			dissum += 1 / dis;
		}
		ans[i].v = vv / dissum;
	}

}
int main()
{
	readold();
	readnew();
	cal();
	for (int i = 1; i <= numnew; i++)
	{
		cout << ans[i].x << ' ' << ans[i].y << ' ' << ans[i].z << ' ' << ans[i].v << endl;
	}
	return 0;
}
