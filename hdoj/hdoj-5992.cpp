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
    int x[2], mi[2], mx[2], mic, c, id, l, r;
} tr[maxn+5];
int D, num[maxn+5];

bool cmp(const int &a, const int &b) { return tr[a].x[D] < tr[b].x[D]; }

int Build(int l, int r, int d) {
    int mid = (l+r) >> 1;
    D = d;
    nth_element(num+l, num+mid, num+r+1, cmp);
    int x = num[mid];
    tr[x].mi[0] = tr[x].mx[0] = tr[x].x[0];
    tr[x].mi[1] = tr[x].mx[1] = tr[x].x[1];
    tr[x].mic = tr[x].c;
    tr[x].l = tr[x].r = 0;
    if(l<mid) {
        tr[x].l = Build(l, mid-1, d^1);
        REP(i,0,1) {
            tr[x].mi[i] = min(tr[x].mi[i], tr[tr[x].l].mi[i]);
            tr[x].mx[i] = max(tr[x].mx[i], tr[tr[x].l].mx[i]);
        }
        tr[x].mic = min(tr[x].mic, tr[tr[x].l].mic);
    }
    if(mid<r) {
        tr[x].r = Build(mid+1, r, d^1);
        REP(i,0,1) {
            tr[x].mi[i] = min(tr[x].mi[i], tr[tr[x].r].mi[i]);
            tr[x].mx[i] = max(tr[x].mx[i], tr[tr[x].r].mx[i]);
        }
        tr[x].mic = min(tr[x].mic, tr[tr[x].r].mic);
    }
    return x;
}

int n, m;
LL dist;
int pid;
inline LL sqr(LL x) { return x*x; }
void Query(int x, Node &pt) {
    if(tr[x].c <= pt.c) {
        LL tmp = 0;
        REP(i,0,1) tmp += sqr(tr[x].x[i]-pt.x[i]);
        if(tmp < dist) dist = tmp, pid = tr[x].id;
        else if(tmp == dist && tr[x].id < pid) pid = tr[x].id;
    }
    LL lc = 0, rc = 0;
    int l = tr[x].l, r = tr[x].r;
    if(l) REP(i,0,1) lc = max(lc, (LL)max( tr[l].mi[i]-pt.x[i], pt.x[i]-tr[l].mx[i] ) );
    if(r) REP(i,0,1) rc = max(rc, (LL)max( tr[r].mi[i]-pt.x[i], pt.x[i]-tr[r].mx[i] ) );
    lc = sqr(lc), rc = sqr(rc);
    if(lc < rc) {
        if(l && tr[l].mic<=pt.c && lc<=dist) Query(l, pt);
        if(r && tr[r].mic<=pt.c && rc<=dist) Query(r, pt);
    }
    else {
        if(r && tr[r].mic<=pt.c && rc<=dist) Query(r, pt);
        if(l && tr[l].mic<=pt.c && lc<=dist) Query(l, pt);
    }
}

int xx[maxn+5], yy[maxn+5], cc[maxn+5];

int main() {
    int _; scanf("%d", &_);
    while(_--) {
        scanf("%d%d", &n, &m);
        REP(i,1,n) {
            scanf("%d%d%d", xx+i, yy+i, cc+i);
            tr[i].x[0] = xx[i], tr[i].x[1] = yy[i];
            tr[i].c = cc[i], tr[i].id = i;
            num[i] = i;
        }
        int root = Build(1,n,0);
        while(m--) {
            int x, y, c; scanf("%d%d%d", &x, &y, &c);
            Node nd;
            nd.x[0] = x, nd.x[1] = y, nd.c = c;
            dist = 1LL << 60, pid = 0;
            Query(root, nd);
            printf("%d %d %d\n", xx[pid], yy[pid], cc[pid]);
        }
    }
    return 0;
}
