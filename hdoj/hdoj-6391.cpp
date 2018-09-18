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

const int P = 19260817;

int n, kk;
LL C[50][50], inv[50];
LL f[50][50];
char s1[50], s2[50];

int main() {
    C[0][0] = 1;
    REP(i,1,45) {
        C[i][0] = C[i][i] = 1;
        REP(j,1,i-1) C[i][j] = (C[i-1][j] + C[i-1][j-1]) % P;
    }
    inv[1] = 1;
    REP(i,2,45) inv[i] = LL(P - P/i) * inv[P%i] % P;
    int _ = 0;
    while(scanf("%d%d", &n, &kk), n) {
        scanf("%s%s", s1, s2);
        int cnt = 0;
        REP(i,0,n-1) cnt += (s1[i]-'0') ^ (s2[i]-'0');
        f[0][0] = 1;
        REP(i,1,kk) {
            REP(j,0,n) {
                f[i][j] = 0;
                if(j>=3) f[i][j] = (f[i][j] + C[j][3] * f[i-1][j-3]) % P;
                if(j-1>=0) f[i][j] = (f[i][j] + C[n-j][1]*C[j][2]%P*f[i-1][j-1]) % P;
                if(j+1<=n) f[i][j] = (f[i][j] + C[n-j][2]*C[j][1]%P*f[i-1][j+1]) % P;
                if(j+3<=n) f[i][j] = (f[i][j] + C[n-j][3] * f[i-1][j+3]) % P;
                if(i>=2) {
                    LL tmp = (C[n][3] - (i-2) + P) % P * f[i-2][j] % P;
                    f[i][j] = (f[i][j] - tmp + P) % P;
                }
                f[i][j] = f[i][j] * inv[i] % P;
            }
        }
        printf("Case #%d: %lld\n", ++_, f[kk][cnt]);
    }
    return 0;
}
