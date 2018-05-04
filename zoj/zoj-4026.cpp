#include <bits/stdc++.h>

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

LL Gcd(LL a, LL b) { return b ? Gcd(b,a%b) : a; }

struct Frac {
    LL a, b; // a/b
    Frac() {}
    Frac(LL _a, LL _b) : a(_a), b(_b) { GG(); }
    void GG() {
        LL g = Gcd(a,b);
        a /= g, b /= g;
    }
    Frac operator+(const Frac &r) { return Frac(a*(r.b) + (r.a)*b, b*(r.b)); }
    Frac operator*(const Frac &r) { return Frac(a*(r.a), b*(r.b)); }
    void operator+=(const Frac &r) { (*this) = (*this) + r; }
    void Print() {
        if(a == 0) printf("0");
        else if(a == 1 && b == 1) printf("1");
        else printf("%lld/%lld", a, b);
    }
};

Frac f[5][12][12][12][12][5];
bool vist[5][12][12][12][12][5];

Frac dfs(int c0, int c1, int c2, int c3, int c4, int c5) {
    Frac &res = f[c0][c1][c2][c3][c4][c5];
    bool &vi = vist[c0][c1][c2][c3][c4][c5];
    if(vi) return res;
    vi = 1;
    if(c0 == 0) return res = c5 ? Frac(0,1) : Frac(1,1);
    int rem = c0+c1+c2+c3+c4+c5;
    res = Frac(0,1);
    if(c0) res += dfs(c0-1, c1, c2, c3, c4, c5) * Frac(c0, rem);
    if(c1) res += dfs(c0, c1-1, c2, c3, c4, c5) * Frac(c1, rem);
    if(c2) res += dfs(c0, c1+1, c2-1, c3, c4, c5) * Frac(c2, rem);
    if(c3) res += dfs(c0, c1, c2+1, c3-1, c4, c5) * Frac(c3, rem);
    if(c4) res += dfs(c0, c1, c2, c3+1, c4-1, c5) * Frac(c4, rem);
    if(c5) res += dfs(c0, c1, c2, c3, c4, c5-1) * Frac(c5, rem);
    return res;
}

int GetNum(char *s) {
    if(s[0] == 'A') return 1;
    if(s[0] == 'J') return 11;
    if(s[0] == 'Q') return 12;
    if(s[0] == '1') return 10;
    return s[0] - '0';
}

int n, cnt[15];
int main() {
    dfs(4, 0, 0, 0, 10, 4);
    int T, a;
    char str[10];
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        REP(i,1,12) cnt[i] = 4;
        for(int i = 1; i <= n; ++i)
            scanf("%s", str), --cnt[ GetNum(str) ];
        int c[5]; mem(c,0); c[0] = cnt[1];
        for(int i = 2; i <= 12; ++i) if(cnt[i]) ++c[cnt[i]];
        printf("1");
        for(int i = 2; i <= 12; ++i) {
            Frac res;
            if(cnt[i] == 1) res = f[c[0]][c[1]-1][c[2]][c[3]][c[4]][1];
            else if(cnt[i] == 2) res = f[c[0]][c[1]][c[2]-1][c[3]][c[4]][2];
            else if(cnt[i] == 3) res = f[c[0]][c[1]][c[2]][c[3]-1][c[4]][3];
            else if(cnt[i] == 4) res = f[c[0]][c[1]][c[2]][c[3]][c[4]-1][4];
            else res = f[c[0]][c[1]][c[2]][c[3]][c[4]][0];
            printf(" ");
            res.Print();
        }
        puts("");
    }
    return 0;
}
