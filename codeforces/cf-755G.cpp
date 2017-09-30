#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
typedef long long LL;
typedef pair<int,int> pii;

const LL P = 998244353, G = 3;
const int maxk = (1 << 16);

LL PowMod(LL a, LL b) {
    LL res = 1;
    while(b) {
        if(b & 1) res = res * a % P;
        a = a * a % P, b >>= 1;
    }
    return res;
}

void NTT(LL *a, int len, int type) {
    int i, j, k, l;
    for(i = 1, j = len >> 1; i < len - 1; ++i) {
        if(i < j) swap(a[i], a[j]);
        k = len >> 1;
        while(j >= k)
            j -= k, k >>= 1;
        j += k;
    }
    LL var, step, u, v;
    for(l = 2; l <= len; l <<= 1) {
        step = PowMod(G, (P-1) / l);
        for(k = 0; k < len; k += l) {
            var = 1;
            for(i = k; i < k + l/2; ++i) {
                u = a[i], v = var * a[i + l/2] % P;
                a[i] = (u + v) % P;
                a[i + l/2] = (u - v + P) % P;
                var = var * step % P;
            }
        }
    }
    if(type == -1) {
        for(i = 1; i < len / 2; ++i) swap(a[i], a[len-i]);
        LL inv = PowMod(len, P-2);
        for(i = 0; i < len; ++i) a[i] = a[i] * inv % P;
    }
}

unordered_map<int, int> Map;
int n, kk, llen, tot = 0;
LL f[150 + 5][maxk + 5], gg[maxk + 5];

int dfs(int x) {
    if(Map.count(x)) return Map[x];
    int hf = x >> 1;
    int y1 = dfs(hf), y2 = dfs(x - hf);
    int y3 = dfs(hf - 1), y4 = dfs(x - hf - 1);
    for(int i = 0; i < llen; ++i) {
        f[tot][i] = f[y1][i] * f[y2][i] % P;
        gg[i] = f[y3][i] * f[y4][i] % P;
    }
    NTT(f[tot], llen, -1);
    NTT(gg, llen, -1);
    for(int i = 1; i < kk; ++i)
        f[tot][i] = (f[tot][i] + gg[i - 1]) % P;
    for(int i = kk; i < llen; ++i) f[tot][i] = 0;
    NTT(f[tot], llen, 1);
    Map[x] = tot;
    return tot++;
}

int main() {
    scanf("%d%d", &n, &kk);
    ++kk, llen = 1;
    while(llen < kk + kk - 1) llen <<= 1;

    f[tot][0] = 1;
    NTT(f[tot], llen, 1), Map[0] = tot++;

    f[tot][0] = f[tot][1] = 1;
    NTT(f[tot], llen, 1), Map[1] = tot++;

    n = dfs(n);
    NTT(f[n], llen, -1);
    for(int i = 1; i < kk; ++i) {
        if(i > 1) printf(" ");
        printf("%lld", f[n][i]);
    }
    printf("\n");
    return 0;
}
