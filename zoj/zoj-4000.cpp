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
#define MP make_pair
#define PB push_back
#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define PER(i,a,b) for(int i = a; i >= b; --i)
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;
typedef double DB;

const DB PI = acos(-1.0);
const int maxn = 2e5;

int n, R;
int xx[maxn+5], yy[maxn+5];
DB deg[maxn+5];
int num[maxn+5], add[maxn+5];

bool comp(const int &a, const int &b) {
    if(deg[a] != deg[b]) return deg[a]<deg[b];
    return add[a] > add[b];
}

int main() {
    int _; scanf("%d", &_);
    while(_--) {
        scanf("%d%d", &n, &R);
        int ct = 0, m = 0, ans = 0;
        REP(i,1,n) {
            int x, y; scanf("%d%d", &x, &y);
            xx[i] = x, yy[i] = y;
            if(x*x+y*y <= R*R) ++ct;
            else {
                if(x>=-R) ++ans;
                DB z = sqrt(x*x+y*y);
                DB theta = atan2(y,x);
                DB beta = acos( min(DB(1.0), max(DB(-1.0),R/z)) );

                ++m, num[m] = m, deg[m] = theta-beta, add[m] = -1;
                if(x==-R && y<0) deg[m] = -PI;
                else if(deg[m]<-PI) deg[m] += PI*2;

                ++m, num[m] = m, deg[m] = theta+beta, add[m] = 1;
                if(x==-R && y>0) deg[m] = PI;
                else if(deg[m]>PI) deg[m] -= PI*2;
            }
        }
        sort(num+1, num+1+m, comp);
        int now = ans;
        REP(i,1,m) {
            now += add[num[i]];
            ans = max(ans, now);
        }
        ans += ct;
        printf("%d\n", ans);
    }
    return 0;
}
