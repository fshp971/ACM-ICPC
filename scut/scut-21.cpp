#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))
#define MP(a,b) make_pair(a,b)
#define sf scanf
#define pf printf

int n, m, kk, aa[10005];
int num[305], cont[105];
int f[105];

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int T, tmp[105], dt, len;
	int ans1, ans2;
	sf("%d", &T);
	while(T--)
	{
		sf("%d%d", &n, &kk);
		REP(i,1,n) sf("%d", aa+i), tmp[i] = aa[i];
		sort(tmp+1, tmp+1+n);
		m = 0, tmp[0] = 0;
		REP(i,1,n)
		{
			if(tmp[i] != tmp[i-1])
				num[tmp[i]] = ++m, cont[m] = 1;
			else ++cont[m];
		}
		REP(i,1,n) aa[i] = num[aa[i]];
		dt = min(m, kk);
		len = dt*n;
		for(int i=n+1; i<=len; ++i) aa[i] = aa[i-n];
		mem(f, 0);
		for(int i=1; i<=len; ++i)
		{
			++f[aa[i]];
			for(int k=0; k<aa[i]; ++k)
				f[aa[i]] = max(f[aa[i]], f[k]+1);
		}
		ans1 = ans2 = 0;
		for(int i=1; i<=m; ++i)
			ans1 = max(ans1, cont[i]), ans2 = max(ans2, f[i]);
		pf("%d\n", ans1 * max(0, kk-dt) + ans2);
	}
	return 0;
}
