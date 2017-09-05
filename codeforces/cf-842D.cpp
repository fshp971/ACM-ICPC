#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int MaxDep = 20;
const int maxn = 3e5;
const int maxnode = maxn * (MaxDep + 1);

int n, m, tot = 0;
int nex[maxnode][2];
bool cnt[maxnode];

int Build(int dep) {
	int rt = ++tot;
	cnt[rt] = 0;
	if(dep >= 0) {
		nex[rt][0] = Build(dep - 1);
		nex[rt][1] = Build(dep - 1);
	}
	return rt;
}

void Insert(int rt, int x, int dep) {
	if(dep < 0)
		cnt[rt] = 1;
	else {
		Insert(nex[rt][(x >> dep) & 1], x, dep - 1);
		cnt[rt] = cnt[nex[rt][0]] && cnt[nex[rt][1]];
	}
}

int Query(int u, int *rev, int MaxStep) {
	int res = 0;
	for(int i = MaxStep; i >= 0; --i) {
		if(cnt[nex[u][rev[i]]] == 0)
			u = nex[u][rev[i]];
		else {
			res |= (1 << i);
			u = nex[u][rev[i] ^ 1];
		}
	}
	return res;
}

int main() {
	int rt = Build(MaxDep);
	int a, rev[MaxDep + 5];
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a);
		Insert(rt, a, MaxDep);
	}
	mem(rev, 0);
	for(int i = 1; i <= m; ++i) {
		scanf("%d", &a);
		for(int i = MaxDep; i >= 0; --i)
			rev[i] ^= (a >> i) & 1;
		printf("%d\n", Query(rt, rev, MaxDep));
	}
	return 0;
}
