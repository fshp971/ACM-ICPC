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

const int INF = 1<<30;
const int maxn = 10000;

struct Node {
    int a, b, c;
    Node() {}
    Node(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {}
    bool operator<(const Node &t) const {
        if(a!=t.a) return a<t.a;
        if(b!=t.b) return b<t.b;
        return c<t.c;
    }
};

int n, m, xi[maxn+5], ci[maxn+5];
int ss[3][maxn+5];

int GetMin(int *a, int ret, int len) {
    int l = 1, r = len;
    while(l <= r) {
        int mid = (l+r) >> 1;
        if(a[mid]-a[0] > 0) ret = mid, r = mid-1;
        else l = mid+1;
    }
    return ret;
}

int GetMax(int *a, int ret, int len) {
    int l = 1, r = len;
    while(l <= r) {
        int mid = (l+r) >> 1;
        if(a[len]-a[mid-1] > 0) ret = mid, l = mid+1;
        else r = mid-1;
    }
    return ret;
}

int main() {
    char str[10];
    int _; scanf("%d", &_);
    while(_--) {
        n = 0;
        scanf("%d", &m);
        REP(i,1,m) {
            scanf("%d%s", xi+i, str), ci[i] = str[0]-'A';
            n = max(n, xi[i]);
        }
        REP(i,1,n) ss[0][i] = ss[1][i] = ss[2][i] = 0;
        REP(i,1,m) ss[ci[i]][xi[i]] = 1;
        REP(i,1,n) {
            REP(k,0,2) ss[k][i] += ss[k][i-1];
        }
        Node ans = Node(INF,INF,INF);
        for(int len = 3; len <= n; ++len) {
            int maxa = 1, minb = len-1, maxb = 2, minc = len;
            for(int i = 0; i+1 <= n; i += len) {
                maxa = max( maxa, GetMax(ss[0]+i, 0, min(len,n-i)) );
                minb = min( minb, GetMin(ss[1]+i, len+1, min(len,n-i)) );
                maxb = max( maxb, GetMax(ss[1]+i, 0, min(len,n-i)) );
                minc = min( minc, GetMin(ss[2]+i, len+1, min(len,n-i)) );
            }
            if(maxa>=minb || maxb>=minc) continue;
            Node tmp = Node(maxa, maxb-maxa, len-maxb);
            if(tmp < ans) ans = tmp;
        }
        if(ans.a == INF) puts("NO");
        else printf("%d %d %d\n", ans.a, ans.b, ans.c);
    }
    return 0;
}
