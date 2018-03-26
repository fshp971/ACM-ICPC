#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cassert>
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

char seg[110];
int main() {
    freopen("brackets.in", "r", stdin);
    freopen("brackets.out", "w", stdout);
    int n, l, r;
    scanf("%d%d%d", &n, &l, &r);
    for(int i = 0; i <= r-l; ++i)
        seg[i+l] = (i&1) ? ']' : '[';
    int d = min(l-1, n-r);
    for(int i = 0; i < d; ++i)
        seg[i+1] = '(', seg[n-i] = ')';
    for(int i = 0; i+d+1 < l; ++i)
        seg[i+d+1] = (i&1) ? ')' : '(';
    for(int i = 0; i+r+1 <= n-d; ++i)
        seg[i+r+1] = (i&1) ? ')' : '(';
    seg[n+1] = '\0';
    printf("%s\n", seg+1);
    return 0;
}
