#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 5000;

int n;
LL sum[maxn + 5], f1[maxn + 5], f2[maxn + 5];
int md1[maxn + 5], md2[maxn + 5];

inline LL S(int l, int r) { return sum[r-1] - sum[l-1]; }

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%lld", sum + i), sum[i] += sum[i-1];
    mem(f1, 0x80), mem(f2, 0x80);
    for(int i = 1; i <= n; ++i) {
        for(int k = 1; k <= i; ++k) {
            LL tmp = S(1,k) - S(k,i);
            if(tmp > f1[i]) f1[i] = tmp, md1[i] = k;
        }
        for(int k = i; k <= n + 1; ++k) {
            LL tmp = S(i,k) - S(k,n+1);
            if(tmp > f2[i]) f2[i] = tmp, md2[i] = k;
        }
    }
    int pt = 0;
    LL ans = -(1LL << 60);
    for(int i = 1; i <= n; ++i)
        if(ans < f1[i] + f2[i])
            ans = f1[i] + f2[i], pt = i;
    printf("%d %d %d\n", md1[pt] - 1, pt - 1, md2[pt] - 1);
    return 0;
}
