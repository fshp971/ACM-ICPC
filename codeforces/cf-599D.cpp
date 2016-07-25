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

#define lld I64d

const int maxn = 2e6;

LL xx;
LL arr[maxn*2+5][2];

bool check(LL cc, LL aa, LL &bb)
{
	cc *= 6;
	if(cc % aa) return false;
	cc /= aa;
	if(cc % (aa+1)) return false;
	cc /= (aa+1);
	cc += aa-1;
	if(cc % 3) return false;
	bb = cc / 3;
	return bb >= aa;
}

void init()
{
	cin >> xx;
	int top = 0;
	LL b;
	for(int i=1; i<=maxn; ++i)
	{
		if(check(xx, i, b))
			arr[++top][0] = i, arr[top][1] = b;
	}
	int m = top*2;
	if(arr[top][0] == arr[top][1]) --m;
	pf("%d\n", m);
	for(int i=1;i<=top;++i) pf("%lld %lld\n", arr[i][0], arr[i][1]);
	if(arr[top][0] == arr[top][1]) --top;
	for(int i=top;i>=1;--i) pf("%lld %lld\n", arr[i][1], arr[i][0]);
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
