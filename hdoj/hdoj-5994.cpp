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
    int l, r, c, x[2], id, mx[2], mi[2], mic, lz;
} tr[maxn+5];
int D;
int num[maxn+5];

bool cmp(const int &a, const int &b) { return tr[a].x[D] < tr[b].x[D]; }

int Build(int l, int r, int d) {
    int mid = (l+r) >> 1;
    D = d;
    nth_element(num+l, num+mid, num+r+1, cmp);
    int x = num[mid];
    tr[x].c = tr[x].mic = 1 << 30;
    tr[x].lz = 0;
    tr[x].mi[0] = tr[x].mx[0] = tr[x].x[0];
    tr[x].mi[1] = tr[x].mx[1] = tr[x].x[1];
    tr[x].l = tr[x].r = 0;
    if(l<mid) {
        tr[x].l = Build(l, mid-1, d^1);
        REP(i,0,1) {
            tr[x].mx[i] = max(tr[x].mx[i], tr[tr[x].l].mx[i]);
            tr[x].mi[i] = min(tr[x].mi[i], tr[tr[x].l].mi[i]);
        }
    }
    if(mid<r) {
        tr[x].r = Build(mid+1, r, d^1);
        REP(i,0,1) {
            tr[x].mx[i] = max(tr[x].mx[i], tr[tr[x].r].mx[i]);
            tr[x].mi[i] = min(tr[x].mi[i], tr[tr[x].r].mi[i]);
        }
    }
    return x;
}

void PushUp(int x) {
    int l = tr[x].l, r = tr[x].r;
    tr[x].mic = tr[x].c;
    if(l) tr[x].mic = min(tr[x].mic, tr[l].mic);
    if(r) tr[x].mic = min(tr[x].mic, tr[r].mic);
}

void PushDown(int x) {
    int l = tr[x].l, r = tr[x].r;
    if(l) tr[l].c -= tr[x].lz, tr[l].mic -= tr[x].lz, tr[l].lz += tr[x].lz;
    if(r) tr[r].c -= tr[x].lz, tr[r].mic -= tr[x].lz, tr[r].lz += tr[x].lz;
    tr[x].lz = 0;
}

inline bool In(int x, Node &nd) {
    if(nd.x[0]<tr[x].mi[0] || nd.x[0]>tr[x].mx[0]) return false;
    if(nd.x[1]<tr[x].mi[1] || nd.x[1]>tr[x].mx[1]) return false;
    return true;
}

bool Upd(int x, Node &nd) {
    PushDown(x);
    if(tr[x].id == nd.id) {
        tr[x].c = tr[x].mic = nd.c;
        if(tr[x].l) tr[x].mic = min(tr[x].mic, tr[tr[x].l].mic);
        if(tr[x].r) tr[x].mic = min(tr[x].mic, tr[tr[x].r].mic);
        return true;
    }
    int l = tr[x].l, r = tr[x].r;
    bool ret = 0;
    if(l && In(l,nd) && Upd(l,nd)) ret = 1;
    if(!ret) {
        if(r && In(r,nd) && Upd(r,nd)) ret = 1;
    }
    if(ret) PushUp(x);
    return ret;
}

void Add(int x, int a) {
    if(tr[x].mx[0]<=a && a<=tr[x].mi[1]) {
        --tr[x].c, --tr[x].mic, ++tr[x].lz;
        return;
    }
    PushDown(x);
    if(tr[x].x[0]<=a && a<=tr[x].x[1]) --tr[x].c;
    int l = tr[x].l, r = tr[x].r;
    if(l && tr[l].mi[0]<=a && a<=tr[l].mx[1]) Add(l, a);
    if(r && tr[r].mi[0]<=a && a<=tr[r].mx[1]) Add(r, a);
    PushUp(x);
}

void Query(int x, vector<int> &vec) {
    PushDown(x);
    if(tr[x].c == 0) vec.PB(tr[x].id), tr[x].c = 1<<30;
    int l = tr[x].l, r = tr[x].r;
    if(l && tr[l].mic==0) Query(l, vec);
    if(r && tr[r].mic==0) Query(r, vec);
    PushUp(x);
}

int m, n;
int oo[maxn+5], xx[maxn+5], yy[maxn+5], cc[maxn+5], aa[maxn+5];
vector<int> ans;
int main() {
    int __; scanf("%d", &__);
    char ord[10];
    for(int _ = 1; _ <= __; ++_) {
        scanf("%d%d", &n, &m);
        int tot = 0;
        REP(i,1,n) {
            scanf("%s", ord);
            if(ord[0] == 'C') {
                oo[i] = 1;
                scanf("%d%d%d", xx+i, yy+i, cc+i);
                ++tot, num[tot] = tot;
                tr[tot].x[0] = xx[i], tr[tot].x[1] = yy[i], tr[tot].id = i;
            }
            else {
                oo[i] = 2;
                scanf("%d", aa+i);
            }
        }
        printf("Case #%d:\n", _);
        if(tot == 0) continue;
        int root = Build(1, tot, 0);
        int cnt = 0;
        REP(i,1,n) {
            if(oo[i] == 1) {
                Node nd;
                nd.x[0] = xx[i], nd.x[1] = yy[i];
                nd.c = cc[i], nd.id = i;
                Upd(root, nd);
            }
            else
                Add(root, aa[i]^cnt);
            if(tr[root].mic == 0) {
                ans.clear();
                Query(root, ans);
                sort(ans.begin(), ans.end());
                printf("%d", i);
                for(auto u : ans) printf(" %d", u), cnt ^= u;
                puts("");
            }
        }
    }
    return 0;
}
