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

const int maxn = 4000, maxm = 202 * maxn;

int sa[maxm + 5], Rank[maxm + 5], height[maxm + 5];
int tx[maxm + 5], ty[maxm + 5], tc[maxm + 5];

void BuildSA(char *a, int len, int size) {
    a[len++] = '\0';
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
        for(i = 1; i < size; ++i) tc[i] += tc[i-1];
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

void GetHeight(char *a, int len) {
    int i, j, k = 0;
    for(i = 0; i <= len; ++i) Rank[sa[i]] = i;
    for(i = 0; i < len; ++i) {
        if(k) --k;
        j = sa[Rank[i] - 1];
        while(a[i+k] == a[j+k]) ++k;
        height[Rank[i]] = k;
    }
}

char str[maxm + 5];
int n, ps[maxm + 5];
char vist[maxn + 5];

bool Check(int len, int lim, int &pt) {
    memset(vist, 0, sizeof(bool) * (n + 1));
    int cnt = 0;
    for(int i = 1; i <= len; ++i) {
        if(height[i] < lim) {
            memset(vist, 0, sizeof(bool) * (n + 1)), cnt = 0;
            if(ps[sa[i]])
                vist[ps[sa[i]]] = 1, ++cnt;
            continue;
        }
        if(!vist[ps[sa[i]]] && ps[sa[i]])
            vist[ps[sa[i]]] = 1, ++cnt;
        if(cnt == n) {
            pt = sa[i];
            return true;
        }
    }
    return false;
}

int main() {
    int len;
    while(scanf("%d", &n), n) {
        len = 0;
        for(int i = 1; i <= n; ++i) {
            scanf("%s", str + len);
            while(str[len] != '\0') ps[len++] = i;
            str[len] = '#', ps[len++] = 0;
        }
        --len;
        BuildSA(str, len, 127);
        GetHeight(str, len);
        int l = 1, r = 200, ans = 0, pt = -1;
        while(l <= r) {
            int mid = (l + r) >> 1;
            if(Check(len, mid, pt))
                ans = mid, l = mid + 1;
            else r = mid - 1;
        }
        if(ans == 0) printf("IDENTITY LOST\n");
        else
            str[pt + ans] = '\0', printf("%s\n", str + pt);
    }
    return 0;
}
