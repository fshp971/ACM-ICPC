#include<iostream>
#include<algorithm>
#include<vector>
#include<algorithm>

using namespace std;

typedef long long LL;

const int maxn = 5e4, maxk = 16;
const LL INF = 1e14;

int n, m;
vector<pair<int,int>> G[maxn+5];
vector<int> ini(maxn+5), vis(maxn+5);
vector<pair<int,int>> rts;

vector<vector<int>> st(maxn+5, vector<int>(maxk+5));
vector<vector<LL>> dis(maxn+5, vector<LL>(maxk+5));

int tpb;
vector<LL> rem(maxn+5), buf(maxn+5);

void dfs1(int x, int p, int w) {
    st[x][0] = p, dis[x][0] = w;
    for(int k = 0; st[x][k]; ++k) {
        st[x][k+1] = st[ st[x][k] ][k];
        dis[x][k+1] = dis[x][k] + dis[ st[x][k] ][k];
    }
    for(auto pp : G[x]) if(pp.first != p) {
        dfs1(pp.first, x, pp.second);
        if(x == 1) rts.push_back(pair<int,int>(pp.second, pp.first));
    }
}

void up(int x, LL &lim) {
    if(x == 1) { buf[++tpb] = lim; return; }
    LL r = lim;
    for(int k = maxk; k >= 0; --k) {
        if(st[x][k] <= 1) continue;
        if(dis[x][k] > r) continue;
        r -= dis[x][k], x = st[x][k];
    }
    if(st[x][0] != 1) vis[x] = 1;
    else {
        if(rem[x] == -1) rem[x] = r;
        else {
            if(r < rem[x]) swap(r, rem[x]);
            if(r > dis[x][0]) buf[++tpb] = r - dis[x][0];
        }
    }
}

bool dfs2(int x, int p) {
    if(vis[x]) return true;
    bool fg = 0;
    for(auto pp : G[x]) if(pp.first != p) {
        if(dfs2(pp.first, x) == false && x != 1)
            return false;
        fg = 1;
    }
    return vis[x] = fg;
}

bool check(LL lim) {
    tpb = 0;
    for(int i = 1; i <= n; ++i) vis[i] = 0, rem[i] = -1;
    for(int i = 1; i <= m; ++i) up(ini[i], lim);

    dfs2(1, 0);
    for(auto pp : rts) if(vis[pp.second]) {
        if(rem[pp.second] > pp.first)
            buf[++tpb] = rem[pp.second] - pp.first;
    }

    sort(buf.begin()+1, buf.begin()+(tpb+1));

    int pt = 1;
    for(auto pp : rts) if(!vis[pp.second] && rem[pp.second]!=-1) {
        while(pt <= tpb && buf[pt] < pp.first) ++pt;
        if(pt > tpb) break;
        if(buf[pt] < rem[pp.second] - pp.first)
            buf[pt] = rem[pp.second] - pp.first;
        ++pt;
    }

    sort(buf.begin()+1, buf.begin()+(tpb+1));

    pt = 1;
    for(auto pp : rts) if(!vis[pp.second] && rem[pp.second]==-1) {
        while(pt <= tpb && buf[pt] < pp.first) ++pt;
        if(pt > tpb) return false;
        ++pt;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin >> n;
    for(int i = 1, u,v,w; i < n; ++i) {
        cin >> u >> v >> w;
        G[u].push_back(pair<int,int>(v,w));
        G[v].push_back(pair<int,int>(u,w));
    }
    cin >> m;
    for(int i = 1; i <= m; ++i) cin >> ini[i];

    dfs1(1, 0, 0);
    if(rts.size() > m) { cout << "-1\n"; return 0; }
    sort(rts.begin(), rts.end());

    LL l = 0, r = INF, ans = r+1;
    while(l <= r) {
        LL mid = (l+r) >> 1;
        if(check(mid)) ans = mid, r = mid-1;
        else l = mid+1;
    }
    cout << ans << "\n";

    return 0;
}
