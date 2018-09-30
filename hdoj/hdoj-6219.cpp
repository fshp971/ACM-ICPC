#include <bits/stdc++.h>

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

const int maxn = 50;

struct Point {
    int x, y;
    Point() {}
    Point(int _x, int _y) : x(_x), y(_y) {}
    int operator * (const Point &a) { return x*a.x + y*a.y; }
    int operator ^ (const Point &a) { return x*a.y - y*a.x; }
    Point operator + (const Point &a) { return Point(x+a.x, y+a.y); }
    Point operator - (const Point &a) { return Point(x-a.x, y-a.y); }
    bool operator < (const Point &a) const { return (x==a.x) ? y<a.y : x<a.x; }
    void Input() { scanf("%d%d", &x, &y); }
} seg[maxn+5];

int n, num[maxn+5];
LL f1[maxn+5][maxn+5], f2[maxn+5][maxn+5];

bool cmp(const int &a, const int &b) {
    return ((seg[a]-seg[num[0]]) ^ (seg[b]-seg[num[0]])) > 0;
}

int dp[maxn+5][maxn+5], vis[maxn+5][maxn+5], T = 0;
int Run(int m) {
    ++T;
    for(int i = 1; i <= m; ++i) {
        dp[0][i] = 0, vis[0][i] = T;
        for(int k = 1; k < i; ++k) {
            for(int j = 0; j < k; ++j) {
                if(vis[j][k] != T) continue;
                if( ((seg[num[k]]-seg[num[j]]) ^ (seg[num[i]]-seg[num[j]])) <= 0 ) continue;
                if(j==0) {
                    if( (f1[num[i]][num[0]] & f1[num[0]][num[k]] & f1[num[k]][num[i]]) != 0 ) continue;
                }
                else {
                    if( (f1[num[i]][num[0]] & f2[num[0]][num[k]] & f1[num[k]][num[i]]) != 0 ) continue;
                }
                int sq = dp[j][k] + ((seg[num[k]]-seg[num[0]]) ^ (seg[num[i]]-seg[num[0]]));
                if(vis[k][i]!=T || dp[k][i] < sq) dp[k][i] = sq, vis[k][i] = T;
            }
        }
    }
    int ans = 0;
    REP(i,0,m) REP(k,i+1,m) if(vis[i][k]==T) ans = max(ans, dp[i][k]);
    return ans;
}

int main() {
    int _; scanf("%d", &_);
    while(_--) {
        scanf("%d", &n);
        REP(i,1,n) seg[i].Input();
        sort(seg+1, seg+1+n);
        REP(i,1,n) REP(k,1,n) {
            f1[i][k] = f2[i][k] = 0;
            REP(j,1,n) {
                int t = (seg[k]-seg[i]) ^ (seg[j]-seg[i]);
                if(t>0) f1[i][k] ^= 1LL<<j;
                if(t>=0) f2[i][k] ^= 1LL<<j;
            }
        }
        int ans = 0;
        REP(i,1,n-2) {
            num[0] = i;
            REP(k,i+1,n) num[k-i] = k;
            sort(num+1, num+1+n-i, cmp);
            ans = max(ans, Run(n-i));
        }
        printf("%.1f\n", double(ans)/2);
    }
    return 0;
}
