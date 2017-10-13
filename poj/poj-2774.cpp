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

const int maxn = 200000;

int sa[maxn + 5], Rank[maxn + 5], height[maxn + 5];
int tx[maxn + 5], ty[maxn + 5], tc[maxn + 5];

void BuildSA(char *a, int len, int size) {
    int i, k, p;
    ++len;
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
    for(i = 0; i < len; ++i) Rank[sa[i]] = i;
    for(i = 0; i < len; ++i) {
        if(k) --k;
        j = sa[Rank[i]-1];
        while(a[i+k] == a[j+k]) ++k;
        height[Rank[i]] = k;
    }
}

char str[maxn + 5];

int main() {
    int len1, len2, len, ans = 0;
    scanf("%s", str), len1 = strlen(str), str[len1] = '#';
    scanf("%s", str + len1 + 1), len2 = strlen(str + len1 + 1);
    len = len1 + 1 + len2;
    BuildSA(str, len, 127);
    GetHeight(str, len);
    for(int i = 1; i <= len; ++i)
        if((sa[i-1] < len1 && sa[i] > len1) || (sa[i-1] > len1 && sa[i] < len1))
            ans = max(ans, height[i]);
    printf("%d\n", ans);
    return 0;
}
