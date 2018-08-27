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

int main() {
    int _; scanf("%d", &_);
    while(_--) {
        int n, m, kk; scanf("%d%d%d", &n, &m, &kk);
        bool fg = (n&1)==0 || (m&1)==0;
        int ax, ay, bx, by;
        for(int i = 1; i <= kk; ++i) {
            scanf("%d%d%d%d", &ax, &ay, &bx, &by);
            fg |= (ax!=bx || ay!=by) && ((ax+ay)&1)==0 && ((bx+by)&1)==0;
        }
        printf("%d\n", fg ? n*m : n*m+1);
    }
    return 0;
}
