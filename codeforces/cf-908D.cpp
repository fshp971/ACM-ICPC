#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1000;
const int md = 1e9 + 7;

inline LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%md; a=a*a%md, b>>=1; } return r; }

int n;
LL f[maxn + 5][maxn + 5];
LL pp, qq, inp, inq;

LL dfs(int has, int del) {
    if(f[has][del] != -1) return f[has][del];
    if(has + del >= n) return f[has][del] = (del + pp*inq) % md;
    return f[has][del] = (pp*dfs(has, del+1) + qq*(dfs(has+del, del) + del)) % md;
}

int main() {
    scanf("%d%lld%lld", &n, &pp, &qq);
    inp = (pp+qq) * PowMod(pp, md-2) % md;
    inq = (pp+qq) * PowMod(qq, md-2) % md;
    pp = PowMod(inp, md-2);
    qq = PowMod(inq, md-2);
    mem(f, -1);
    printf("%lld\n", dfs(0,1));
    return 0;
}
