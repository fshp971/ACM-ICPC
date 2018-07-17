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
typedef unsigned long long ULL;
typedef pair<int,int> pii;

const int maxn = 2e5;
const int base = 19260817;
const int md2 = 998244353, base2 = 37;

int n;
ULL ha[26][maxn + 5], pw[maxn + 5];
LL ha2[26][maxn + 5], pw2[maxn + 5];
pair<ULL,LL> aa[30], bb[30];
char str[maxn + 5];

void GetHa(pair<ULL,LL> *a, int s, int l) {
    for(int i = 0; i < 26; ++i) {
        ULL t1 = ha[i][s+l-1] - ha[i][s-1] * pw[l];
        LL t2 = (ha2[i][s+l-1] - ha2[i][s-1] * pw2[l] % md2 + md2) % md2;
        a[i] = MP(t1,t2);
    }
    sort(a, a+26);
}

int main() {
    int T;
    scanf("%d%d", &n, &T);
    scanf("%s", str + 1);
    pw[0] = 1, pw2[0] = 1;
    for(int i = 1; i <= n; ++i) {
        for(int k = 0; k < 26; ++k) {
            ha[k][i] = ha[k][i-1] * base;
            ha2[k][i] = ha2[k][i-1] * base2 % md2;
        }
        ha[ str[i]-'a' ][i] += 1;
        pw[i] = pw[i-1] * base;
        ha2[ str[i]-'a' ][i] = (ha2[ str[i]-'a' ][i]+1) % md2;
        pw2[i] = pw2[i-1] * base2 % md2;
    }
    while(T--) {
        int x, y, l, fg = 1;
        scanf("%d%d%d", &x, &y, &l);
        GetHa(aa, x, l), GetHa(bb, y, l);
        for(int i = 0; i < 26 && fg; ++i)
            if(aa[i] != bb[i]) fg = 0;
        printf("%s\n", fg ? "YES" : "NO");
    }
    return 0;
}
