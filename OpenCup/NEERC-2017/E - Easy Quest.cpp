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

const int maxn = 1000;

int n, uni = 0;
int cnt[maxn + 5];
int tot = 0, sta[maxn + 5];

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        int u;
        scanf("%d", &u);
        if(u > 0) ++cnt[u];
        else if(u == 0) ++uni;
        else {
            if(cnt[-u]) --cnt[-u];
            else if(tot < uni) sta[++tot] = -u;
            else { puts("No"); return 0; }
        }
    }
    while(tot < uni) sta[++tot] = 1;
    puts("Yes");
    for(int i = 1; i <= tot; ++i) {
        if(i > 1) printf(" ");
        printf("%d", sta[i]);
    }
    printf("\n");
    return 0;
}
