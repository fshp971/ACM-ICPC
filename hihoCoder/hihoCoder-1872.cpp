#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define PER(i,a,b) for(int i = a; i >= b; --i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;
typedef __int128 LINT;

const int maxn = 32000;
const int Step = 2e7;

int Gcd(int a, int b) { return b ? Gcd(b,a%b) : a; }

int Sqrt(int n) {
    int l = 1, r = maxn, res = 0;
    while(l<=r) {
        int mid = (l+r)>>1, tmp = mid*mid;
        if(tmp<=n) res = mid, l = mid+1;
        else r = mid-1;
    }
    return res;
}

template<class T>
inline T sq(T x) { return x*x; }

bool vis[maxn+5];
int prime[maxn+5];
int mu[maxn+5];
int ff[Step+5];
void Pre() {
    int tot = 0;
    mu[1] = 1;
    for(int i = 2; i <= maxn; ++i) {
        if(!vis[i]) prime[++tot] = i, mu[i] = -1;
        for(int k = 1; k <= tot; ++k) {
            if(LL(prime[k])*i > maxn) break;
            vis[prime[k]*i] = true;
            if(i % prime[k]) mu[i*prime[k]] = -mu[i];
            else {
                mu[i * prime[k]] = 0;
                break;
            }
        }
    }

    int i2, k2;
    for(int i = 1; i <= maxn; i+=2) {
        i2 = i*i;
        if(i2>Step) break;
        for(int k = 2; k <= maxn; k+=2) {
            k2 = k*k;
            if(i2+k2>Step) continue;
            if(Gcd(i,k)==1) ++ff[i2+k2];
        }
    }
    REP(i,1,Step) ff[i] += ff[i-1];
}

LL F(int n) {
    if(n<=Step) return ff[n];
    int lim = Sqrt(n);
    LL res = 0;
    for(int d = 1; d <= lim; ++d) {
        LL tmp = 0, cc;
        int lim2 = lim/d;
        for(int k = 1, nx; k <= lim2; k = nx+1) {
            cc = Sqrt(n-sq(k*d)) / d;
            nx = Sqrt(n-sq(cc*d)) / d;
            tmp += (nx-k+1) * cc;
            if(d&1) {
                tmp -= ((nx-k+1+(k&1))>>1) * ((cc+1)>>1);
            }
        }
        res += tmp*mu[d];
    }
    return (res>>1);
}

int main() {
    Pre();
    int _; scanf("%d", &_);
    while(_--) {
        int n; scanf("%d", &n);
        LL ans = 0;
        for(int i = 1, nx; i <= n; i = nx+1) {
            nx = n/(n/i);
            ans += F(n/i) * (nx-i+1);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
