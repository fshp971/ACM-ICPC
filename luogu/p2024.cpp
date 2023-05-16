#include<iostream>

using namespace std;

const int maxn = 3 * 5e4;

int n, kk, fa[maxn+5], pre[maxn+5], nex[maxn+5];
int find(int x) { return fa[x]==x ? x : fa[x] = find(fa[x]); }

inline int self(int &x) { return x*3-2; }
inline int prev(int &x) { return x*3-1; }
inline int next(int &x) { return x*3; }

int unite1(int x, int y) {
    if(find(self(x))==find(prev(y)) || find(self(x))==find(next(y))) return 1;
    if(find(prev(x))==find(self(y)) || find(prev(x))==find(next(y))) return 1;
    if(find(next(x))==find(prev(y)) || find(next(x))==find(self(y))) return 1;
    fa[find(self(x))] = find(self(y));
    fa[find(prev(x))] = find(prev(y));
    fa[find(next(x))] = find(next(y));
    return 0;
}

int unite2(int x, int y) {
    if(find(self(x))==find(self(y)) || find(self(x))==find(next(y))) return 1;
    if(find(prev(x))==find(prev(y)) || find(prev(x))==find(self(y))) return 1;
    if(find(next(x))==find(next(y)) || find(next(x))==find(prev(y))) return 1;
    fa[find(self(x))] = find(prev(y));
    fa[find(prev(x))] = find(next(y));
    fa[find(next(x))] = find(self(y));
    return 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin >> n >> kk;
    for(int i = 1; i <= n*3; ++i) fa[i] = i;
    int ans = 0;
    while(kk--) {
        int o, x, y;
        cin >> o >> x >> y;
        if(x>n || y>n) { ++ans; continue; }
        if(o == 1)
            ans += unite1(x, y);
        else {
            if(x == y) { ++ans; continue; }
            ans += unite2(x, y);
        }
    }
    cout << ans << "\n";
    return 0;
}
