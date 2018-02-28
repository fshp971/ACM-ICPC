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

const int maxn = 1e5, c_sz = 26;

bitset<100000> f[c_sz], ini, ans;
int n;
char str[maxn + 5], buf[maxn + 5];

int main() {
    scanf("%s", str), n = strlen(str);
    for(int i = 0; i < n; ++i) f[str[i]-'a'][i] = 1, ini[i] = 1;
    int T, ord, l, r, len;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &ord);
        if(ord == 1) {
            scanf("%d%s", &l, buf), --l;
            f[str[l]-'a'][l] = 0, str[l] = buf[0], f[str[l]-'a'][l] = 1;
        }
        else {
            scanf("%d%d%s", &l, &r, buf), --l, --r;
            len = strlen(buf);
            if(r-l+1 < len) { puts("0"); continue; } //别去写未定义行为就是了...
            ans = ini;
            for(int i = 0; i < len; ++i)
                ans &= (f[buf[i]-'a'] >> i);
            printf("%d\n", int( (ans>>l).count() - (ans>>(r-len+2)).count() ) );
        }
    }
    return 0;
}
