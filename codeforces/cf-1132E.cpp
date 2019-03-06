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
#define lson (x<<1)
#define rson (x<<1|1)
#define mid ((l+r)>>1)
typedef long long LL;

const int maxn = 1e6;
const int maxnode = maxn<<2;

int n, kk, ai[maxn+5], st[maxn+5];
int in[maxn+5], out[maxn+5], DFN = 0;
int ans[maxn+5], m = 0;
vector<int> G[maxn+5];

int tr[maxnode+5], lz[maxnode+5];
void PushDown(int x) {
    tr[lson]+=lz[x], tr[rson]+=lz[x];
    lz[lson]+=lz[x], lz[rson]+=lz[x];
    lz[x] = 0;
}
void Inc(int x, int l, int r, int ll, int rr) {
    if(ll<=l && r<=rr) ++tr[x], ++lz[x];
    else {
        PushDown(x);
        if(ll<=mid) Inc(lson, l, mid, ll, rr);
        if(mid<rr) Inc(rson, mid+1, r, ll, rr);
        tr[x] = max(tr[lson], tr[rson]);
    }
}
void Reset(int x, int l, int r, int p) {
    if(l==r) lz[x] = 0, tr[x] = -(maxn+10);
    else {
        PushDown(x);
        if(p<=mid) Reset(lson, l, mid, p);
        else Reset(rson, mid+1, r, p);
        tr[x] = max(tr[lson], tr[rson]);
    }
}

void dfs(int x) {
    in[x] = ++DFN;
    for(auto y : G[x]) dfs(y);
    out[x] = DFN;
}

int main() {
    scanf("%d%d", &n, &kk);
    REP(i,1,n) scanf("%d", ai+i);
    {
        int top = 0;
        for(int i = n; i >= 1; --i) {
            while(top && ai[i]>=ai[st[top]]) --top;
            if(top==0) G[n+1].PB(i);
            else G[st[top]].PB(i);
            st[++top] = i;
        }
    }
    dfs(n+1);
    for(int i = 1; i <= n; ++i) {
        Inc(1,1,n+1,in[i],out[i]);
        if(i-kk>=1) Reset(1,1,n+1,in[i-kk]);
        if(i>=kk) ans[++m] = tr[1];
    }
    REP(i,1,m) printf("%d%c", ans[i], (i==m)?'\n':' ');
    return 0;
}
