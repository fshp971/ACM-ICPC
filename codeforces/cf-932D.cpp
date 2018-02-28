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

const int maxn = 400000;
const int MaxStep = 19;

int n, st1[maxn + 5][MaxStep + 2], mx[maxn + 5][MaxStep + 2];
int st2[maxn + 5][MaxStep + 2];
LL sum[maxn + 5][MaxStep + 2];

int main() {
    mem(st1, -1); mem(st2, -1);
    n = 1, st1[1][0] = st2[1][0] = 0;
    int T, o;
    LL last = 0, p, q;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%lld%lld", &o, &p, &q);
        p ^= last, q ^= last;
        if(o == 1) {
            ++n, st1[n][0] = p, mx[n][0] = q;
            for(int i = 0; st1[n][i] > 0; ++i) {
                st1[n][i+1] = st1[st1[n][i]][i];
                mx[n][i+1] = max(mx[n][i], mx[st1[n][i]][i]);
            }
            int ps = p;
            for(int i = MaxStep; i >= 0; --i)
                if(st1[ps][i] != -1 && mx[ps][i] < q)
                    ps = st1[ps][i];
            st2[n][0] = ps, sum[n][0] = q;
            for(int i = 0; st2[n][i] > 0; ++i) {
                st2[n][i+1] = st2[st2[n][i]][i];
                sum[n][i+1] = sum[n][i] + sum[st2[n][i]][i];
            }
        }
        else {
            last = 0;
            for(int i = MaxStep; i >= 0; --i) {
                if(st2[p][i] != -1 && sum[p][i] <= q)
                    q -= sum[p][i], p = st2[p][i], last |= (1LL << i);
            }
            printf("%lld\n", last);
        }
    }
    return 0;
}
