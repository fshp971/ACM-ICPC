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

const int maxn = 2e5;

int n;
LL T;
deque<int> q;

int main() {
    scanf("%d%lld", &n, &T);
    for(int i = 1, a; i <= n; ++i)
        scanf("%d", &a), q.push_back(a);
    LL ans = 0;
    while(q.size()) {
        int mx = 0;
        LL sum = 0;
        for(auto u : q) mx = max(mx, u), sum += u;
        if(T >= mx) ans += ((T-mx)/sum) * q.size(), T = (T-mx)%sum + mx;
        int sz = q.size();
        while(sz--) {
            int a = q.front(); q.pop_front();
            if(a<=T) ++ans, T-=a;
            if(a<=T) q.push_back(a);
        }
    }
    printf("%lld\n", ans);
    return 0;
}
