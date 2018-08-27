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

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e5;
const int P = 998244353;

inline LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%P; a=a*a%P, b>>=1; } return r; }

int phi[maxn+5];
void phi_maker() {
	memset(phi,0,sizeof(phi));
	phi[1] = 1;
	for(int i=2;i<=maxn;++i) if(!phi[i]) {
		for(int k=i;k<=maxn;k+=i) {
			if(!phi[k]) phi[k] = k;
			phi[k] = phi[k] / i * (i-1);
		}
	}
}

int n, M, bi, cnt[maxn+5];
LL inv[maxn+5];
vector<int> deco[maxn + 5];

void Pre() {
    phi_maker();
    inv[1] = 1;
    REP(i,2,maxn) inv[i] = LL(P-P/i)*inv[P%i]%P;
    for(int x = 1; x <= maxn; ++x) {
        for(int i = 1; i*i <= x; ++i) {
            if(x%i) continue;
            deco[x].PB(i);
            if(i*i!=x) deco[x].PB(x/i);
        }
    }
}

int main() {
    Pre();
    int _; scanf("%d", &_);
    while(_--) {
        scanf("%d%d", &n, &M);
        mem(cnt,0);
        REP(i,1,n) {
            scanf("%d",&bi);
            for(auto x : deco[bi]) ++cnt[x];
        }
        LL ans = 0;
        for(int m = 1; m <= M; ++m) {
            LL tmp = 0;
            for(auto x : deco[m]) {
                tmp = (tmp + (PowMod(m+1,cnt[x])-1+P) * phi[x]) % P;
            }
            tmp = tmp*inv[m] % P;
            ans ^= tmp;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
