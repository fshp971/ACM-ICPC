#include<bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define FOR(i,a,b) for(int i = a; i < b; ++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
#define PB push_back
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 20;
const int maxnode = maxn * 100, c_sz = 401;

int n;

struct Tire {
    int nx[maxnode + 5][c_sz], tot;
    int sta[maxn + 5];
    void Init() {
        tot = 0;
        mem(nx[tot], 0);
    }
    void Insert(int *a, int len) {
        int u = 0;
        for(int i = 1; i <= len; ++i) {
            if(!nx[u][a[i]])
                ++tot, nx[u][a[i]] = tot, mem(nx[tot], 0);
            u = nx[u][a[i]];
        }
    }
    void dfs(int u, int top) {
        if(top >= n) {
            for(int i = 1; i < n; ++i) {
                if(i > 1) printf(" ");
                printf("%d", sta[i]);
            }
            printf("\n");
            return;
        }
        for(int i = 1; i < c_sz; ++i)
            if(nx[u][i]) {
                sta[top] = i;
                dfs(nx[u][i], top + 1);
            }
    }
} tree;

int sta1[maxn + 5], tot1;
int sta2[maxn + 5], tot2;

multiset<int> E;

void RB(vector<int> &seg) {
    for(auto it : seg) E.insert(-it);
}

bool GF(int pos, vector<int> &seg) {
    int fg = 1;
    for(int i = 1; i <= tot1; ++i) {
        auto it = E.find(-abs(pos - sta1[i]));
        if(it == E.end()) { fg = 0; break; }
        seg.PB(-(*it)), E.erase(it);
    }
    if(!fg) return false;
    for(int i = 1; i <= tot2; ++i) {
        auto it = E.find(-abs(pos - sta2[i]));
        if(it == E.end()) { fg = 0; break; }
        seg.PB(-(*it)), E.erase(it);
    }
    return fg != 0;
}

int arr[maxn + 5];
void dfs(int pt) {
    if(pt > n) {
        int len = 0;
        for(int i = 2; i <= tot1; ++i)
            arr[++len] = sta1[i] - sta1[i-1];
        arr[++len] = sta2[tot2] - sta1[tot1];
        for(int i = tot2 - 1; i >= 1; --i)
            arr[++len] = sta2[i] - sta2[i+1];
        tree.Insert(arr, len);
        return;
    }
    vector<int> seg;
    int mx = -(*E.begin());
    int pos = sta1[1] + mx;
    if(GF(pos, seg)) {
        sta2[++tot2] = pos;
        dfs(pt + 1);
        --tot2;
    }
    RB(seg);

    seg.clear();
    pos = sta2[1] - mx;
    if(GF(pos, seg)) {
        sta1[++tot1] = pos;
        dfs(pt + 1);
        --tot1;
    }
    RB(seg);
}

int main() {
    freopen("C.in", "r", stdin);
    int u;
    while(scanf("%d", &n), n) {
        E.clear();
        for(int i = 1; i <= ((n*(n-1))>>1); ++i)
            scanf("%d", &u), E.insert(-u);
        sta1[tot1 = 1] = 0, sta2[tot2 = 1] = -(*E.begin());
        E.erase(E.begin());
        tree.Init();
        dfs(3);
        tree.dfs(0, 1);
        printf("-----\n");
    }
    return 0;
}
