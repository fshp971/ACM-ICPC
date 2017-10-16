#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
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

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e5;

int sa[maxn + 5], Rank[maxn + 5], height[maxn + 5];
int tx[maxn + 5], ty[maxn + 5], tc[maxn + 5];

void BuildSA(int *a, int len, int size) {
    a[len++] = 0;
    int i, k, p;
    for(i = 0; i < size; ++i) tc[i] = 0;
    for(i = 0; i < len; ++i) ++tc[tx[i] = a[i]];
    for(i = 1; i < size; ++i) tc[i] += tc[i-1];
    for(i = len - 1; i >= 0; --i) sa[--tc[tx[i]]] = i;
    for(k = 1; k <= len; k <<= 1) {
        p = 0;
        for(i = len - k; i < len; ++i) ty[p++] = i;
        for(i = 0; i < len; ++i) if(sa[i] >= k) ty[p++] = sa[i] - k;
        for(i = 0; i < size; ++i) tc[i] = 0;
        for(i = 0; i < len; ++i) ++tc[tx[ty[i]]];
        for(i = 0; i < size; ++i) tc[i] += tc[i-1];
        for(i = len - 1; i >= 0; --i) sa[--tc[tx[ty[i]]]] = ty[i];
        swap(tx, ty);
        p = 1, tx[sa[0]] = 0;
        for(i = 1; i < len; ++i)
            tx[sa[i]] = ty[sa[i]] == ty[sa[i-1]] && ty[min(sa[i]+k,len-1)] == ty[min(sa[i-1]+k,len-1)] ? p-1 : p++;
        if(p >= len) break;
        size = p;
    }
    --len;
}

void GetHeight(int *a, int len) {
    int i, j, k = 0;
    for(i = 0; i <= len; ++i) Rank[sa[i]] = i;
    for(i = 0; i < len; ++i) {
        if(k) --k;
        j = sa[Rank[i] - 1];
        while(a[i+k] == a[j+k]) ++k;
        height[Rank[i]] = k;
    }
}

int n, m, kk;
int seg[maxn + 5], f[maxn + 5];
int main() {
    while(~scanf("%d%d%d", &n, &m, &kk)) {
        int len = 0;
        for(int i = 1; i <= n; ++i)
            scanf("%d", seg + len), ++seg[len], ++len;
        seg[len] = 20000, ++len;
        for(int i = 1; i <= m; ++i)
            scanf("%d", seg + len), ++seg[len], ++len;
        BuildSA(seg, len, 20001);
        GetHeight(seg, len);
        FOR(i,0,n) f[i] = 0;
        int now = 0, ans = 0;
        for(int i = 1; i <= len; ++i) {
            if(sa[i] < n)
                now = min(now, height[i]), f[sa[i]] = max(f[sa[i]], now);
            else now = len + 5;
        }
        now = 0, height[len + 1] = 0;
        for(int i = len; i >= 1; --i) {
            if(sa[i] < n)
                now = min(now, height[i+1]), f[sa[i]] = max(f[sa[i]], now);
            else now = len + 5;
        }
        FOR(i,0,n) if(f[i] == kk) ++ans;
        printf("%d\n", ans);
    }
    return 0;
}
