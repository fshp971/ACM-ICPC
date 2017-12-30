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

int n, m;
int tree[maxn + 5];
char str[maxn + 5], ans[maxn + 5];
set<int> Set[70];

void Add(int x, int del) { for(;x<=n;x+=x&(-x)) tree[x]+=del; }
int Sum(int x) { int r=0; for(;x;x-=x&(-x)) r+=tree[x]; return r; }

inline int Id(char c) {
    if('a' <= c && c <= 'z') return c - 'a';
    if('A' <= c && c <= 'Z') return c - 'A' + 26;
    return c - '0' + 52;
}

int main() {
    scanf("%d%d", &n, &m);
    scanf("%s", str + 1);
    for(int i = 1; i <= n; ++i) {
        Set[Id(str[i])].insert(i);
        Add(i, 1);
    }
    int l, r;
    char ord[5];
    while(m--) {
        scanf("%d%d%s", &l, &r, ord);
        int ll = 1, rr = n, ps = 0;
        while(ll <= rr) {
            int mid = (ll + rr) >> 1;
            if(l <= Sum(mid)) ps = mid, rr = mid - 1;
            else ll = mid + 1;
        }
        l = ps;
        ll = 1, rr = n, ps = 0;
        while(ll <= rr) {
            int mid = (ll + rr) >> 1;
            if(r >= Sum(mid)) ps = mid, ll = mid + 1;
            else rr = mid - 1;
        }
        r = ps;
        int id = Id(ord[0]);
        vector<set<int>::iterator> hh;
        for(auto it = Set[id].lower_bound(l); it != Set[id].end() && *it <= r; ++it)
            str[*it] = 0, Add(*it, -1), hh.PB(it);
        for(auto it : hh) Set[id].erase(it);
    }
    int tot = 0;
    for(int i = 1; i <= n; ++i)
        if(str[i] != 0) ans[tot++] = str[i];
    ans[tot] = '\0';
    printf("%s\n", ans);
    return 0;
}
