#include<bits/stdc++.h>

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

const int maxn = 1e5;
const int INF = 1 << 30;

LL Gcd(LL a, LL b) { return b ? Gcd(b,a%b) : a; }

int n, dist[maxn + 5];
vector<pii> G[maxn + 5];
string str[maxn + 5];

int num[15], wi[15];

priority_queue<pii> que;

void Dij(int n, int u) {
    FOR(i,0,n) dist[i] = INF;
    int x = u % n;
    dist[x] = wi[u], str[x].PB(u + '0');
    que.push( MP(-dist[x], x) );
    while(!que.empty()) {
        pii tmp = que.top(); que.pop();
        if(-tmp.fi != dist[tmp.se]) continue;
        x = tmp.se;
        string s = str[x];
        for(auto it : G[x]) {
            s.PB(it.se + '0');
            int d = dist[x] + wi[it.se];
            if(d < dist[it.fi])
                dist[it.fi] = d, str[it.fi] = s, que.push( MP(-dist[it.fi], it.fi) );
            else if(d == dist[it.fi] && s < str[it.fi])
                str[it.fi] = s, que.push( MP(-dist[it.fi], it.fi) );
            s.pop_back();
        }
    }
}

int main() {
    int a, b, c, u, v;
    scanf("%d%d%d", &a, &b, &c);
    int g = Gcd(a,b);
    REP(i,1,c) scanf("%d", num + i);
    REP(i,1,c) scanf("%d", wi + (num[i]));
    scanf("%d%d", &u, &v);
    for(int i = 0; i < g; ++i) {
        for(int k = 0; k <= 9; ++k) {
            if(!wi[k]) continue;
            G[i].PB( MP((i * 10 + k) % g, k) );
        }
    }
    Dij(g,u);
    int val = INF;
    string ans = "";
    for(int i = 0; i < g; ++i) {
        if(dist[i] == INF) continue;
        int rem = i;
        if(i != 0 || str[i][str[i].size()-1] != v + '0')
            str[i].PB(v + '0'), dist[i] += wi[v], rem = (i * 10 + v) % g;
        if(rem) continue;
        if(dist[i] < val) val = dist[i], ans = str[i];
        else if(dist[i] == val && str[i] < ans) ans = str[i];
    }
    if(val == INF) puts("-1");
    else printf("%s\n", ans.c_str());
    return 0;
}
