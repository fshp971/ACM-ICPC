#include<bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define FOR(i,a,b) for(int i = a; i < b; ++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int md = 1e9 + 7;
const int base = 2097152;
const int maxm = base * 8;

int dest, ans, T;
char f[maxm + 5], vist[maxm + 5];

inline int GetHash(char *a, int &len, int pt) {
    int res = 0;
    for(int i = 0; i < len; ++i)
        res = res * 8 + a[i] - 'a' + 1;
    return pt * base + res;
}

void dfs(char *a, int len, int pt, int dis) {
    int haha = GetHash(a,len,pt);
    if(haha % base == dest) { ans = dis; return; }
    if(vist[haha] == T && f[haha] <= dis) return;
    vist[haha] = T, f[haha] = dis;
    if(pt > 0 && dis + 1 < ans) dfs(a, len, pt - 1, dis + 1);
    if(pt < len && dis + 1 < ans) dfs(a, len, pt + 1, dis + 1);
    if(len > 0) {
        if(pt - 1 >= 0 && dis + 2 < ans) {
            char c = a[pt - 1];
            for(int i = pt - 1; i < len; ++i)
                a[i] = a[i + 1];
            --len;
            dfs(a, len, pt - 1, dis + 2);
            for(int i = len + 1; i >= pt; --i)
                a[i] = a[i - 1];
            ++len, a[pt - 1] = c;
        }
        if(pt < len && dis + 2 < ans) {
            char c = a[pt];
            for(int i = pt; i < len; ++i)
                a[i] = a[i + 1];
            --len;
            dfs(a, len, pt, dis + 2);
            for(int i = len + 1; i >= pt + 1; --i)
                a[i] = a[i - 1];
            ++len, a[pt] = c;
        }
    }
    if(len < 7) {
        bool ffg[8];
        mem(ffg, 0);
        for(int i = 0; i < len; ++i)
            ffg[a[i] - 'a'] = 1;
        for(int i = len + 1; i >= pt + 1; --i)
            a[i] = a[i - 1];
        ++len;
        for(int k = 0; k < 7 && dis + 2 < ans; ++k)
            if(!ffg[k]) {
                a[pt] = k + 'a';
                dfs(a, len, pt + 1, dis + 2);
            }
        for(int i = pt; i < len; ++i)
            a[i] = a[i + 1];
        --len;
    }
}

int main() {
    int pt, len;
    char a[10], b[10];
    bool ffg[8];
    T = 0;
    while(~scanf("%s%d%s", a, &pt, b)) {
        ++T;
        len = strlen(b);
        mem(ffg, 0);
        bool hh = true;
        for(int i = 0; i < len; ++i) {
            if(ffg[b[i] - 'a']) { hh = false; break; }
            ffg[b[i] - 'a'] = 1;
        }
        if(!hh) { printf("-1\n"); continue; }
        dest = GetHash(b, len, 0);
        ans = len;
        len = strlen(a);
        ans += len;
        ans *= 2;
        dfs(a, len, pt, 0);
        printf("%.1f\n", ans/2.0);
    }
    return 0;
}
