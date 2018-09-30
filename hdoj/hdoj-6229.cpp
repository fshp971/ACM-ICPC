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

const int walk[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};

LL Gcd(LL a, LL b) { return b ? Gcd(b,a%b) : a; }

int n, kk;
LL a1[5], a2[5];

set<pii> Set;
int tot = 0;
pii vec[4000+5];
int main() {
    int __; scanf("%d", &__);
    for(int _ = 1; _ <= __; ++_) {
        scanf("%d%d", &n, &kk);
        if(n==1) a1[1] = a2[1] = 1, a1[2] = a2[2] = 0;
        else a1[1] = a2[1] = 0, a1[2] = 4, a2[2] = 3;
        if(n>=3) {
            a1[3] = LL(n-2)*4;
            a2[3] = LL(n-2)*2;

            a1[4] = LL(n-2)*(n-2);
            a2[4] = (LL(n-2)*(n-1)) >> 1;
        }
        else a1[3] = a2[3] = 0, a1[4] = a2[4] = 0;
        ///*
        Set.clear();
        tot = 0;
        while(kk--) {
            int x,y, d = 0; scanf("%d%d", &x, &y);
            if(Set.find(pii(x,y)) != Set.end()) continue;
            REP(t,0,3) {
                int xx = x+walk[t][0];
                int yy = y+walk[t][1];
                if(xx<0||xx>=n||yy<0||yy>=n) continue;
                vec[++tot] = pii(xx,yy);
                ++d;
            }
            Set.insert( MP(x,y) );
            //printf("x = %d, y = %d, d = %d\n", x, y, d);
            --a1[d];
            if(x+y>=n-1) --a2[d];
        }
        sort(vec+1, vec+1+tot);
        tot = unique(vec+1, vec+1+tot) - vec - 1;
        for(int i = 1; i <= tot; ++i) {
            if(Set.find(vec[i]) != Set.end()) continue;
            int x = vec[i].fi, y = vec[i].se;
            int d1 = 0, d2 = 0;
            REP(t,0,3) {
                int xx = x+walk[t][0];
                int yy = y+walk[t][1];
                if(xx<0||xx>=n||yy<0||yy>=n) continue;
                ++d1;
                if(Set.find(pii(xx,yy)) != Set.end()) ++d2;
            }
            --a1[d1], ++a1[d1-d2];
            if(x+y>=n-1) --a2[d1], ++a2[d1-d2];
        }
        //*/
        LL s1 = 0, s2 = 0;
        REP(i,1,4) {
            s1+=a1[i]*(i+1), s2+=a2[i]*(i+1);
            //printf("a1[%d] = %lld, a2[%d] = %lld\n", i, a1[i], i, a2[i]);
        }
        if(s2 == 0) {
            printf("Case #%d: %d/1\n", _, (n==1) ? 1 : 0);
        }
        else {
            LL g = Gcd(s1,s2);
            printf("Case #%d: %lld/%lld\n", _, s2/g, s1/g);
        }
    }
    return 0;
}
