#include <bits/stdc++.h>

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

int n, m, seed, vmax;

inline int rnd() {
    int ret = seed;
    seed = (LL(seed) * 7 + 13) % 1000000007;
    return ret;
}

LL PowMod(LL a, LL b, LL p) { a%=p; LL r=1; while(b) { if(b&1) r=r*a%p; a=a*a%p, b>>=1; } return r; }

map<int,LL> Map;
vector<pair<LL, int>> vec;

int main() {
    int u, op, l, r, x, y;
    map<int,LL>::iterator it1, it2;
    scanf("%d%d%d%d", &n, &m, &seed, &vmax);
    Map[n+1] = 0;
    for(int i = 1; i <= n; ++i)
        Map[i] = (rnd() % vmax) + 1;
    while(m--) {
        op = (rnd() % 4) + 1;
        l = (rnd() % n) + 1;
        r = (rnd() % n) + 1;
        if(l > r) swap(l, r);
        if(op == 3) x = (rnd() % (r - l + 1)) + 1;
        else x = (rnd() % vmax) + 1;
        if(op == 4) y = (rnd() % vmax) + 1;
        it1 = Map.upper_bound(l), --it1;
        if(it1->fi != l) Map[l] = it1->se, ++it1;
        it2 = Map.upper_bound(r+1), --it2;
        if(it2->fi != r+1) Map[r+1] = it2->se, ++it2;
        if(op == 1)
            while(it1 != it2) it1->se += x, ++it1;
        else if(op == 2) {
            while(it1 != it2) Map.erase(it1++);
            Map[l] = x;
        }
        else if(op == 3) {
            vec.clear();
            int pre = l, cc = 0;
            LL key = it1->se;
            while(it1 != it2) {
                ++it1;
                vec.PB(MP(key, it1->fi - pre));
                key = it1->se, pre = it1->fi;
            }
            sort(vec.begin(), vec.end());
            for(auto it : vec) {
                if(cc + it.se >= x) { printf("%lld\n", it.fi); break; }
                cc += it.se;
            }
        }
        else {
            int pre = l;
            LL sum = 0, key = it1->se;
            while(it1 != it2) {
                ++it1;
                sum = (sum + PowMod(key, x, y) * (it1->fi - pre)) % y;
                key = it1->se, pre = it1->fi;
            }
            printf("%lld\n", sum);
        }
    }
    return 0;
}
