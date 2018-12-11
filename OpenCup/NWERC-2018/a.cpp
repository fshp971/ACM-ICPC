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
typedef double DB;

const int maxn = 1e5;

struct Node {
    int c;
    LL sx, sa;
    Node() {}
} sta[maxn+5];

int n;
int si[maxn+5], ti[maxn+5];

DB Run(int *xi) {
    int top = 1;
    sta[1].c = 1;
    sta[1].sx = xi[1];
    sta[1].sa = LL(xi[1])*xi[1];
    for(int i = 2; i <= n; ++i) {
        ++top;
        sta[top].c = 1;
        sta[top].sx = xi[i];
        sta[top].sa = LL(xi[i])*xi[i];
        while(top>=2 && sta[top-1].sx*sta[top].c > sta[top].sx*sta[top-1].c) {
            sta[top-1].c += sta[top].c;
            sta[top-1].sx += sta[top].sx;
            sta[top-1].sa += sta[top].sa;
            --top;
        }
    }
    DB res = 0;
    while(top) {
        res += sta[top].sa - DB(sta[top].sx) / sta[top].c * sta[top].sx;
        --top;
    }
    return res;
}

int main() {
    scanf("%d", &n);
    REP(i,1,n) scanf("%d%d", si+i, ti+i);
    DB ans = Run(si) + Run(ti);
    printf("%.10f\n", ans);
    return 0;
}
