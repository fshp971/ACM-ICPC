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

const int maxn = 5000;

int n, m;
vector<vector<pair<int,int>>> G(maxn+5);
vector<int> ans(maxn+5), cur(maxn+5), vis(maxn+5);

void dfs(int x, int &top, int &flag, int &bad) {
    vis[x] = 1, cur[++top] = x;
    if(flag == 0) {
        if(ans[top] == 0) flag = 1;
        else if(ans[top] > x) flag = 1;
        else if(ans[top] < x) { flag = -1; return; }
    }
    for(auto &it : G[x]) if(!vis[it.fi] && it.se!=bad) {
        dfs(it.fi, top, flag, bad);
        if(flag == -1) return;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin >> n >> m;
    for(int i = 1, u,v; i <= m; ++i) {
        cin >> u >> v;
        G[u].PB(pair<int,int>(v,i));
        G[v].PB(pair<int,int>(u,i));
    }
    REP(i,1,n) if(G[i].size())
        sort(G[i].begin(), G[i].end());
    int top = 0, flag = 0, bad = 0;
    if(m == n-1) {
        dfs(1, top, flag, bad);
        REP(i,1,n) ans[i] = cur[i];
    }
    else {
        REP(i,1,m) {
            REP(k,1,n) vis[k] = 0;
            top = 0, flag = 0, bad = i;
            dfs(1, top, flag, bad);
            if(flag == 1 && top == n)
                REP(k,1,n) ans[k] = cur[k];
        }
    }
    REP(i,1,n) cout << ans[i] << ((i==n) ? '\n' : ' ');
    return 0;
}
