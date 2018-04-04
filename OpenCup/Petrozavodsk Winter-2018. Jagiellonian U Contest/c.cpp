#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cassert>
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

const int maxn = 2e5;

int T = 0, tot = 0, vist[maxn + 5];
int tr[maxn + 5];
inline void Upd(int x, int v) {
    for(; x<=tot; x+=x&(-x)) {
        if(vist[x] != T) vist[x] = T, tr[x] = 0;
        tr[x] = max(tr[x], v);
    }
}

inline int Max(int x) {
    int res = 0;
    for(; x; x-=x&(-x)) {
        if(vist[x] != T) vist[x] = T, tr[x] = 0;
        res = max(res, tr[x]);
    }
    return res;
}

int n, ans[maxn + 5];
int xx[maxn + 5], yy[maxn + 5];

bool cmp(const int &a, const int &b) { return xx[a] < xx[b]; }

int arr1[maxn + 5], arr2[maxn + 5];
void Solve(int l, int r) {
    if(l == r) return;
    int mid = (l + r) >> 1, l1 = 0, l2 = 0;
    Solve(l, mid);
    for(int i = l; i <= mid; ++i) arr1[l1++] = i;
    for(int i = mid+1; i <= r; ++i) arr2[l2++] = i;
    sort(arr1, arr1 + l1, cmp);
    sort(arr2, arr2 + l2, cmp);
    ++T;
    for(int i = 0, k = 0; i < l2; ++i) {
        while(k < l1 && xx[arr1[k]] < xx[arr2[i]])
            Upd(yy[arr1[k]], ans[arr1[k]]), ++k;
        ans[arr2[i]] = max(ans[arr2[i]], Max(yy[arr2[i]] - 1) + 1);
    }
    Solve(mid + 1, r);
}

int yi[maxn + 5];
int main() {
    //freopen("in.txt", "r", stdin);
    int m;
    scanf("%d", &m);
    while(m--) {
        scanf("%d", &n);
        REP(i,1,n) scanf("%d", xx + i), ans[i] = 1;
        REP(i,1,n) scanf("%d", yy + i), yi[i] = yy[i];
        sort(yi + 1, yi + 1 + n);
        tot = unique(yi + 1, yi + 1 + n) - yi - 1;
        for(int i = 1; i <= n; ++i)
            yy[i] = lower_bound(yi + 1, yi + 1 + tot, yy[i]) - yi;
        Solve(1,n);
        int mx = 0;
        REP(i,1,n) mx = max(mx, ans[i]);
        printf("%d\n", mx);
    }
    return 0;
}
