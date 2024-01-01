#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define PER(i,a,b) for(int i = a; i >= b; --i)
#define PB push_back
#define MP make_pair
#define fi first
#define se second
typedef long long LL;
typedef long double LD;

const int maxn = 2e5, maxk = 20;
const int P = 998244353;

template<typename T>
void add_(T &a, T b) { a+=b; if(a>=P) a-=P; }

inline int S2(int x) { return ((x*LL(x+1)) >> 1) % P; }

struct Fenwick {
    int n;
    vector<int> tr;
    Fenwick(int _n): n(_n) { tr = vector<int>(_n); }
    void clear(int _n) { n=_n; REP(i,1,n) tr[i]=0; }
    void add(int x, int d) { for(;x<=n;x+=x&(-x)) add_(tr[x],d); }
    int sum(int x) { int r=0; for(;x;x-=x&(-x)) add_(r,tr[x]); return r; }
    int sum(int l, int r) { return (sum(r) - sum(l-1) + P) % P; }
} fwk1(maxn+5), fwk2(maxn+5);

vector<int> pp(maxn+5), qq(maxn+5), pos(maxn*2+5);
vector<int> cache(maxk+5), ff1(maxk+5), ff2(maxk+5);

int main() {
    ios::sync_with_stdio(0);
    int _; cin >> _;
    int n, kk;
    while(_--) {
        cin >> n >> kk;
        REP(i,1,n) cin >> pp[i], pos[pp[i]] = i;
        REP(i,1,kk) cin >> qq[i];

        int ans = 0;
        fwk1.clear(kk);
        for(int i = 1; i <= kk; ++i) {
            add_(ans, (i-1) - fwk1.sum(qq[i]+1));
            fwk1.add(qq[i]+1, 1);
        }
        ans = ans * LL(n) % P;

        int lim = min(maxk, kk);
        REP(i,1,lim) {
            ff1[i] = S2(kk-i);
            ff2[i] = (S2(kk) - S2(i-1) + P + kk * LL(i-1)) % P;
            cache[i] = 1;
        }
        fwk1.clear(n);
        fwk2.clear(n);
        for(int i = 1; i <= (n<<1); i += 2) {
            for(int k = 1; k <= lim; ++k) {
                int tmp1 = (ff1[k] - ff1[k-1] + P) % P;
                int tmp2 = (ff2[k] - ff2[k-1] + P) % P;
                while(cache[k] <= (n<<1) && LL(1<<(k-1))*cache[k] < i) {
                    fwk1.add(pos[cache[k]], tmp1);
                    fwk2.add(pos[cache[k]], tmp2);
                    cache[k] += 2;
                }
            }
            add_(ans, fwk1.sum(pos[i]-1));
            add_(ans, fwk2.sum(pos[i]+1, n));
        }
        cout << ans << '\n';
    }
    return 0;
}
