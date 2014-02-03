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
bool board[102][102];
int dx[] = {0, 1, -1, 0, 0};
int dy[] = {0, 0, 0, 1, -1};

bool tryFill(int x, int y)
{
	for(int i = 0; i < 5; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(!board[nx][ny])
			return false;
		board[nx][ny] = false;
	}
	return true;
}

int MAIN()
{
	cin >> n;
	memset(board, 0, sizeof(board));
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
		{
			char c;
			cin >> c;
			if(c == '#')
				board[i][j] = true;
		}
	bool bad = false;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			if(board[i][j])
				if(!tryFill(i+1, j))
					bad = true;
	if(!bad)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;
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
