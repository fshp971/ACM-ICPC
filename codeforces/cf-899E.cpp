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

const int maxn = 4e5;

struct Node {
    int ps, len, id;
    Node(): ps(0), len(0), id(0) {}
    Node(int _ps, int _len, int _id) { ps = _ps, len = _len; id = _id; }
    bool operator<(const Node &a) const {
        if(len != a.len) return len < a.len;
        return ps > a.ps;
    }
};

priority_queue<Node> que;
bool dead[maxn + 5];
int n, tot = 0;
int val[maxn + 5], nex[maxn + 5], pre[maxn + 5], cnt[maxn + 5], nid[maxn + 5];

int main() {
    scanf("%d", &n);
    REP(i,1,n) scanf("%d", val + i);
    for(int i = 1; i <= n; ++i) pre[i] = i-1, nex[i] = i+1;
    dead[0] = true;
    nid[0] = nid[n+1] = 0;
    for(int i = 1; i <= n; ++i) {
        int k = i;
        cnt[i] = 1;
        while(k+1 <= n && val[k+1] == val[i]) nid[k+1] = 0, ++k, ++cnt[i];
        nex[i] = nex[k], pre[nex[k]] = i;
        nid[i] = ++tot;
        que.push( Node(i, cnt[i], nid[i]) );
        i = k;
    }
    int ans = 0;
    while(!que.empty()) {
        Node tmp = que.top(); que.pop();
        if(dead[tmp.id]) continue;
        dead[tmp.id] = 1, ++ans;
        int x = tmp.ps;
        if(!dead[nid[nex[x]]] && !dead[nid[pre[x]]] && val[nex[x]] == val[pre[x]]) {
            dead[nid[nex[x]]] = 1, dead[nid[pre[x]]] = 1;
            nid[pre[x]] = ++tot;
            nex[pre[x]] = nex[nex[x]], pre[nex[nex[x]]] = pre[x];
            cnt[pre[x]] += cnt[nex[x]];
            que.push( Node(pre[x], cnt[pre[x]], nid[pre[x]]) );
        }
        else {
            pre[nex[x]] = pre[x], nex[pre[x]] = nex[x];
        }
    }
    printf("%d\n", ans);
    return 0;
}
