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
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e5;
const int maxk = 1 << 6;

char str[maxn + 5];
int n, seg[maxn + 5];
int cnt[10], B[maxk + 5];

bool Chk() {
    for(int i = 0; i < (1<<6); ++i) {
        int tmp1 = 0, tmp2 = 0;
        for(int k = 0; k < 6; ++k)
            if(i>>k&1) tmp1 += cnt[k];
        for(int k = 0; k < (1<<6); ++k)
            if(i&k) tmp2 += B[k];
        if(tmp1 > tmp2) return false;
    }
    return true;
}

int main() {
    scanf("%s", str), n = strlen(str), B[(1<<6)-1] = n;
    for(int i = 0; i < n; ++i) ++cnt[str[i]-'a'], seg[i] = (1<<6) - 1;
    int _, __; scanf("%d", &_);
    while(_--) {
        int ps, msk = 0;
        scanf("%d%s", &ps, str), --ps;
        --B[(1<<6)-1];
        for(int i = 0; str[i] != '\0'; ++i)
            msk |= 1 << (str[i]-'a');
        ++B[msk], seg[ps] = msk;
    }
    for(int i = 0; i < n; ++i) {
        int fg = 0;
        --B[ seg[i] ];
        for(int k = 0; k < 6 && !fg; ++k) {
            if( !(seg[i]>>k&1) ) continue;
            --cnt[k];
            if(Chk()) fg = 1, str[i] = k+'a';
            else ++cnt[k];
        }
        if(!fg) exit( puts("Impossible")*0 );
    }
    str[n] = '\0';
    printf("%s\n", str);
    return 0;
}
