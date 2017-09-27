#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 3000;

int n;
int f[maxn + 5], pre[maxn + 5];
char str[maxn + 5];

int main() {
    scanf("%s", str + 1);
    n = strlen(str + 1);
    mem(f, 0x7f), f[0] = -1;
    for(int i = 1; i <= n; ++i) {
        int len = 0, diff = 0;
        for(int k = i; k > 0; --k) {
            if(str[k] == 'a' || str[k] == 'e' || str[k] == 'i' || str[k] == 'o' || str[k] == 'u')
                len = 0, diff = 0;
            else {
                ++len;
                if(len > 1 && str[k] != str[k + 1])
                    diff = 1;
            }
            if(len >= 3 && diff) break;
            if(f[i] > f[k-1] + 1)
                f[i] = f[k-1] + 1, pre[i] = k;
        }
    }
    vector<pii> sta;
    int pif = 0, pt = n;
    while(pt > 0) {
        sta.PB(MP(pre[pt], pt));
        pt = pre[pt] - 1;
    }
    for(int i = sta.size() - 1; i >= 0; --i) {
        if(pif) printf(" ");
        pif = 1;
        for(int k = sta[i].first; k <= sta[i].second; ++k)
            printf("%c", str[k]);
    }
    printf("\n");
    return 0;
}
