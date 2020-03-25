#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define PER(i,a,b) for(int i = a; i >= b; --i)
#define PB push_back
#define MP make_pair
#define fi first
#define se second
typedef long long LL;
typedef double DB;

const int maxn = 4e5;
const int maxk = 24;

int n;
int ai[maxn+5];
int L1[maxn+5], R1[maxn+5], L2[maxn+5], R2[maxn+5];
int vec[maxn+5];

int main() {
    int ans = 0;
    scanf("%d", &n);
    REP(i,1,n) scanf("%d", ai+i);
    for(int k = 0, msk = 1; k <= maxk; ++k, msk=(msk<<1)+1) {
        REP(i,0,n-1) vec[i] = ai[i+1]&msk;
        sort(vec, vec+n);
        int l1 = (1<<(k+1)) + (1<<k), r1 = (1<<(k+2)) - 2;
        int l2 = (1<<k), r2 = (1<<(k+1)) - 1;
        for(int i=n-1, p1=0, p2=0; i >= 0; --i) {
            while(p1<n && vec[p1]+vec[i]<l1) ++p1;
            while(p2<n && vec[p2]+vec[i]<l2) ++p2;
            L1[i] = min(p1, i);
            L2[i] = min(p2, i);
        }
        for(int i=0, p1=n-1, p2=n-1; i < n; ++i) {
            while(p1>=0 && vec[p1]+vec[i]>r1) --p1;
            while(p2>=0 && vec[p2]+vec[i]>r2) --p2;
            R1[i] = min(p1, i-1);
            R2[i] = min(p2, i-1);
        }
        int sum = 0;
        for(int i = 0; i < n; ++i)
            sum ^= ((R1[i]-L1[i]+1)&1) ^ ((R2[i]-L2[i]+1)&1);
        if(sum) ans ^= (1<<k);
    }
    printf("%d\n", ans);
    return 0;
}
