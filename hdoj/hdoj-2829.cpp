#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define MP(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define sf scanf
#define pf printf

#define lld I64d

const int maxn = 1000;

int n, m;
int q[maxn+5];
LL f[maxn+5][maxn+5];
LL ww[maxn+5], sum[maxn+5];

inline LL dy(int i, int j, int k)
{
	return (f[j][k]-ww[j]+sum[j]*sum[j]) - (f[i][k]-ww[i]+sum[i]*sum[i]);
}

inline LL dx(int i, int j, int k)
{
	return sum[j]-sum[i];
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	while(sf("%d%d", &n, &m), n)
	{
		REP(i,1,n)
		{
			sf("%lld", sum+i);
			f[i][0] = ww[i] = ww[i-1] +sum[i] * sum[i-1];
			sum[i] += sum[i-1];
		}
		for(int j=1; j<=m; ++j)
		{
			int head = 1, tail = 1;
			q[1] = j-1;
			for(int i=j; i<=n; ++i)
			{
				while(head<tail && dy(q[head], q[head+1], j-1) <= dx(q[head], q[head+1], j-1) * sum[i])
					++head;
				f[i][j] = f[q[head]][j-1] - ww[q[head]] + sum[q[head]] * (sum[q[head]]-sum[i]) + ww[i];
				while(head<tail && dy(q[tail-1], q[tail], j-1)*dx(q[tail], i, j-1) >= dy(q[tail], i, j-1)*dx(q[tail-1], q[tail], j-1))
					--tail;
				q[++tail] = i;
			}
		}
		pf("%lld\n", f[n][m]);
	}
	return 0;
}
