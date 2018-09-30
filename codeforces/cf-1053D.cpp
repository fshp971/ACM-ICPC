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
#define PER(i,a,b) for(int i=a; i>=b; --i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 2e5;
const int maxP = 2e6;
const int P = 1e9+7;

inline LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%P; a=a*a%P, b>>=1; } return r; }

bool vis[maxP+5];
int mx1[maxP+5], mx2[maxP+5];
int prime[maxn+5], tot = 0;
void Pre() {
    prime[++tot] = 2;
    for(int i = 3; i <= maxP; i += 2) if(!vis[i]) {
        prime[++tot] = i;
        for(LL k = LL(i)*i; k <= maxP; k += i)
            vis[k] = 1;
    }
    //printf("tot = %d\n", tot);
}

int n, ai[maxn+5];
bool type[maxn+5];

inline void Upd(int a, int b) {
    if(mx1[a]<b) swap(mx1[a],b);
    if(mx2[a]<b) swap(mx2[a],b);
}

int main() {
    Pre();
    scanf("%d", &n);
    REP(i,1,n) scanf("%d", ai+i);
    sort(ai+1, ai+1+n);
    PER(i,n,1) {
        if(mx1[ai[i]] == 0) mx1[ai[i]] = 1;
        else {
            type[i] = 1;
            int val = ai[i]-1;
            for(int k = 1; k<=tot && prime[k]*prime[k]<=val; ++k) {
                int c = 0;
                while(val%prime[k]==0) ++c, val/=prime[k];
                Upd(prime[k], c);
            }
            if(val>1) Upd(val, 1);
        }
    }
    int del = 0;
    PER(i,n,1) {
        if(del) break;
        if(type[i] == 0) continue;
        bool fg = 1;
        int val = ai[i]-1;
        for(int k = 1; k<=tot && prime[k]*prime[k]<=val; ++k) {
            int c = 0;
            while(val%prime[k]==0) ++c, val/=prime[k];
            if(mx1[prime[k]]==c && mx2[prime[k]]!=c) {
                fg = 0; break;
            }
        }
        if(val>1 && (mx1[val]==1 && mx2[val]!=1)) fg = 0;
        del |= fg;
    }
    LL ans = 1;
    REP(i,1,maxP) if(mx1[i]) ans = ans * PowMod(i,mx1[i]) % P;
    printf("%lld\n", (ans+del) % P);
    return 0;
}
