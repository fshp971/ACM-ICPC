#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cassert>
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

const int maxn = 1600000; // maxn > 3^13

int n, kk, f[maxn + 5], cnt[maxn + 5], base[20];

int main() {
    //freopen("in.txt", "r", stdin);
    base[0] = 1;
    for(int i = 1; i <= 15; ++i) base[i] = base[i-1] * 3;
    int T;
    char str[20];
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &kk);
        mem(f, 0), mem(cnt, 0);
        REP(i,1,n) {
            scanf("%s", str);
            int t = 0;
            for(int k = 0; k < kk; ++k)
                t += (str[k]-'0') * base[k];
            cnt[t] = 1;
        }
        for(int i = 0; i < base[kk]; ++i) {
            for(int k = 0; k < kk; ++k) {
                if(i/base[k]%3 == 2) {
                    cnt[i] = cnt[i-base[k]] + cnt[i-base[k]*2];
                    break;
                }
            }
        }
        for(int i = 0; i < base[kk]; ++i) {
            if(cnt[i] <= 1) continue;
            f[i] = kk;
            for(int k = 0; k < kk; ++k) {
                if(i/base[k]%3 != 2) continue;
                f[i] = min(f[i], max(f[i-base[k]], f[i-base[k]*2]));
            }
            ++f[i];
        }
        printf("%d\n", f[base[kk]-1]);
    }
    return 0;
}
