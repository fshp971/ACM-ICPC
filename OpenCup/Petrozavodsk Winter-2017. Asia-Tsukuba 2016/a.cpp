#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
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

const int maxn = 2e5;

int Q[maxn + 5];
vector<int> ans;
bool vist[maxn + 5];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    REP(i,1,m) scanf("%d", Q + i);
    for(int i = m; i >= 1; --i) {
        if(vist[Q[i]]) continue;
        vist[Q[i]] = 1;
        ans.PB(Q[i]);
    }
    for(int i = 1; i <= n; ++i) {
        if(vist[i]) continue;
        ans.PB(i);
    }
    for(auto it : ans) printf("%d\n", it);
    return 0;
}
