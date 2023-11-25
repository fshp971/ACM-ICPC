#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define PER(i,a,b) for(int i = a; i >= b; --i)
#define PB push_back
#define MP make_pair
#define fi first
#define se second
typedef long long LL;
typedef long double LD;

const int maxn = 5e4;

int n, m;
vector<int> f(maxn+5), h(maxn+5);
vector<vector<pair<int,int>>> G(maxn+5);

void calc(int x, int p, int &lim) {
    f[x] = h[x] = 0;
    vector<int> seg;
    for(auto pp : G[x]) if(pp.fi != p) {
        calc(pp.fi, x, lim);
        f[x] += f[pp.fi];
        if(h[pp.fi] + pp.se >= lim) ++f[x];
        else seg.PB(h[pp.fi] + pp.se);
    }
    if(seg.size() == 0) return;
    sort(seg.begin(), seg.end());

    int af = 0, tail = seg.size()-1;
    for(int i = 0; i < tail; ++i) {
        if(seg[i] + seg[tail] >= lim)
            ++af, --tail;
    }

    int l = 0, r = seg.size()-1, pt = -1;
    while(l <= r) {
        int mid = (l+r) >> 1;
        tail = seg.size()-1;
        if(tail == mid) --tail;
        int tmp = 0;
        for(int i = 0; i < tail; ++i) {
            if(i == mid) continue;
            if(seg[i] + seg[tail] >= lim) {
                ++tmp, --tail;
                if(tail == mid) --tail;
            }
        }
        if(tmp == af) pt = mid, l = mid+1;
        else r = mid-1;
    }

    f[x] += af;
    if(pt != -1) h[x] = seg[pt];
    return;
}

int main() {
    ios::sync_with_stdio(0);
    cin >> n >> m;
    for(int i = 1, u,v,w; i < n; ++i) {
        cin >> u >> v >> w;
        G[u].PB(pair<int,int>(v,w));
        G[v].PB(pair<int,int>(u,w));
    }

    int l = 1, r = 1e9, ans = 1e9 + 7;
    while(l <= r) {
        int mid = (l+r) >> 1;
        calc(1, 0, mid);
        if(f[1] >= m) ans = mid, l = mid+1;
        else r = mid-1;
    }
    cout << ans << "\n";
    return 0;
}
