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

const int maxn = 100, maxm = (maxn + 2) * 1000;

int sa[maxm + 5], Rank[maxm + 5], height[maxm + 5];
int tx[maxm + 5], ty[maxm + 5], tc[maxm + 5];

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
        for(i = 0;i < size; ++i) tc[i] = 0;
        for(i = 0; i < len; ++i) ++tc[tx[ty[i]]];
        for(i = 1; i < size; ++i) tc[i] += tc[i-1];
        for(i = len - 1; i >= 0; --i) sa[--tc[tx[ty[i]]]] = ty[i];
        swap(tx, ty), p = 1, tx[sa[0]] = 0;
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
        j = sa[Rank[i]-1];
        while(a[i+k] == a[j+k]) ++k;
        height[Rank[i]] = k;
    }
}

int n, hf, arr[maxm + 5], id[maxm + 5];
char str[1005], vist[maxn + 5];

bool Check(int len, int lim) {
    mem(vist, 0);
    int cnt = 0;
    for(int i = 1; i <= len; ++i) {
        if(height[i] < lim)
            mem(vist, 0), vist[id[sa[i]]] = 1, cnt = 1;
        else {
            if(!vist[id[sa[i]]]) vist[id[sa[i]]] = 1, ++cnt;
            if(cnt >= hf) return true;
        }
    }
    return false;
}

int main() {
    while(scanf("%d", &n), n) {
        hf = (n >> 1) + 1;
        int len = 0;
        for(int i = 1; i <= n; ++i) {
            scanf("%s", str);
            for(int k = 0; str[k] != '\0'; ++k)
                id[len] = i, arr[len++] = str[k] - 'a' + 1;
            id[len] = 0, arr[len++] = i + 30;
        }
        --len;
        BuildSA(arr, len, 150);
        GetHeight(arr, len);
        int l = 1, r = 1000, ans = 0;
        while(l <= r) {
            int mid = (l + r) >> 1;
            if(Check(len, mid))
                ans = mid, l = mid + 1;
            else r = mid - 1;
        }
        if(ans == 0) { puts("?\n"); continue; }
        mem(vist, 0);
        int cnt = 0;
        for(int i = 1; i <= len; ++i) {
            if(height[i] < ans)
                mem(vist, 0), vist[id[sa[i]]] = 1, cnt = 1;
            else if(!vist[id[sa[i]]]) vist[id[sa[i]]] = 1, ++cnt;
            if(cnt >= hf && (i == len || height[i+1] < ans)) {
                for(int k = 0; k < ans; ++k)
                    printf("%c", (char)(arr[sa[i] + k] + 'a' - 1));
                printf("\n");
            }
        }
        printf("\n");
    }
    return 0;
}
