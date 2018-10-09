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
typedef double DB;

const int maxn = 1e5;

int n;
int xi[maxn+5], yi[maxn+5];

inline DB sqr(DB x) { return x*x; }

bool Chk(DB r) {
    DB mi = -(1e10), mx = (1e10);
    REP(i,1,n) {
        DB tmp = 2.0 * r * yi[i] - sqr(yi[i]);
        if(tmp < 0) return false;
        tmp = sqrt( max(tmp,DB(0)) );
        mi = max(mi, xi[i]-tmp);
        mx = min(mx, xi[i]+tmp);
        if(mi > mx) return false;
    }
    return true;
}

int main() {
    scanf("%d", &n);
    REP(i,1,n) scanf("%d%d", xi+i, yi+i);
    REP(i,2,n) {
        if( (yi[i]>0&&yi[i-1]<0) || (yi[i]<0&&yi[i-1]>0) )
            exit( puts("-1")*0 );
    }
    REP(i,1,n) yi[i] = abs(yi[i]);
    DB l = 0, r = (1e20);
    REP(i,1,100) {
        DB mid = (r+l) / 2.0;
        if(Chk(mid)) r = mid;
        else l = mid;
    }
    printf("%.10f\n", l);
    return 0;
}
