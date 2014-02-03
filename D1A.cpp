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

int n;
int x[1000001];

bool check(int piles)
{
	for(int i = 0; i < n; i++)
	{
		if(x[i] < i / piles)
			return false;
	}
	return true;
}

int MAIN()
{
	cin >> n;
	for(int i = 0; i < n; i++)
		cin >> x[i];
	sort(x, x + n);
	int L = 0, R = n, M;
	while(R-L > 1)
	{
		M = (L + R) / 2;
		if(check(M))
			R = M;
		else
			L = M;
	}
	cout << R << endl;
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
