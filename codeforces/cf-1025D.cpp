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

const int maxn = 700;

LL Gcd(LL a, LL b) { return b ? Gcd(b,a%b) : a; }

int n, ai[maxn + 5];
LL g[maxn+5][maxn+5];
int vi[maxn+5][maxn+5][2], f[maxn+5][maxn+5][2];

bool dfs(int l, int r, int ti) {
    if(l>r) return true;
    if(vi[l][r][ti]) return f[l][r][ti];
    vi[l][r][ti] = true;
    for(int i = l; i <= r && !f[l][r][ti]; ++i) {
        if(ti==0 && g[i][r+1]==1) continue;
        if(ti==1 && g[l-1][i]==1) continue;
        if(!dfs(l,i-1,0) || !dfs(i+1,r,1)) continue;
        return f[l][r][ti] = true;
    }
    return false;
}

int main() {
    scanf("%d", &n);
    REP(i,1,n) scanf("%d", ai+i);
    REP(i,1,n) REP(k,i+1,n) g[i][k] = Gcd(ai[i],ai[k]);
    if(dfs(1,n,0)) puts("Yes");
    else puts("No");
    return 0;
}
