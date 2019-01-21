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

const int maxn = 200;
const int INF = int(1e9) + 10;

int n, m, kk;
int seg[maxn*2+5], num[maxn*2+5];
int ans[maxn*2+5];
bool vi[maxn*2+5];
char mmp[maxn+5][maxn+5];

inline void Add(int &a, int b) { a+=b; if(a>INF) a=INF; }

int f[2][maxn*2+5];
LL Run() {
    int par = 0;
    f[par][0] = 1;
    for(int i = 1; i <= n+m-1; ++i) {
        for(int k = 0; k <= i; ++k) f[par^1][k] = 0;
        for(int k = 0; k <= (i-1); ++k) {
            if(vi[i]) {
                if(k+ans[i]>=0) Add(f[par^1][k+ans[i]], f[par][k]);
            }
            else {
                Add(f[par^1][k+1], f[par][k]);
                if(k-1>=0) Add(f[par^1][k-1], f[par][k]);
            }
        }
        par^=1;
    }
    return f[par][0];
}

int main() {
    mem(seg,0x7f);
    scanf("%d%d%d", &n, &m, &kk);
    REP(i,1,n) REP(k,1,m) {
        int v; scanf("%d", &v);
        int x = i, y = k;
        while(x<n && y>1) ++x, --y;
        if(y==1) seg[x] = min(seg[x], v);
        else seg[n+y-1] = min(seg[n+y-1], v);
    }
    REP(i,1,n+m-1) num[i] = i;
    sort(num+1, num+1+n+m-1, [&](int a,int b){return seg[a]<seg[b];});
    for(int i = 1; i <= n+m-1; ++i) {
        int x = num[i];
        vi[x] = 1, ans[x] = 1;
        int tmp = Run();
        if(kk > tmp) kk -= tmp, ans[x] = -1;
    }
    for(int i = 1; i <= n+m-1; ++i) {
        int x, y;
        char c = (ans[i]==1) ? '(' : ')';
        if(i<=n) x = i, y = 1;
        else x = n, y = i-n+1;
        while(x>=1 && y<=m) {
            mmp[x][y] = c;
            --x, ++y;
        }
    }
    REP(i,1,n) {
        mmp[i][m+1] = '\0';
        printf("%s\n", mmp[i]+1);
    }
    return 0;
}
