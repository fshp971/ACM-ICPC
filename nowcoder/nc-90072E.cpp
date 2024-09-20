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

const int maxn = 1e6;

int n;
vector<int> ok(maxn+5, 0);

int main() {
    ios::sync_with_stdio(0);
    cin >> n;
    for(int i = 1, x; i <= n; ++i)
        cin >> x, ok[x] = 1;
    for(int i = 1; i <= maxn; ++i) if(!ok[i])
        for(int k = i; k <= maxn; k += i)
            ok[k] = 0;
    int ans = 0;
    REP(i,1,maxn) ans += ok[i];
    cout << ans << '\n';
    return 0;
}
