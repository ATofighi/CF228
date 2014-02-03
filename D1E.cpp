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

long long gcd(long long a, long long b)
{
	if(a == 0 || b == 0)return a + b;
	return gcd(b, a % b);
}

struct vector3D
{
	long long x, y, z;
	vector3D to(vector3D that)
	{
		vector3D ret;
		ret.x = that.x - x;
		ret.y = that.y - y;
		ret.z = that.z - z;
		return ret;
	}
	vector3D crossProduct(vector3D that)
	{
		vector3D ret;
		ret.x = y * that.z - z * that.y;
		ret.y = z * that.x - x * that.z;
		ret.z = x * that.y - y * that.x;
		return ret;
	}
	long long dotProduct(vector3D that)
	{
		return x * that.x + y * that.y + z * that.z;
	}
	void std()
	{
		long long g = gcd(abs(x), abs(y));
		g = gcd(abs(z), g);
		if(g > 0)
		{
			x /= g;
			y /= g;
			z /= g;
		}
		if(x < 0 || (x == 0 && y < 0) || (x == 0 && y == 0 && z < 0))
		{
			x = -x;
			y = -y;
			z = -z;
		}
	}
	bool isZero()
	{
		return (x == 0) && (y == 0) && (z == 0);
	}
	vector <long long> getHash()
	{
		vector <long long> ret;
		ret.push_back(x);
		ret.push_back(y);
		ret.push_back(z);
		return ret;
	}
};

struct segment
{
	vector3D A, B;
}S[2001];

struct rational
{
	long long v1, v2;
	void std()
	{
		long long g = gcd(abs(v1), abs(v2));
		if(g > 0)
		{
			v1 /= g;
			v2 /= g;
		}
		if(v1 < 0 || (v1 == 0 && v2 < 0))
		{
			v1 = -v1;
			v2 = -v2;
		}
	}
};

struct rationalPoint
{
	rational x, y, z;
	vector <long long> getHash()
	{
		vector <long long> ret;
		ret.push_back(x.v1); ret.push_back(x.v2);
		ret.push_back(y.v1); ret.push_back(y.v2);
		ret.push_back(z.v1); ret.push_back(z.v2);
		return ret;
	}
};

int n;
map < vector<long long> , map <int, bool> > passThisPoint_occur;
map < vector<long long> , int > passThisPoint_cnt;

map < vector<long long> , map < vector <long long> , bool > > passThisPlane_occur;
map < vector<long long> , int > passThisPlane_cnt;
int ans = 1;

void solveSegmentPair(int id1, int id2)
{
	segment S1 = S[id1];
	segment S2 = S[id2];
	vector3D normalVector = (S1.A.to(S1.B)).crossProduct(S2.A.to(S2.B));
	normalVector.std();

	// S1 is parallel to S2
	if(normalVector.isZero())
	{
		return;
	}

	long long v1 = normalVector.dotProduct(S1.A);
	long long v2 = normalVector.dotProduct(S2.A);

	// not in the same plane
	if(v1 != v2)
		return;

	vector3D n1 = S1.A.to(S2.A).crossProduct(S1.A.to(S2.B));
	vector3D n2 = S1.B.to(S2.A).crossProduct(S1.B.to(S2.B));
	n2.x = -n2.x; n2.y = -n2.y; n2.z = -n2.z;

	long long r1, r2;
	if(n2.x != 0 || n1.x != 0)
	{
		r1 = n2.x;
		r2 = n1.x;
	}
	else if(n2.y != 0 || n1.y != 0)
	{
		r1 = n2.y;
		r2 = n1.y;
	}
	else
	{
		r1 = n2.z;
		r2 = n1.z;
	}

	rationalPoint p;
	p.x.v1 = S1.A.x * r1 + S1.B.x * r2;
	p.x.v2 = r1 + r2;
	p.x.std();
	p.y.v1 = S1.A.y * r1 + S1.B.y * r2;
	p.y.v2 = r1 + r2;
	p.y.std();
	p.z.v1 = S1.A.z * r1 + S1.B.z * r2;
	p.z.v2 = r1 + r2;
	p.z.std();

	vector <long long> hash = p.getHash();
	
	if(passThisPoint_occur[hash].count(id1) == false)
	{
		passThisPoint_occur[hash][id1] = true;
		passThisPoint_cnt[hash] += 1;
		ans = max(ans, passThisPoint_cnt[hash]);
	}
	
	if(passThisPoint_occur[hash].count(id2) == false)
	{
		passThisPoint_occur[hash][id2] = true;
		passThisPoint_cnt[hash] += 1;
		ans = max(ans, passThisPoint_cnt[hash]);
	}

	normalVector.std();
	hash = normalVector.getHash();
	hash.push_back(v1);

	vector3D dir1 = S1.A.to(S1.B);
	dir1.std();
	vector <long long> hash1 = dir1.getHash();
	vector3D dir2 = S2.A.to(S2.B);
	dir2.std();
	vector <long long> hash2 = dir2.getHash();

	if(passThisPlane_occur[hash].count(hash1) == false)
	{
		passThisPlane_occur[hash][hash1] = true;
		passThisPlane_cnt[hash] += 1;
		ans = max(ans, passThisPlane_cnt[hash]);
	}

	if(passThisPlane_occur[hash].count(hash2) == false)
	{
		passThisPlane_occur[hash][hash2] = true;
		passThisPlane_cnt[hash] += 1;
		ans = max(ans, passThisPlane_cnt[hash]);
	}

}

bool onTheLine(segment seg, vector3D v)
{
	vector3D h = v.to(seg.A).crossProduct(v.to(seg.B));
	return h.isZero();
}

bool isSameLine(segment S1, segment S2)
{
	return onTheLine(S1, S2.A) && onTheLine(S1, S2.B);
}

int MAIN()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> S[i].A.x >> S[i].A.y >> S[i].A.z;
		cin >> S[i].B.x >> S[i].B.y >> S[i].B.z;
	}
	for(int i = 1; i <= n; i++)
		for(int j = i+1; j <= n; j++)
			solveSegmentPair(i, j);

	cout << ans << endl;
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
