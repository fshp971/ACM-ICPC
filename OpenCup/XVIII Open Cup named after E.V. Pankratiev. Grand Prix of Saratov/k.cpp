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
typedef unsigned long long ULL;
typedef pair<int,int> pii;
typedef pair<ULL,LL> PP;

const ULL base = 19260817;
const ULL base2 = 67,  md2 = 1e9+9;

const int maxn = 1e5;

int n, m, ans[maxn+5];
char ss[maxn+5], tt[maxn+5];
ULL ha[maxn+5], pw[maxn+5];
LL ha2[maxn+5], pw2[maxn+5];
vector<pair<PP,int>> vec[maxn+5];
map<PP,int> Map;
int seg[maxn+5];

inline PP GetHa(int l, int r) {
    return PP( ha[r] - ha[l-1]*pw[r-l+1], (ha2[r] - ha2[l-1]*pw2[r-l+1]%md2 + md2) % md2 );
}

int main() {
    pw[0] = 1, pw2[0] = 1;
    REP(i,1,maxn) {
        pw[i] = pw[i-1]*base;
        pw2[i] = pw2[i-1]*base2 % md2;
    }
    scanf("%d%d", &n, &m);
    scanf("%s", ss+1);
    REP(i,1,n) {
        ha[i] = ha[i-1]*base + ss[i]-'a';
        ha2[i] = (ha2[i-1]*base2 + ss[i]-'a') % md2;
    }
    REP(i,1,m) {
        scanf("%s", tt+1);
        PP tmp = PP(0,0);
        int len = strlen(tt+1);
        for(int k = 1; k <= len; ++k) {
            tmp.fi = tmp.fi*base + tt[k]-'a';
            tmp.se = (tmp.se*base2 + tt[k]-'a') % md2;
        }
        vec[len].PB( MP(tmp,i) );
    }
    for(int i = 1; i <= maxn; ++i) {
        if(vec[i].size() == 0) continue;
        Map.clear();
        for(int k = n-i+1; k >= 1; --k) {
            PP tmp;
            if(k+i+i-1 <= n) {
                tmp = GetHa(k+i, k+i+i-1);
                Map[tmp] = seg[k+i];
            }
            tmp = GetHa(k, k+i-1);
            seg[k] = Map[tmp]+1;
        }
        for(int k = i; k >= 1; --k) {
            if(k+i-1<=n) Map[GetHa(k,k+i-1)] = seg[k];
        }
        for(auto pp : vec[i])
            ans[pp.se] = Map[pp.fi];
    }
    REP(i,1,m) printf("%d\n", ans[i]);
    return 0;
}
