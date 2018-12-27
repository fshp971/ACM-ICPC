#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define PER(i,a,b) for(int i = a; i >= b; --i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef double DB;

const int maxn = 2e5;

int n, q, seg[maxn+5];
char ss[maxn+5];
int tr[3][maxn+5];
set<int> Set[3];

// 0: rock;
// 1: paper;
// 2: scissor;
void Add(int *a, int x, int d) { for(;x<=n;x+=x&(-x)) a[x]+=d; }
int Sum(int *a, int x) { int r=0; for(;x;x-=x&(-x)) r+=a[x]; return r; }

int c1[3], c2[3];
pair<int,int> sta[20];

inline bool Chk(int v) {
    if(c1[(v+1)%3] && !c1[(v+2)%3]) return false;
    if(c2[(v+1)%3] && !c2[(v+2)%3]) return false;
    return true;
}

int Calc() {
    int tot = 0;
    mem(c1,0); mem(c2,0);
    REP(i,0,2) if(Set[i].size()) {
        sta[++tot] = pair<int,int>(*Set[i].begin(),i), ++c2[i];
        if(Set[i].size()>1)
            sta[++tot] = pair<int,int>(*(--Set[i].end()),i), ++c2[i];
    }
    sort(sta+1, sta+1+tot);
    int ans = 0;
    for(int i = 1; i <= tot; ++i) {
        ++c1[sta[i].se], --c2[sta[i].se];
        if(Chk(sta[i].se)) ++ans;
        if(i+1<=tot && sta[i].fi+1<=sta[i+1].fi-1) {
            REP(k,0,2) if(Chk(k)) {
                ans += Sum(tr[k], sta[i+1].fi-1) - Sum(tr[k], sta[i].fi);
            }
        }
    }
    return ans;
}

int main() {
    scanf("%d%d", &n, &q);
    scanf("%s", ss+1);
    REP(i,1,n) seg[i] = ss[i]=='R' ? 0 : (ss[i]=='P'?1:2);
    REP(i,0,2) {
        REP(k,1,n) if(seg[k]==i) {
            Add(tr[i], k, 1);
            Set[i].insert(k);
        }
    }
    printf("%d\n", Calc());
    char oo[10];
    while(q--) {
        int x;
        scanf("%d%s", &x, oo);
        Set[seg[x]].erase(x);
        Add(tr[seg[x]], x, -1);
        seg[x] = oo[0]=='R' ? 0 : (oo[0]=='P'?1:2);
        Set[seg[x]].insert(x);
        Add(tr[seg[x]], x, 1);
        printf("%d\n", Calc());
    }
    return 0;
}
