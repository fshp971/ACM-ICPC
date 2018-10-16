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
 
const int maxn = 1e6;
 
template<class T>
inline void Read(T &x) {
    char c = getchar();
    while(c<'0' || c>'9') c = getchar();
    for(x = 0; '0'<=c&&c<='9'; x = x*10+c-'0', c = getchar());
}
 
struct Node {
    int x[2];
    int mi[2], mx[2];
    int l, r, sz;
} tr[maxn+5];
int tot, D, root, ans, num[maxn+5];
bool cmp(const int &a, const int &b) { return tr[a].x[D] < tr[b].x[D]; }
 
int n, m;
 
void PushUp(int x) {
    int l = tr[x].l, r = tr[x].r;
    tr[x].sz = tr[l].sz + tr[r].sz + 1;
    REP(i,0,1) tr[x].mi[i] = tr[x].mx[i] = tr[x].x[i];
    REP(i,0,1) {
        if(l) {
            tr[x].mi[i] = min(tr[x].mi[i], tr[l].mi[i]);
            tr[x].mx[i] = max(tr[x].mx[i], tr[l].mx[i]);
        }
        if(r) {
            tr[x].mi[i] = min(tr[x].mi[i], tr[r].mi[i]);
            tr[x].mx[i] = max(tr[x].mx[i], tr[r].mx[i]);
        }
    }
}
 
int Build(int l, int r, int d) {
    int mid = (l+r) >> 1;
    D = d;
    nth_element(num+l, num+mid, num+r+1, cmp);
    int x = num[mid];
    tr[x].l = tr[x].r = 0;
    tr[x].mi[0] = tr[x].mx[0] = tr[x].x[0];
    tr[x].mi[1] = tr[x].mx[1] = tr[x].x[1];
    if(l<=mid-1) tr[x].l = Build(l, mid-1, d^1);
    if(mid+1<=r) tr[x].r = Build(mid+1, r, d^1);
    PushUp(x);
    return x;
}
 
void Insert(int &x, Node &pt, int d) {
    if(x == 0) {
        x = ++tot, tr[x].sz = 1;
        REP(i,0,1) tr[x].x[i] = tr[x].mi[i] = tr[x].mx[i] = pt.x[i];
        return;
    }
    if(pt.x[d] < tr[x].x[d]) {
        Insert(tr[x].l, pt, d^1);
        PushUp(x);
    }
    else {
        Insert(tr[x].r, pt, d^1);
        PushUp(x);
    }
}
 
void Query(int x, Node &pt) {
    int tmp = 0;
    REP(i,0,1) tmp += abs(pt.x[i] - tr[x].x[i]);
    ans = min(ans, tmp);
    int l = tr[x].l, r = tr[x].r;
    int lc = 0, rc = 0;
    if(l) REP(i,0,1) lc += max(0,tr[l].mi[i]-pt.x[i]) + max(0,pt.x[i]-tr[l].mx[i]);
    if(r) REP(i,0,1) rc += max(0,tr[r].mi[i]-pt.x[i]) + max(0,pt.x[i]-tr[r].mx[i]);
    if(lc<rc) {
        if(l && lc<ans) Query(l, pt);
        if(r && rc<ans) Query(r, pt);
    }
    else {
        if(r && rc<ans) Query(r, pt);
        if(l && lc<ans) Query(l, pt);
    }
}
 
int main() {
    //scanf("%d%d", &n, &m);
    Read(n); Read(m);
    for(int i = 1, x,y; i <= n; ++i) {
        //scanf("%d%d", &x, &y);
        Read(x); Read(y);
        tr[i].x[0] = x, tr[i].x[1] = y;
        num[i] = i;
    }
    tot = n;
    root = Build(1, n, 0);
    while(m--) {
        int o, x, y;
        //scanf("%d%d%d", &o, &x, &y);
        Read(o); Read(x); Read(y);
        Node nd; nd.x[0] = x, nd.x[1] = y;
        if(o == 1) Insert(root, nd, 0);
        else {
            ans = 1LL << 30;
            Query(root, nd);
            printf("%d\n", ans);
        }
    }
    return 0;
}
