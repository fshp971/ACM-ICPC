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

const int maxn = 500000;

int n, m;
LL f[maxn+5], sum[maxn+5];

int que[maxn+5], head, tail;

inline LL cal_y(int i, int k)
{
	return f[k] + sum[k]*sum[k] - f[i] - sum[i]*sum[i];
}

inline LL cal_x(int i, int k)
{
	return (sum[k] - sum[i]) * 2;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	while(~sf("%d%d", &n, &m))
	{
		sum[0] = f[0] = 0;
		REP(i,1,n)
			sf("%lld", sum+i), sum[i] += sum[i-1];
		que[head=tail=1] = 0;
		for(int i=1; i<=n; ++i)
		{
			while(head<tail && cal_y(que[head], que[head+1]) <= sum[i] * cal_x(que[head], que[head+1]))
				++head;
			f[i] = f[que[head]] + (sum[i]-sum[que[head]]) * (sum[i]-sum[que[head]]) + m;
			while(tail>head && cal_y(que[tail-1],que[tail]) * cal_x(que[tail], i)  >= cal_y(que[tail], i) * cal_x(que[tail-1], que[tail]))
				--tail;
			que[++tail] = i;
		}
		pf("%lld\n", f[n]);
	}
	return 0;
}
