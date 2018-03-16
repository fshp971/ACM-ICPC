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

const double Pi = acos(-1.0);

LL Gcd(LL a, LL b) { return b ? Gcd(b,a%b) : a; }
LL Lcm(LL a, LL b) { return a / Gcd(a,b) * b; }

int main() {
    LL n, m;
    scanf("%lld%lld", &n, &m);
    double d = cos(Pi / Lcm(n,m)) * tan(Pi / m) / sin(Pi / n);
    printf("%.10f\n", d);
    return 0;
}
