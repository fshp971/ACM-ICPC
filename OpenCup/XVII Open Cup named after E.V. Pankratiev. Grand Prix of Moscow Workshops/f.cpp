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

const int maxn = 5e6;

struct State {
    int val;
    bool v[2];
    State *go[2], *par;
    void Init() { val = 0, par = NULL; mem(v,0); mem(go,0); }
} que[maxn*2 + 5], *root, *last[2];
int tot;

int lcs = 0;
void Extend(int o, int w) {
    State *p = last[o], *np = que + (tot++);
    np->Init(); np->val = p->val + 1;
    while(p != NULL && p->go[w] == NULL)
        p->go[w] = np, p = p->par;
    if(p == NULL) np->par = root;
    else {
        State *q = p->go[w];
        if(p->val+1 == q->val) np->par = q;
        else {
            State *nq = que + (tot++);
            *nq = *q; nq->val = p->val + 1;
            np->par = q->par = nq;
            while(p != NULL && p->go[w] == q)
                p->go[w] = nq, p = p->par;
        }
    }
    last[o] = np;
    while(np != NULL && np->v[o] == 0) {
        np->v[o] = 1;
        if(np->v[0] && np->v[1])
            lcs = max(lcs, np->val);
        np = np->par;
    }
}

char str[maxn + 5];
int main() {
    int T;
    scanf("%d%s", &T, str);
    LL ans = 0;
    tot = 1, root = last[0] = last[1] = que;
    root->Init();
    for(int t = 0; t < T; ++t) {
        int w = str[t] - '0';
        int a = (lcs ^ w) & 1, c = ((lcs^w) >> 1) & 1;
        Extend(a, c);
        ans += lcs;
    }
    printf("%lld\n", ans);
    return 0;
}
