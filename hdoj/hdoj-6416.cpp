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

#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define FOR(i,a,b) for(int i = a; i < b; ++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 2e3;
const int P = 998244353;

int n, m, kk;
int T = 0;
int f[2][maxn+5][maxn+5];
int vi[maxn+5][maxn+5];
int sta[2][maxn*maxn+5][2], top[2];
char str[maxn+5];
int pre[maxn+5], nex[maxn+5];

inline void Add(int &a, int b) { a+=b; if(a>=P) a-=P; }
inline void Upd(int pr, int l, int r, int b) {
    if(vi[l][r] != T) {
        ++top[pr], sta[pr][top[pr]][0] = l, sta[pr][top[pr]][1] = r;
        vi[l][r] = T, f[pr][l][r] = b;
    }
    else Add(f[pr][l][r], b);
}

int main() {
    int _; scanf("%d", &_);
    while(_--) {
        scanf("%d%d%d", &n, &m, &kk);
        int pr = 0;
        top[pr] = 1, sta[pr][1][0] = 1, sta[pr][1][1] = m;
        f[pr][1][m] = 1;
        while(n--) {
            scanf("%s", str+1);
            nex[m] = m;
            for(int i = m-1; i >= 1; --i) {
                if(str[i]==str[i+1])
                    nex[i] = nex[i+1];
                else nex[i] = i;
            }
            pre[1] = 1;
            for(int i = 2; i <= m; ++i) {
                if(str[i]==str[i-1])
                    pre[i] = pre[i-1];
                else pre[i] = i;
            }
            ++T;
            top[pr^1] = 0;
            for(int i = 1; i <= m; i = nex[i]+1) {
                Upd(pr^1, i, nex[i], 0);
            }
            while(top[pr]>=1) {
                int l = sta[pr][top[pr]][0], r = sta[pr][top[pr]][1];
                --top[pr];
                int kl = max(1,l-kk), kr = min(m,r+kk);
                if(pre[kl] != kl) {
                    Upd(pr^1, kl, min(nex[kl],kr), f[pr][l][r]);
                    kl = min(nex[kl],kr) + 1;
                }
                if(kl > kr) continue;
                if(nex[kr] != kr) {
                    Upd(pr^1, pre[kr], kr, f[pr][l][r]);
                    kr = pre[kr]-1;
                }
                if(kl > kr) continue;
                Add(f[pr^1][kl][nex[kl]], f[pr][l][r]);
                if(kr+1 <= m)
                    Add(f[pr^1][kr+1][nex[kr+1]], P-f[pr][l][r]);
            }
            for(int i = nex[1]+1; i <= m; i = nex[i]+1) {
                Add(f[pr^1][i][nex[i]], f[pr^1][pre[i-1]][i-1]);
            }
            pr ^= 1;
        }
        int ans = 0;
        for(int i = 1; i <= top[pr]; ++i) {
            int l = sta[pr][i][0], r = sta[pr][i][1];
            Add(ans, f[pr][l][r]);
        }
        printf("%d\n", ans);
    }
    return 0;
}
