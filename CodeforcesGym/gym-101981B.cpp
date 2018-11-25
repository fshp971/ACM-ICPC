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
typedef pair<int,int> pii;

const int maxn = 3e5;

int n, kk;
LL ai[maxn+5];

LL f[maxn+5];
int num[maxn+5], q[maxn+5], L[maxn+5], R[maxn+5];

inline LL Calc(int l, int r) { return (ai[r] - ai[((l+r+1)>>1)-1]) - (ai[(l+r)>>1] - ai[l-1]); }

void Run(LL cost) {
    f[0] = 0, num[0] = 0;
    int s = 1, t = 1;
    q[1] = 0, L[1] = 1, R[1] = n;
    REP(i,1,n) {
        while(s+1<=t && R[s]<i) ++s;
        f[i] = f[q[s]] + Calc(q[s]+1,i) + cost;
        num[i] = num[q[s]] + 1;
        while(s<=t && i<=L[t] && f[q[t]]+Calc(q[t]+1,L[t]) > f[i]+Calc(i+1,L[t])) --t;
        if(s>t) ++t, q[t] = i, L[t] = i+1, R[t] = n;
        else {
            int l = max(L[t],i), r = R[t], ps = r+1;
            while(l<=r) {
                int mid = (l+r)>>1;
                if(f[q[t]]+Calc(q[t]+1,mid) > f[i]+Calc(i+1,mid)) ps = mid, r = mid-1;
                else l = mid+1;
            }
            R[t] = ps-1;
            if(ps<=n) ++t, q[t] = i, L[t] = ps, R[t] = n;
        }
    }
}

int main() {
    scanf("%d%d", &n, &kk);
    REP(i,1,n) scanf("%lld", ai+i), ai[i]+=ai[i-1];
    LL l = 0, r = maxn*LL(1e9), rc = r+1;
    while(l<=r) {
        LL mid = (l+r)>>1;
        Run(mid);
        if(num[n] <= kk) rc = mid, r = mid-1;
        else l = mid+1;
    }
    Run(rc);
    LL ans = f[n] - rc*kk;
    printf("%lld\n", ans);
    return 0;
}
