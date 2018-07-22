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
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = (5e4) * 6 + 10;
const int c_sz = 3 + 6;

struct State {
    int val;
    State *par, *go[c_sz];
    void Init() { val = 0, par = NULL, mem(go,0); }
} que[maxn*2 + 5], *root, *last;
int tot;

void Extend(int w) {
    State *p = last, *np = que + (tot++);
    np->Init();
    np->val = p->val + 1;
    while(p != NULL && p->go[w] == NULL)
        p->go[w] = np, p = p->par;
    if(p == NULL) np->par = root;
    else {
        State *q = p->go[w];
        if(p->val + 1 == q->val) np->par = q;
        else {
            State *nq = que + (tot++);
            *nq = *q;
            nq->val = p->val + 1;
            np->par = q->par = nq;
            while(p != NULL && p->go[w] == q)
                p->go[w] = nq, p = p->par;
        }
    }
    last = np;
}

const int f[6][3] = {{0,1,2}, {0,2,1}, {1,0,2}, {1,2,0}, {2,0,1}, {2,1,0}};

int n;
char str[maxn + 5];

int main() {
    while(~scanf("%d", &n)) {
        scanf("%s", str);
        root = last = que;
        tot = 1, que[0].Init();
        for(int t = 0; t < 6; ++t) {
            for(int i = 0; i < n; ++i)
                Extend( f[t][ str[i]-'a' ] );
            Extend(t+3);
        }
        LL ans = 0;
        for(int i = 1; i < tot; ++i) {
            int l = 1, r = que[i].val - (que[i].par->val);
            int lim = (que[i].val-1) % (n+1) + 1;
            if(lim == n+1) continue;
            int ps = que[i].val - lim + 1;
            if(ps <= l) ans += r-l+1;
            else if(ps <= r) ans += r-ps+1;
        }
        int mx = 0, now = 0, wd = -1;
        for(int i = 0; i < n; ++i) {
            if(str[i]-'a' == wd) {
                ++now; mx = max(mx, now);
            }
            else {
                wd = str[i] - 'a';
                now = 1; mx = max(mx, now);
            }
        }
        printf("%lld\n", (ans+mx*3) / 6);
    }
    return 0;
}
