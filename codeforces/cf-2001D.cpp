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

int main() {
    ios::sync_with_stdio(0);
    int _; cin >> _;
    while(_--) {
        int n; cin >> n;
        vector<int> ai(n+5), vis(n+5, 0), las(n+5, 0);
        REP(i,1,n) {
            cin >> ai[i];
            las[ai[i]] = i;
        }
        int m = 0;
        priority_queue<pair<int,int>> q, mi, mx;
        REP(i,1,n) if(las[i])
            ++m, q.push(pair<int,int>(-las[i], i));
        vector<int> bi(m+5);
        for(int i = 1, pos = 0, odd = 1, lim = 0; i <= m; ++i, odd^=1) {
            while(vis[q.top().second]) q.pop();
            int lim2 = -q.top().first;
            while(lim+1 <= lim2) {
                ++lim;
                mi.push(pair<int,int>(-ai[lim], -lim));
                mx.push(pair<int,int>(ai[lim], -lim));
            }
            while(vis[-mi.top().first] || -mi.top().second<=pos) mi.pop();
            while(vis[mx.top().first] || -mx.top().second<=pos) mx.pop();
            pair<int,int> pp;
            if(odd) pp = mx.top();
            else pp = mi.top();
            bi[i] = ai[-pp.second];
            vis[bi[i]] = 1;
            pos = -pp.second;
        }
        cout << m << '\n';
        REP(i,1,m) cout << bi[i] << ((i==m) ? '\n' : ' ');
    }
    return 0;
}
