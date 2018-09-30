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

LL Calc(LL n, LL m) {
    if(n>m) swap(n,m);
    if(n==1) {
        LL t = (m/6)*6, r = m%6;
        if(r==4) t += 2;
        else if(r==5) t += 4;
        return t;
    }
    if(n==2) {
        if(m<=2) return 0;
        if(m==3) return 4;
        if(m==7) return 12;
        return n*m;
    }
    return ((n*m)>>1)<<1;
}

int main() {
    LL n, m;
    scanf("%lld%lld", &n, &m);
    printf("%lld\n", Calc(n,m));
    return 0;
}
