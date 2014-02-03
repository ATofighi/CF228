#include <algorithm>
#include <iostream>
#include <iomanip>
#include <complex>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <map>
#include <set>
using namespace std;
//#pragma comment(linker,"/STACK:102400000,102400000")

int z;
int id[32][32];
bool G[501][501];

void addEdge(int i, int j, int i2, int j2)
{
	G[id[i][j]][id[i2][j2]] = true;
	G[id[i2][j2]][id[i][j]] = true;
}

int MAIN()
{
	z = 3;
	id[1][1] = 1;
	id[1][2] = 2;
	for(int i = 2; i <= 31; i++)
		for(int j = 1; j <= i; j++)
		{
			id[i][j] = z;
			z ++;
		}
	memset(G, 0, sizeof(G));
	for(int i = 2; i <= 31; i++)
		for(int j = 1; j <= i; j++)
		{
			addEdge(i, j, i-1, 1);
			for(int k = 1; k < j; k++)
				addEdge(i, j, i-1, k);
		}
	int want;
	cin >> want;
	for(int i = 0; i < 30; i++)
		if((want&(1<<i)) > 0)
			addEdge(1,2,31,i+2);
	cout << z << endl;
	for(int i = 1; i <= z; i++)
	{
		for(int j = 1; j <= z; j++)
		{
			if(G[i][j])
				cout << "Y";
			else
				cout << "N";
		}
		cout << endl;
	}
	return 0;
}

int main()
{
	#ifdef LOCAL_TEST
		freopen("in.txt", "r", stdin);
		freopen("out.txt", "w", stdout);
	#endif
	ios :: sync_with_stdio(false);
	cout << fixed << setprecision(16);
	return MAIN();
}
