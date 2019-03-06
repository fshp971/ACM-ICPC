#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cassert>
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
#include<stack>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define PER(i,a,b) for(int i=a; i>=b; --i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;

const int maxn = 3000;

const LL base = 19260817, P = 1e9+7;
LL pw[maxn+5], ha[maxn+5];

const LL base2 = 37, P2 = 1e9+9;
LL pw2[maxn+5], ha2[maxn+5];

int n, s[maxn+5];
LL f[maxn+5][maxn+5], ans[maxn+5];
set<pair<LL,LL>> Set;

const int md = 1e9+7;
inline void Add(LL &a, LL b) { a+=b; if(a>=md) a-=md; }

bool Chk(int k) {
    if(s[k-3]==0 && s[k-2]==0 && s[k-1]==1 && s[k]==1) return false;
    if(s[k-3]==0 && s[k-2]==1 && s[k-1]==0 && s[k]==1) return false;
    if(s[k-3]==1 && s[k-2]==1 && s[k-1]==1 && s[k]==0) return false;
    if(s[k-3]==1 && s[k-2]==1 && s[k-1]==1 && s[k]==1) return false;
    return true;
}

int main() {
    pw[0] = pw2[0] = 1;
    REP(i,1,maxn) {
        pw[i] = pw[i-1] * base % P;
        pw2[i] = pw2[i-1] * base2 % P2;
    }
    scanf("%d", &n);
    REP(i,1,n) {
        scanf("%d", s+i);
        ha[i] = (ha[i-1]*base + s[i]) % P;
        ha2[i] = (ha2[i-1]*base2 + s[i]) % P2;
    }
    REP(i,1,n) {
        REP(k,i,n) {
            REP(t,1,3) if(k-t>=i-1)
                Add(f[i][k], (k-t>=i) ? f[i][k-t] : 1);
            if(k-4>=i-1 && Chk(k))
                Add(f[i][k], (k-4>=i) ? f[i][k-4] : 1);
        }
    }
    for(int l = 1; l <= n; ++l) {
        Set.clear();
        for(int i = 1, k = l; k <= n; ++i, ++k) {
            LL tmp = (ha[k] - ha[i-1]*pw[l]%P + P) % P;
            LL tmp2 = (ha2[k] - ha2[i-1]*pw2[l]%P2 + P2) % P2;
            if(Set.find(pair<LL,LL>(tmp,tmp2)) != Set.end()) continue;
            Set.insert(pair<LL,LL>(tmp,tmp2));
            Add(ans[k], f[i][k]);
        }
    }
    REP(i,1,n) {
        Add(ans[i], ans[i-1]);
        printf("%lld\n", ans[i]);
    }
    return 0;
}
