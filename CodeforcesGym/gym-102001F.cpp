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

const int maxn = 1e5;

int n, M;
int ai[maxn+5], bi[maxn+5];
LL si[maxn+5];
priority_queue<pii> q;
vector<int> ans;

int main() {
    scanf("%d%d", &n, &M);
    REP(i,1,n) scanf("%d", ai+i);
    REP(i,1,n) scanf("%d", bi+i);

    {
        int tn = 0, sum = 0;
        while(tn+1<=n && sum+ai[tn+1]<=M) sum+=ai[++tn];
        n = tn;
    }

    REP(i,1,n) q.push( pii(bi[i],-i) ), si[i] = si[i-1] + bi[i];
    int id1 = 0, id2 = 0, ci = 0;
    LL del = 0, ti = 0;
    while(ti!=M) {
        while(!q.empty() && -q.top().se<=id2) q.pop();
        if(q.empty()) break;
        int x = -q.top().se; q.pop();
        if(ti + si[x]-si[id2] > M) continue;
        del += si[x]-si[id2];
        ti += si[x]-si[id2];
        id2 = x-1;
        while(id1+1<=n && ai[id1+1]<=del) {
            ++id1, del-=ai[id1], ++ci;
        }
        if(ci) {
            ans.PB(ti); --ci; q.push( pii(bi[x],-x) );
        }
        else {
            id2 = x;
        }
    }
    if(id2==n) puts("-1");
    else {
        printf("%d\n", int(ans.size()) );
        for(int i = 0; i < ans.size(); ++i)
            printf("%d%c", ans[i], (i+1==ans.size())?'\n':' ');
    }
    return 0;
}
