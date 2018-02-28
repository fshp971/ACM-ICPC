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

const int maxn = 3e5;

int vist[maxn + 5];
vector<pii> deco[maxn + 5];
void GetPrime() {
    for(int i = 2; i <= maxn; ++i)
        if(!vist[i]) {
            for(int k = i; k <= maxn; k += i) {
                int tmp = k, tt = 0;
                while(tmp%i == 0) tmp /= i, ++tt;
                deco[k].PB( MP(i,tt) ), vist[k] = 1;
            }
            vist[i] = 0;
        }
}

int Calc(int x) {
    int ret = 1;
    for(auto it : deco[x]) ret *= (it.se + 1);
    return ret - 1;
}

bool dead[maxn + 5];
int main() {
    GetPrime();
    int n, kk;
    scanf("%d%d", &n, &kk);
    int sum = 0, m = 0;
    while(sum < kk && m < n)
        sum += Calc(++m);
    if(sum < kk) { puts("No"); exit(0); }
    int all = m;
    if(m <= 120) {
        for(int i = 2; i <= (m>>1); ++i) {
            int t = Calc(i) + m/i - 1;
            if(sum - t >= kk) { dead[i] = 1, --all, sum -= t; break; }
        }
    }
    for(int i = (m>>1) + 1; i <= m && sum > kk; ++i) {
        if(!vist[i]) dead[i] = 1, --sum, --all;
    }
    puts("Yes");
    printf("%d\n", all);
    for(int i = 1; all; ++i)
        if(!dead[i])
            printf("%d%c", i, (--all) ? ' ' : '\n');
    return 0;
}
