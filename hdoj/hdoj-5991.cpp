#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
#include<utility>
#include<map>
#include<set>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define sf scanf
#define pf printf
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 100;

int n, ans;
bool mmp[maxn+5][maxn+5];

void dfs(int res)
{
	int A = 0, B = 0, C = 0;
	if(res >= ans) return;
	for(int i=1; i<=n && !A; ++i)
		for(int k=i+1; k<=n && !A; ++k)
			if(mmp[i][k])
			{
				for(int j=1; j<=n && !A; ++j)
					if(i!=j && k!=j && (mmp[i][j]^mmp[j][k]))
						A = i, B = k, C = j;
			}
	if(A == 0)
	{
		ans = res;
		return;
	}
	mmp[A][B] = mmp[B][A] = mmp[A][B]^1; dfs(res+1);
	mmp[A][B] = mmp[B][A] = mmp[A][B]^1, mmp[A][C] = mmp[C][A] = mmp[A][C]^1; dfs(res+1);
	mmp[A][C] = mmp[C][A] = mmp[A][C]^1, mmp[B][C] = mmp[C][B] = mmp[B][C]^1; dfs(res+1);
	mmp[B][C] = mmp[C][B] = mmp[B][C]^1;
}

int main()
{
	int T, a;
	sf("%d", &T);
	REP(t,1,T)
	{
		printf("Case #%d: ", t);
		sf("%d", &n);
		REP(i,1,n)
			REP(k,1,n)
				sf("%d", &a), mmp[i][k] = a;
		ans = 11;
		dfs(0);
		if(ans == 11) printf("-1\n");
		else printf("%d\n", ans);
	}
	return 0;
}
