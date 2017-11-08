#include<bits/stdc++.h>

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

const int maxn = 2e5;

int n, m, seg[maxn + 5], ans[maxn + 5];
int pre[maxn + 5], L[maxn + 5], R[maxn + 5], Rnum[maxn + 5];
int tree[maxn + 5];
vector< pair<pii, int> > que;

void Add(int x, int del) { for(; x <= n; x += x&(-x)) tree[x] += del; }
int Sum(int x) { int res = 0; for(; x; x -= x&(-x)) res += tree[x]; return res; }

bool vist[maxn + 5];
vector<int> deco[maxn + 5];
void GetPrime() {
    for(int i = 2; i <= maxn; ++i)
        if(!vist[i]) {
            for(int k = i; k <= maxn; k += i)
                vist[k] = 1, deco[k].PB(i);
        }
}

bool cmp(const int &a, const int &b) { return R[a] < R[b]; }

int main() {
    GetPrime();
    while(scanf("%d%d", &n, &m), n) {
        REP(i,1,n) scanf("%d", seg + i), tree[i] = 0;
        REP(i,1,maxn) pre[i] = 0;
        for(int i = 1; i <= n; ++i) {
            L[i] = 1;
            if(seg[i] == 1)  continue;
            for(auto it : deco[seg[i]])
                L[i] = max(L[i], pre[it] + 1), pre[it] = i;
        }
        REP(i,1,maxn) pre[i] = n + 1;
        for(int i = n; i >= 1; --i) {
            R[i] = n;
            if(seg[i] == 1) continue;
            for(auto it : deco[seg[i]])
                R[i] = min(R[i], pre[it] - 1), pre[it] = i;
        }
        REP(i,1,n) Rnum[i] = i;
        sort(Rnum + 1, Rnum + 1 + n, cmp);
        que.clear();
        int l, r;
        for(int i = 1; i <= m; ++i)
            scanf("%d%d", &l, &r), que.PB( MP( MP(r,l), i ) );
        sort(que.begin(), que.end());
        int pt1 = 1, pt2 = 1;
        for(auto it : que) {
            while(pt1 <= n && pt1 <= it.fi.fi) {
                Add(L[pt1], 1);
               if(pt1 < n)  Add(pt1 + 1, -1);
               ++pt1;
            }
            while(pt2 <= n && R[Rnum[pt2]] < it.fi.fi) {
                Add(L[Rnum[pt2]], -1);
                if(Rnum[pt2] < n) Add(Rnum[pt2] + 1, 1);
                ++pt2;
            }
            ans[it.se] = Sum(it.fi.se);
        }
        for(int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
    }
    return 0;
}
