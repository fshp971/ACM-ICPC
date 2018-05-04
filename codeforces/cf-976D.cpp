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

const int maxn = 1000;

int n;
int di[maxn + 5];
vector<pii> vec;

void Add(int x, int bound) {
    for(int i = bound; i <= di[n]+1; ++i)
        vec.PB( MP(x,i) );
}

int main() {
    scanf("%d", &n);
    REP(i,1,n) scanf("%d", di + i);
    int l = 1, r = n, sub = 0, pt = 1;
    while(l <= r) {
        if(l == r) {
            for(int i = 0; i < di[l]+1-sub; ++i)
                Add(pt+i, pt+i+1);
        }
        else {
            for(int i = 0; i < di[l]-sub; ++i)
                Add(pt+i, pt+i+1);
            pt += (di[r]-di[r-1]) + di[l] - sub;
            sub += di[l] - sub;
        }
        ++l, --r;
    }
    printf("%d\n", int(vec.size()));
    for(auto it : vec) printf("%d %d\n", it.fi, it.se);
    return 0;
}
