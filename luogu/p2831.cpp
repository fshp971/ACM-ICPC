#include<cassert>
#include<iostream>
#include<iomanip>
#include<algorithm>

using namespace std;

typedef long long LL;

const int maxn = 18, maxnode = 1<<maxn;

int n, T, top, go[maxn*maxn+5], f[maxnode+5], vis[maxnode+5];
double xi[maxn+5], yi[maxn+5];

int dfs(int msk) {
    if(vis[msk] == T) return f[msk];
    vis[msk] = T;
    if(msk+1 == (1<<n)) return f[msk] = 0;
    f[msk] = n - __builtin_popcount(msk);
    for(int i = 1; i <= top; ++i) {
        if((msk|go[i]) == msk) continue;
        f[msk] = min(f[msk], dfs(msk|go[i])+1);
    }
    return f[msk];
}

int main() {
    ios::sync_with_stdio(0);
    int _, __; cin >> _;
    while(_--) {
        cin >> n >> __;
        double tx, ty;
        for(int i = 0; i < n; ++i) {
            cin >> xi[i] >> yi[i];
        }
        top = 0;
        for(int i = 0; i < n; ++i) {
            for(int k = i+1; k < n; ++k) {
                if(xi[i] == xi[k]) continue;
                double tmp = xi[i] * xi[k] * (xi[i]-xi[k]);
                double tmpa = (yi[i]*xi[k] - yi[k]*xi[i]) / tmp;
                double tmpb = (yi[k]*xi[i]*xi[i] - yi[i]*xi[k]*xi[k]) / tmp;
                if(tmpa >= 0) continue;
                int msk = 0;
                for(int j = 0; j < n; ++j) {
                    if(abs(tmpa*xi[j]*xi[j] + tmpb*xi[j] - yi[j]) < 1e-8)
                        msk |= (1<<j);
                }
                go[++top] = msk;
            }
        }
        ++T;
        cout << dfs(0) << "\n";
    }
    return 0;
}
