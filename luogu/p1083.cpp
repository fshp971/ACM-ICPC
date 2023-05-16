#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>

using namespace std;
typedef long long LL;

const int maxn = 1e6;

int n, m;
vector<int> ri(maxn+5), di(maxn+5), si(maxn+5), ti(maxn+5);
vector<LL> delta(maxn+5);

bool check(int x) {
    for(int i = 1; i <= n+1; ++i) delta[i] = 0;
    for(int i = 1; i <= x; ++i) {
        delta[si[i]] += di[i];
        delta[ti[i]+1] -= di[i];
    }
    LL now = 0;
    for(int i = 1; i <= n; ++i) {
        now += delta[i];
        if(now > ri[i]) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin >> n >> m;
    for(int i = 1; i <= n; ++i)
        cin >> ri[i];
    for(int i = 1; i <= m; ++i)
        cin >> di[i] >> si[i] >> ti[i];
    int ans = 0, l = 1, r = m;
    while(l <= r) {
        int mid = (l+r) >> 1;
        if(check(mid)) ans = mid, l = mid+1;
        else r = mid-1;
    }
    if(ans == m) cout << "0\n";
    else cout << "-1\n" << ans+1 << "\n";
    return 0;
}
