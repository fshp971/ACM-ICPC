#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e5, MaxStep = 17;

int n, seg[maxn + 5], nex[maxn + 5];
int mx[maxn + 5][MaxStep + 2], mi[maxn + 5][MaxStep + 2];

int Max(int l, int r) {
    int i = 0;
    for(; (1 << (i+1)) <= (r-l+1); ++i);
    return max(mx[r][i], mx[l + (1<<i) - 1][i]);
}

int Min(int l, int r) {
    int i = 0;
    for(; (1 << (i+1)) <= (r-l+1); ++i);
    return min(mi[r][i], mi[l + (1<<i) - 1][i]);
}

bool Check(int p) {
    for(int i = 1; i <= n; ++i) {
        int l = i + 1, r = n;
        nex[i] = i;
        while(l <= r) {
            int mid = (l + r) >> 1;
            if(seg[i] - p <= Min(i+1,mid) && Max(i+1,mid) <= seg[i] + p)
                nex[i] = mid, l = mid + 1;
            else r = mid - 1;
        }
    }
    int lim = 1;
    for(int i = 1; i <= n; ++i) {
        if(i > lim) return false;
        lim = max(lim, nex[i]);
    }
    return true;
}

int main() {
    scanf("%d", &n), n += 2;
    for(int i = 1; i <= n; ++i) {
        scanf("%d", seg + i);
        mx[i][0] = mi[i][0] = seg[i];
        for(int k = 1; (1 << k) <= i; ++k) {
            mx[i][k] = max(mx[i][k-1], mx[i - (1 << (k-1))][k-1]);
            mi[i][k] = min(mi[i][k-1], mi[i - (1 << (k-1))][k-1]);
        }
    }
    int l = 1, r = 1e9, ans = 2e9;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(Check(mid)) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    printf("%d\n", ans);
    return 0;
}
