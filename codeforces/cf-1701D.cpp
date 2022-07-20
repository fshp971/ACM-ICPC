#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define PER(i,a,b) for(int i = a; i >= b; --i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef long double LD;

const int maxn = 5e5;

int n;
vector<int> ans(maxn+5);
vector<vector<pair<int,int>>> ss(maxn+5);

int find(int ii, int bb) {
    int l = 1, r = n, res = 0;
    while(l <= r) {
        int mid = (l+r) >> 1;
        if(ii / mid > bb) res = mid, l = mid+1;
        else r = mid-1;
    }
    return res+1;
}

int main() {
    int _; scanf("%d", &_);
    while(_--) {
        scanf("%d", &n);
        REP(i,1,n) ss[i].clear();
        for(int i = 1, b; i <= n; ++i) {
            scanf("%d", &b);
            if(b == 0)
                ss[i+1].PB(MP(n,i));
            else {
                int a = find(i,b);
                ss[a].PB(MP(i/(i/a),i));
            }
        }
        priority_queue<pair<int,int>> q;
        for(int i = 1; i <= n; ++i) {
            for(auto pp : ss[i])
                q.push( MP(-pp.fi, pp.se) );
            ans[q.top().se] = i;
            q.pop();
        }
        REP(i,1,n) printf("%d%c", ans[i], (i==n)?'\n':' ');
    }
    return 0;
}
