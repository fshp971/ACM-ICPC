#include <bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
#define PB push_back
#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define PER(i,a,b) for(int i = a; i >= b; --i)
#define fi first
#define se second
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> pii;

const int maxn = 2e5;
const ULL base = 19260817;

int n, m, kk;
int wd[maxn+5];
int ans[maxn+5];
ULL pw[maxn+5], ha[maxn+5];
set<ULL> Set;

int main() {
    pw[0] = 1;
    REP(i,1,maxn) pw[i] = pw[i-1] * base;
    scanf("%d%d%d", &n, &m, &kk);
    REP(i,0,m-1) scanf("%d", wd+i);
    --kk;
    int len = n;
    Set.insert( ULL(0) );
    while(kk--) {
        bool fg = 0;
        ULL h = (ha[len] - ha[len-(n-1)] * pw[n-1]) * base;
        for(int i = m-1; i >= 0; --i) {
            ULL tmp = h+i;
            if(Set.find(tmp) == Set.end()) {
                fg = 1;
                Set.insert(tmp);
                ++len, ans[len] = i, ha[len] = ha[len-1]*base+i;
                break;
            }
        }
        assert(fg);
    }
    REP(i,1,len) printf("%d", wd[ans[i]]);
    puts("");
    return 0;
}
