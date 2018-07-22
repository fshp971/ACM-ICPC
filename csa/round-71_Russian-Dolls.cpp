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

const int maxn = 1e5;

int n, seg[maxn + 5];
int m, val[maxn + 5], cnt[maxn + 5];
int vv[maxn + 5], cc[maxn + 5];

int main() {
    scanf("%d", &n);
    REP(i,1,n) scanf("%d", seg + i);
    sort(seg + 1, seg + 1 + n);
    m = 0;
    for(int i = 1; i <= n; ++i) {
        val[++m] = seg[i], cnt[m] = 1;
        while(i+1 <= n && val[m] == seg[i+1])
            ++i, ++cnt[m];
    }
    if(val[m] == 1) { puts("0"); exit(0); }
    int ans = 1 << 30;
    for(int vv = val[m]+1, cc = 0, res = 0; vv > 1 && cc < n;) {
        --vv, res += cc, cc *= 2;
        if(m && val[m] == vv) cc += cnt[m], --m;
        int pv = val[m]+1, pc = 0, pt = m, tmp = 0;
        while((pv > 1 && pc > cc) || pt) {
            if(pc >= cc*2) break;
            if(pc <= cc)
                pv = val[pt], pc = cnt[pt], --pt;
            else {
                int d = pc - cc;
                tmp += d, --pv, pc = d*2;
                if(pt && val[pt] == pv) pc += cnt[pt], --pt;
            }
        }
        if(pc > cc) continue;
        ans = min(ans, res + tmp);
    }
    printf("%d\n", ans);
    return 0;
}
