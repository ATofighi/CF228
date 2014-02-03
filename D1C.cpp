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

int ansA = 0, ansB = 0;

int MAIN()
{
	int n;
	cin >> n;
	vector <int> mids;
	for(int i = 1; i <= n; i++)
	{
		int s;
		cin >> s;
		for(int j = 1; j <= s; j++)
		{
			int t;
			cin >> t;
			if(s%2 == 0)
			{
				if(j <= s/2)
					ansA += t;
				else
					ansB += t;
			}
			else
			{
				if(j <= s/2)
					ansA += t;
				else if(j > s/2+1)
					ansB += t;
				else
					mids.push_back(t);
			}
		}
	}
	sort(mids.begin(), mids.end());
	reverse(mids.begin(), mids.end());
	for(int i = 0; i < mids.size(); i++)
		if(i % 2 == 0)
			ansA += mids[i];
		else
			ansB += mids[i];
	cout << ansA << " " << ansB << endl;
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
