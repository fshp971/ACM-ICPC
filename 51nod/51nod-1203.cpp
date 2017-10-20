//#include<cstdio>
#include<stdio.h>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<queue>
#include<utility>
#include<bitset>
#include<complex>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
typedef long long LL;
typedef pair<int,int> pii;

#define fi first
#define se second

const int maxn = 5e5, md = 1e9 + 7;

int tot, all;
int tree[maxn * 19 + 5];
void Add(int x, int val) { for(; x <= all; x += x&(-x)) tree[x] = LL(tree[x])*val % md; }
int Sum(int x) { int res = 1; for(; x; x -= x&(-x)) res = LL(res)*tree[x] % md; return res; }

bool vis[maxn + 5];
vector<int> deco[maxn + 5];
void GetPrime() {
    for(int i = 2; i <= maxn; ++i)
        if(!vis[i]) {
            for(int k = i; k <= maxn; k += i)
                vis[k] = 1, deco[k].PB(i);
        }
}

LL PowMod(LL a, LL b) { LL res = 1; while(b) { if(b&1) res = res*a % md; a = a*a % md; b >>= 1; } return res; }

int n, m, seg[maxn + 5], L[maxn + 5], pre[maxn + 5];
LL ans[maxn + 5];
vector<pii> que1[maxn + 5];
vector<int> que2[maxn + 5];

int main() {
    GetPrime();
    int u, l, r;
    scanf("%d%d", &n, &m), tree[tot = 1] = 1, all = n * 19;
    for(int i = 1; i <= maxn; ++i) pre[i] = 1;
    for(int i = 1; i <= all; ++i) tree[i] = 1;
    for(int i = 1; i <= n; ++i) scanf("%d", seg + i);
    for(int i = 1; i <= m; ++i)
        scanf("%d%d", &l, &r), que1[r].PB(MP(l,i)), que2[l].PB(i);
    for(int i = 1; i <= n; ++i) {
        for(auto it : que2[i])
            ans[it] = PowMod(Sum(tot), md - 2);
        L[i] = tot + 1;
        if(seg[i] == 1) ++tot;
        else {
            for(auto it : deco[seg[i]])
                for(LL k = it; seg[i] % k == 0; k *= it)
                    Add(pre[k], it), pre[k] = ++tot;
        }
        for(auto it : que1[i])
            ans[it.se] = ans[it.se] * Sum(L[it.fi] - 1) % md;
    }
    for(int i = 1; i <= m; ++i) printf("%lld\n", ans[i]);
    return 0;
}
