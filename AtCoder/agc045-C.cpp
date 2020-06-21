#include <bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define PER(i,a,b) for(int i = a; i >= b; --i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef long double LD;

const int maxn = 5000;
const int P = 1e9+7;

void Add(int &a, int b) { a+=b; if(a>=P) a-=P; }
void Sub(int &a, int b) { a-=b; if(a<0) a+=P; }
LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%P; a=a*a%P, b>>=1; } return r; }

int n, A, B;
int f[maxn+5][maxn+5][2], ss[maxn+5];
int two[maxn+5];

int main() {
    two[0] = 1;
    REP(i,1,maxn) two[i] = two[i-1]*2 % P; 

    scanf("%d%d%d", &n, &A, &B);
    if(A>B) swap(A,B);

    f[0][1][0] = f[0][1][1] = 1;
    ss[0] = 1;
    int ans = 0;
    for(int i = 1; i <= n; ++i) {
        ss[i] = ss[i-1];
        for(int t = 1; t <= i; ++t) {
            int tmp = f[i-1][t][0];
            if(i-t+1 >= B) {
                if(i < n) tmp = LL(tmp) * two[n-i-1] % P;
                Add(ans, tmp);
            }
            else {
                f[i][t][1] = tmp;
                Add(ss[i], f[i][t][1]);
            }
            Add(f[i][t][1], f[i-1][t][1]);
        }

        Add(f[i][i+1][0], ss[i-1]);
        if(i-A >= 0) Sub(f[i][i+1][0], ss[i-A]);

        for(int t = 1; t <= i; ++t) {
            int tmp = 0;
            if(i-A >= 0) tmp = f[i-A][t][1];
            if(i-t+1 >= B) {
                if(i < n) tmp = LL(tmp) * two[n-i-1] % P;
                Add(ans, tmp);
            }
            else {
                f[i][t][0] = tmp;
            }
            Add(f[i][t][0], f[i-1][t][0]);
        }
    }
    printf("%d\n", ans);
    return 0;
}
