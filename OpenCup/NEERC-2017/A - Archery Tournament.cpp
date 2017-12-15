#include<bits/stdc++.h>

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

int n;
map<pii,int> tree;

inline LL Dist(LL x0, LL y0, LL x1, LL y1) {
    return (x0-x1)*(x0-x1) + (y0-y1)*(y0-y1);
}

int main() {
    int od, x, y;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%d%d%d", &od, &x, &y);
        if(od == 1) tree[MP(x,y)] = i;
        else {
            auto it = tree.lower_bound(MP(x,y));
            if(it != tree.end()) {
                if(Dist(it->fi.fi,it->fi.se,x,y) < LL(it->fi.se)*(it->fi.se)) {
                    printf("%d\n", it->se);
                    tree.erase(it);
                    continue;
                }
            }
            if(it != tree.begin()) {
                --it;
                if(Dist(it->fi.fi,it->fi.se,x,y) < LL(it->fi.se)*(it->fi.se)) {
                    printf("%d\n", it->se);
                    tree.erase(it);
                    continue;
                }
            }
            printf("-1\n");
        }
    }
    return 0;
}
