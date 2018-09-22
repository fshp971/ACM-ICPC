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

const int maxn = 2e6;
const int P = 998244353;

int na, nl, nr;
char sa[maxn+5], sl[maxn+5], sr[maxn+5];
int f1[maxn+5], f2[maxn+5];
LL g[maxn+5];

void Z_Function(char *a, int len, int *f) {
    f[1] = len;
    for(int i = 2, l = 0, r = 0; i <= len; ++i) {
        if(i <= r) f[i] = min(r-i+1, f[i-l+1]);
        else f[i] = 0;
        while(i+f[i]<=len && a[i+f[i]]==a[f[i]+1]) ++f[i];
        if(i+f[i]-1 > r) l = i, r = i+f[i]-1;
    }
}

int main() {
    scanf("%s%s%s", sa+1, sl+1, sr+1);
    na = strlen(sa+1), nl = strlen(sl+1), nr = strlen(sr+1);
    sl[nl+1] = sr[nr+1] = '#';
    sprintf(sl+nl+2, "%s", sa+1);
    sprintf(sr+nr+2, "%s", sa+1);
    Z_Function(sl, na+1+nl, f1);
    Z_Function(sr, na+1+nr, f2);

    g[na+1] = 1;
    PER(i,na,1) {
        int l, r;

        if(nl>na-i+1) l = na+1;
        else {
            l = nl;
            int tmp = f1[nl+1+i];
            if(tmp<nl && sl[tmp+1]>sa[i+tmp]) ++l;
        }

        if(sa[i]=='0') r = 1;
        else if(nr>na-i+1) r = na-i+1;
        else {
            r = nr;
            int tmp = f2[nr+1+i];
            if(tmp<nr && sr[tmp+1]<sa[i+tmp]) --r;
        }

        if(l<=r) g[i] = (g[i+l] - g[i+r+1] + P) % P;
        g[i] = (g[i] + g[i+1]) % P;
    }
    printf("%lld\n", (g[1]-g[2]+P)%P);
    return 0;
}
