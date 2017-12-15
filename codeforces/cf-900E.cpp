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

const int maxn = 1e5;

int n, m;
int ff[maxn + 5], gg[maxn + 5];
int pp[maxn + 5], ww[maxn + 5];
char str[maxn + 5];

inline void Upd(int &f, int &g, int a, int b) {
    if(f < a) f = a, g = b;
    else if(f == a && g > b) g = b;
}

int main() {
    scanf("%d%s%d", &n, str + 1, &m);
    int tm = (m>>1)<<1;
    for(int i = 1; i <= n; ++i) {
        if(i >= 2 && (str[i-1]!='b' && str[i]!='a')) {
            pp[i] = pp[i-2] + 2;
            ww[i] = ww[i-2];
            if(str[i-1] == '?') ++ww[i];
            if(str[i] == '?') ++ww[i];
            if(pp[i] > tm) {
                pp[i] -= 2;
                if(str[i-tm-1] == '?') --ww[i];
                if(str[i-tm] == '?') --ww[i];
            }
        }
        ff[i] = ff[i-1], gg[i] = gg[i-1];
        if(m&1) {
            if(pp[i-1] == tm && str[i] != 'b') {
                int tmp = ww[i-1];
                if(str[i] == '?') ++tmp;
                Upd(ff[i], gg[i], ff[i-m] + 1, gg[i-m] + tmp);
            }
        }
        else {
            if(pp[i] == tm)
                Upd(ff[i], gg[i], ff[i-m] + 1, gg[i-m] + ww[i]);
        }
    }
    printf("%d\n", gg[n]);
    return 0;
}
