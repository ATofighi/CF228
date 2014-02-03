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

long long n;
long long mod = 1000000007;
long long F[101][101][2];

long long f(int cur, int nBase, int alreadyLess)
{

	if(cur < 0) return 1;
	long long &ret = F[cur][nBase][alreadyLess];
	if(ret >= 0) return ret;
	ret = 0;
	int thisBit = (n & (1LL << cur)) > 0;
	// add base
	if(alreadyLess == 1 || thisBit == 1)
	{
		ret += f(cur-1, nBase + 1, alreadyLess);
		ret %= mod;
	}

	// not add base
	if(nBase == 0)
	{
		ret += f(cur-1, nBase, alreadyLess | (thisBit == 1));
		ret %= mod;
	}
	else
	{
		// add  1
		if(alreadyLess == 1 || thisBit == 1)
		{
			ret += f(cur-1, nBase, alreadyLess) * (1LL << (nBase-1));
			ret %= mod;
		}

		// add 0
		ret += f(cur-1, nBase, alreadyLess | (thisBit == 1)) * (1LL << (nBase-1));
		ret %= mod;
	}
	
	ret %= mod;
	return ret;
}


int MAIN()
{
	cin >> n;
	memset(F, 0xff, sizeof(F));
	cout << f(31, 0, 0) << endl;
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
