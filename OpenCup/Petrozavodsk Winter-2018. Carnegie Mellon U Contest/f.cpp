#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cassert>
#include<cassert>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<queue>
#include<utility>
#include<bitset>
#include<complex>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>

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

const int maxn = 2e6;

struct Node {
    int ps, fg, l, r, id;
    Node() {}
    Node(int _ps, int _fg, int _l, int _r = 0, int _id = 0) {
        ps = _ps, fg = _fg, l = _l, r = _r, id = _id;
    }
    bool operator<(const Node &a) const {
        if(ps != a.ps) return ps < a.ps;
        return abs(fg) < abs(a.fg);
    }
};

int bit[maxn + 5];
void Add(int x, int v) { for(;x<=maxn;x+=x&(-x)) bit[x]+=v; }
int Sum(int x) { int r=0; for(;x;x-=x&(-x)) r+=bit[x]; return r; }

int ans[maxn + 5];
vector<Node> vec;

int main() {
    //freopen("in.txt", "r", stdin);
    int n, m;
    scanf("%d", &n);
    for(int i = 1, x, y; i <= n; ++i) {
        scanf("%d%d", &x, &y);
        vec.PB( Node(x-y,0,x+y) );
    }
    scanf("%d", &m);
    for(int i = 1, x, y, d; i <= m; ++i) {
        scanf("%d%d%d", &x, &y, &d);
        int l = max(x+y-d, 1);
        int r = min(x+y+d, maxn);
        vec.PB( Node(x-y-d-1, -1, l, r, i) ); 
        vec.PB( Node(x-y+d, 1, l, r, i) ); 
    }
    sort(vec.begin(), vec.end());
    for(auto it : vec) {
        if(it.fg == 0) Add(it.l, 1);
        else
            ans[it.id] += it.fg * (Sum(it.r) - Sum(it.l-1));
    }
    REP(i,1,m) printf("%d\n", ans[i]);
    return 0;
}
