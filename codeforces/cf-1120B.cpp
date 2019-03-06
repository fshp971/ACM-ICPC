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

const int maxn = 1e5;

char s[maxn+5];
int n, a[maxn+5], b[maxn+5];
int hh[maxn+5];
LL cnt = 0;

vector<pair<int,int>> ans;

bool Chk() {
    int now = 0;
    for(int i = n; i >= 2; --i) {
        now = b[i]-a[i]-now;
        cnt += abs(now);
    }
    return a[1]+now==b[1];
}

void Insert(int p, int v) {
    ans.PB( MP(p,v) );
    if(ans.size() == maxn) {
        printf("%lld\n", cnt);
        for(int i = 0; i < ans.size(); ++i)
            printf("%d %d\n", ans[i].fi, ans[i].se);
        exit(0);
    }
}

int main() {
    scanf("%d", &n);

    scanf("%s", s+1);
    REP(i,1,n) a[i] = s[i]-'0';
    scanf("%s", s+1);
    REP(i,1,n) b[i] = s[i]-'0';

    if(!Chk()) exit( puts("-1")*0 );
    for(int i = n; i >= 2; --i) {
        if(a[i]==b[i]) continue;
        int p = i-1, v;
        if(a[i]<b[i]) v = 1;
        else v = -1;
        hh[p] = v;
        while(1) {
            if(a[p]+hh[p] > 9) {
                hh[p-1] = -hh[p];
                --p;
            }
            else if(a[p]+hh[p] < 0) {
                hh[p-1] = -hh[p];
                --p;
            }
            else break;
        }
        for(int k = p; k < i; ++k) {
            Insert(k, hh[k]);
            a[k] += hh[k], a[k+1] += hh[k];
        }
        ++i;
    }
    printf("%lld\n", cnt);
    for(int i = 0; i < ans.size(); ++i)
        printf("%d %d\n", ans[i].fi, ans[i].se);
    return 0;
}
