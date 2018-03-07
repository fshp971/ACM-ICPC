#include<bits/stdc++.h>

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

const int md = 1e9 + 7;

inline int Get(int x) {
    if(x < 10) return 1;
    if(x < 100) return 2;
    if(x < 1000) return 3;
    if(x < 10000) return 4;
    if(x < 100000) return 5;
    if(x < 1000000) return 6;
    if(x < 10000000) return 7;
    return 8;
}

LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%md; a=a*a%md, b>>=1; } return r; }

int main() {
    int S;
    LL ans = 0;
    scanf("%d", &S);
    for(int l = 1, r = 1, sum = 0; l < int(1e7); ++r) {
        sum += Get(r);
        while(sum > S) sum -= Get(l++);
        if(l < int(1e7) && sum == S) ++ans;
    }
    for(int i = S/8; i >= 1; --i) {
        if(S%i == 0) {
            LL tmp = PowMod(10, S/i - 1);
            ans = (ans + tmp*10 - tmp - (i - 1) + md) % md;
        }
        else
            ans = (ans + 1) % md;
    }
    printf("%lld\n", ans);
    return 0;
}
