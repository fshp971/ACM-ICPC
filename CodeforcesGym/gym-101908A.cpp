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

#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define PER(i,a,b) for(int i = a; i >= b; --i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;

const int P = 1e9 + 7;
const int maxn = 1e5;

LL Gcd(LL a, LL b) { return b ? Gcd(b,a%b) : a; }

bool vis[maxn+5];
int prime[maxn+5];
int mu[maxn+5], fk1[maxn+5], fk2[maxn+5];

void Pre() {
    int tot = 0;
    mu[1] = 1;
    for(int i = 2; i <= maxn; ++i) {
        if(!vis[i]) prime[++tot] = i, mu[i] = -1;
        for(int k = 1; k <= tot; ++k) {
            if(LL(prime[k]) * i > maxn) break;
            vis[prime[k] * i] = true;
            if(i % prime[k]) mu[i * prime[k]] = -mu[i];
            else {
                mu[i * prime[k]] = 0;
                break;
            }
        }
    }
    REP(i,1,maxn) {
        fk1[i] = (LL(fk1[i-1]) + LL(i) * mu[i] + P) % P;
        fk2[i] = (LL(fk2[i-1]) + LL(i)*i%P * mu[i] + P) % P;
        mu[i] = (LL(mu[i-1]) + mu[i] + P) % P;
    }
}

inline LL S1(LL n) {
    return (n*(n+1) >> 1) % P;
}

int Sqrt(LL n) {
    int l = 1, r = 1e5 + 10, ret = 0;
    while(l <= r) {
        int mid = (l+r) >> 1;
        LL tmp = LL(mid)*mid;
        if(tmp == n) return mid;
        if(tmp < n) ret = mid, l = mid+1;
        else r = mid-1;
    }
    return ret;
}

int n, m;

LL Sum(int L) {
    if(L == 0) return 0LL;
    LL ret = 0;
    int lim = min(n, min(m,L));
    for(int d = 1, nx; d <= lim; d = nx+1) {
        nx = min( n/(n/d), m/(m/d) );
        int nn = n/d, mm = m/d, ll = L/d, lim2 = min(nn,ll);

        LL shit = (LL(L) * L) / (LL(d) * d);
        nx = min( nx, Sqrt(LL(L)*L / shit) );

        LL tmp1 = 0, tmp2 = 0, tmp3 = 0, tmp4 = 0;
        for(int i = 1; i <= lim2; ++i) {
            int lim3 = min( mm, Sqrt(shit - LL(i)*i) );
            tmp1 = (tmp1 + lim3) % P;
            tmp2 = (tmp2 + LL(i)*lim3) % P;
            tmp3 = (tmp3 + S1(lim3)) % P;
            tmp4 = (tmp4 + LL(i) * S1(lim3)) % P;
        }
        tmp1 = tmp1 * n % P * m % P;
        tmp2 = tmp2 * m % P;
        tmp3 = tmp3 * n % P;
        ret = (ret + tmp1 * (LL(mu[nx])-mu[d-1]+P)) % P;
        ret = (ret - (tmp2+tmp3) * (LL(fk1[nx])-fk1[d-1]+P) % P + P) % P;
        ret = (ret + tmp4 * (LL(fk2[nx])-fk2[d-1]+P)) % P;
    }
    ret = ret*2 % P;
    return ret;
}

int main() {
    Pre();
    LL l, r;
    scanf("%d%d%lld%lld", &n, &m, &l, &r);
    LL ans = (Sum(r) - Sum(l) + P) % P;
    if(l == 1) ans = (ans + LL(n-1)*m + LL(m-1)*n) % P;
    for(LL i = 1; i < l; ++i) {
        LL k = Sqrt(l*l - i*i);
        if(i*i+k*k == l*l && Gcd(i,k) == 1 && i < n && k < m) {
            ans = (ans + (n-i) * (m-k) * 2) % P;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
