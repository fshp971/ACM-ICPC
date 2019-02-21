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
typedef pair<int,int> pii;

const int maxk = 12;
const int maxn = 1<<maxk;
const int maxe = 2e5;

int li[maxk+5];
int h[maxn+5], e[maxe+5], nx[maxe+5], tot;
int cnt[maxn+5], cho[maxn+5];
int bt[maxn+5];
vector<int> vec[maxn+5];

inline void Add(int x, int v) {
    e[++tot] = v, nx[tot] = h[x], h[x] = tot;
}

int main() {
    for(int i = 1; i <= maxn; ++i) bt[i] = bt[i>>1]+(i&1);
    for(int i = 0; i < (1<<12); ++i) {
        for(int k = 0; k < 12; ++k)
            if(i>>k&1) vec[i].PB(1<<k);
    }
    int __; scanf("%d", &__);
    for(int _ = 1; _ <= __; ++_) {
        REP(i,0,11) scanf("%d", li+i);
        sort(li, li+12);
        REP(i,0,(1<<12)-1) h[i] = 0;
        tot = 0;
        REP(i,0,11) REP(k,i+1,11) REP(j,k+1,11) {
            if(li[i]+li[k]<=li[j]) continue;
            int msk = (1<<i) + (1<<k) + (1<<j);
            int rem = ((1<<12)-1) ^ msk;
            for(int p = rem; p > 0; p = (p-1)&rem)
                Add(p|msk, msk);
            Add(msk,msk);
        }
        int ans = 0, val = 0;
        for(int i = 1; i < (1<<12); ++i) {
            cnt[i] = 0, cho[i] = 0;
            for(int k = h[i]; k; k = nx[k]) {
                if(cnt[i] == bt[i]/3) break;
                if(cnt[i^e[k]]+1 > cnt[i]) {
                    cnt[i] = cnt[i^e[k]]+1;
                    cho[i] = e[k];
                }
            }
            for(auto x : vec[i]) {
                if(cnt[i] == bt[i]/3) break;
                if(cnt[i^x] > cnt[i]) {
                    cnt[i] = cnt[i^x];
                    cho[i] = x;
                }
            }
            if(ans < cnt[i]) {
                ans = cnt[i], val = i;
            }
        }
        printf("Case #%d: %d\n", _, ans);
        while(val) {
            if(bt[cho[val]]==3) {
                int fg = 0;
                REP(i,0,11) {
                    if(cho[val]>>i&1) {
                        if(fg) printf(" ");
                        printf("%d", li[i]);
                        fg = 1;
                    }
                }
                puts("");
            }
            val ^= cho[val];
        }
    }
    return 0;
}
