#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
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
#include<stack>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define PER(i,a,b) for(int i=a; i>=b; --i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 2e5;

struct Node {
    int id, fg, x1, x2, y;
    Node() {}
    Node(int _id, int _fg, int _x1, int _x2, int _y) : id(_id), fg(_fg), x1(_x1), x2(_x2), y(_y) {}
    bool operator<(const Node &a) const {
        return y<a.y;
    }
};

int tr[maxn+5], vi[maxn+5], T;
int xi[maxn+5], m = 0;
void Add(int x, int d) {
    for(;x<=m;x+=x&(-x)) {
        if(vi[x]!=T) vi[x]=T, tr[x]=0;
        tr[x]+=d;
    }
}
int Sum(int x) { int r=0; for(;x;x-=x&(-x)) if(vi[x]==T) r+=tr[x]; return r; }

int n;
LL ans[maxn+5];
vector<Node> poi, rec;

void Solve(int l, int r, vector<Node> &pp, vector<Node> &gg) {
    if(l==r) return;
    int mid = (l+r)>>1;
    vector<Node> p1, p2, g1, g2;
    for(auto x : pp) {
        if(x.id<=mid) p1.PB(x);
        else p2.PB(x);
    }
    for(auto x : gg) {
        if(x.id<=mid) g1.PB(x);
        else g2.PB(x);
    }
    Solve(l, mid, p1, g1);
    Solve(mid+1, r, p2, g2);

    int i = 0, k = 0;
    ++T;
    while(i<p1.size() && k<g2.size()) {
        if(p1[i].y <= g2[k].y) {
            Add(p1[i].x1, 1);
            ++i;
        }
        else {
            ans[g2[k].id] += (Sum(g2[k].x2) - Sum(g2[k].x1-1)) * g2[k].fg;
            ++k;
        }
    }
    while(k<g2.size()) {
        ans[g2[k].id] += (Sum(g2[k].x2) - Sum(g2[k].x1-1)) * g2[k].fg;
        ++k;
    }

    i = int(g1.size())-1, k = int(p2.size())-1, ++T;
    while(i>=0 && k>=0) {
        if(g1[i].y >= p2[k].y) {
            Add(g1[i].x1, g1[i].fg);
            Add(g1[i].x2+1, -g1[i].fg);
            --i;
        }
        else {
            ans[p2[k].id] += Sum(p2[k].x1);
            --k;
        }
    }
    while(k>=0) {
        ans[p2[k].id] += Sum(p2[k].x1);
        --k;
    }
}

int main() {
    scanf("%d", &n);
    int o, x1, y1, x2, y2;
    REP(i,1,n) {
        scanf("%d%d%d", &o, &x1, &y1);
        xi[++m] = x1;
        if(o==1)
            poi.PB( Node(i,1,x1,x1,y1) );
        else {
            scanf("%d%d", &x2, &y2);
            rec.PB( Node(i,-1,x1,x2,y1-1) );
            rec.PB( Node(i,1,x1,x2,y2) ); 
            xi[++m] = x2;
        }
    }
    sort(xi+1, xi+1+m);
    sort(poi.begin(), poi.end());
    sort(rec.begin(), rec.end());
    m = unique(xi+1, xi+1+m) - xi - 1;
    for(int i = 0; i < poi.size(); ++i) {
        poi[i].x1 = lower_bound(xi+1, xi+1+m, poi[i].x1) - xi;
        poi[i].x2 = lower_bound(xi+1, xi+1+m, poi[i].x2) - xi;
    }
    for(int i = 0; i < rec.size(); ++i) {
        rec[i].x1 = lower_bound(xi+1, xi+1+m, rec[i].x1) - xi;
        rec[i].x2 = lower_bound(xi+1, xi+1+m, rec[i].x2) - xi;
    }
    Solve(1,n, poi, rec);
    REP(i,1,n) {
        ans[i] += ans[i-1];
        printf("%lld\n", ans[i]);
    }
    return 0;
}
