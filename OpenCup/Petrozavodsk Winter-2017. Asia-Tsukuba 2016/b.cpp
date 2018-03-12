#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
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

int mmp[10][10];
int num[5];

bool Chk() {
    int r = 0;
    for(int i = 4; i >= 0; --i) r = mmp[r][num[i]];
    return r == 0;
}

int dirty(int x) {
    for(int i = 1; i <= 4; ++i) num[i] = x%10, x /= 10;
    num[0] = 0;
    for(int i = 4; i >= 1; --i) num[0] = mmp[num[0]][num[i]];
    for(int i = 0; i <= 3; ++i) {
        if(num[i] == num[i+1]) continue;
        swap(num[i],num[i+1]);
        if(Chk()) return 1;
        swap(num[i],num[i+1]);
    }
    for(int i = 0; i <= 4; ++i) {
        int t = num[i];
        for(int k = 0; k <= 9; ++k) {
            if(k == t) continue;
            num[i] = k;
            if(Chk()) return 1;
        }
        num[i] = t;
    }
    return 0;
}

int main() {
    //freopen("in.txt", "r", stdin);
    REP(i,0,9) REP(k,0,9) scanf("%d", &mmp[i][k]);
    int ans = 0;
    for(int i = 0; i <= 9999; ++i) ans += dirty(i);
    printf("%d\n", ans);
    return 0;
}
