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
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e5;

bool vis[maxn + 5];
int prime[maxn + 5], mu[maxn + 5];
vector<int> deco[maxn + 5], divide[maxn + 5];

void Init() {
    int tot = 0;
    mu[1] = 1;
    for(int i = 2; i <= maxn; ++i) {
        if(!vis[i]) prime[++tot] = i, mu[i] = -1;
        for(int k = 1; k <= tot; ++k) {
            if(LL(prime[k]) * i > maxn) break;
            vis[prime[k] * i] = true;
            if(i % prime[k]) mu[i * prime[k]] = -mu[i];
            else { mu[i * prime[k]] = 0; break; }
        }
    }
    for(int i = 1; i <= tot; ++i)
        for(int k = prime[i]; k <= maxn; k += prime[i])
            deco[k].PB(prime[i]);
    for(int i = 1; i <= maxn; ++i) {
        for(int k = (1 << deco[i].size()) - 1; k >= 0; --k) {
            int res = 1;
            for(int j = 0; j < deco[i].size(); ++j)
                if(k >> j & 1) res *= deco[i][j];
            divide[i].PB(res);
        }
    }
}

int n;
int aa[maxn + 5], bb[maxn + 5];
vector<int> seg1[maxn + 5], seg2[maxn + 5];
map<int,int> cnt1, cnt2;

LL Calc(int d) {
    if(!seg1[d].size() || !seg2[d].size()) return 0LL;
    cnt1.clear(); cnt2.clear();
    for(auto it : seg1[d])
        for(auto dd : divide[it])
            ++cnt1[dd];
    for(auto it : seg2[d])
        for(auto dd : divide[it]) {
            if(cnt1.find(dd) != cnt1.end())
                ++cnt2[dd];
        }
    LL res = 0;
    for(auto it : cnt2)
        res += LL(mu[it.fi]) * cnt1[it.fi] * it.se;
    return res;
}

int main() {
    Init();
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", aa + i);
    for(int i = 1; i <= n; ++i) scanf("%d", bb + i);
    for(int i = 1; i <= n; ++i) seg1[aa[bb[i]]].PB(i);
    for(int i = 1; i <= n; ++i) seg2[bb[aa[i]]].PB(i);
    LL ans = 0;
    for(int i = 1; i <= n; ++i) ans += Calc(i);
    printf("%lld\n", ans);
    return 0;
}
