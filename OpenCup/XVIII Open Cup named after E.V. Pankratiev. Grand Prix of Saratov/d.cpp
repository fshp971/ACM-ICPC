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

int n, m;
int ti[maxn+5], ai[maxn+5];
int tti[maxn+5], aai[maxn+5];
bool inq[maxn+5];
LL f[maxn+5];
priority_queue<pair<LL,int>> q1, q2;
priority_queue<LL> q3;

// f[i] = \min_{0<=k<=i-1}{ \max{f[k],t[i]) + 2*a[k+1] }
int main() {
    while(~scanf("%d", &n)) {
        REP(i,1,n) scanf("%d%d", ti+i, ai+i);
        m = 0;
        REP(i,1,n) {
            while(m>0 && aai[m]<=ai[i]) --m;
            ++m, tti[m] = ti[i], aai[m] = ai[i];
        }
        while(!q1.empty()) q1.pop();
        while(!q2.empty()) q2.pop();
        while(!q3.empty()) q3.pop();
        REP(i,1,m) inq[i] = 0;
        q3.push(-aai[1]*2LL);
        REP(i,1,m) {
            while(!q1.empty() && -q1.top().fi<=tti[i]) {
                int x = q1.top().se; q1.pop();
                inq[x] = 0;
                q3.push(-aai[x+1]*2LL);
            }
            while(!q2.empty() && inq[q2.top().se]==0) q2.pop();
            f[i] = 1LL<<60;
            if(!q2.empty()) f[i] = min(f[i], -q2.top().fi);
            if(!q3.empty()) f[i] = min(f[i], tti[i] - q3.top());
            inq[i] = 1;
            q1.push( pair<LL,int>(-f[i],i) );
            q2.push( pair<LL,int>(-(f[i]+aai[i+1]*2LL),i) );
        }
        printf("%lld\n", f[m]);
    }
    return 0;
}
