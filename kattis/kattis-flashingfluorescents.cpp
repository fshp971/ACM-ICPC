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

const int maxk = 16, maxn = 1 << maxk;
const int Step = 50;

int ini = 0, kk;
bool f[Step + 5][maxn + 5];
queue<int> que;

char str[100];
int main() {
    scanf("%s", str);
    kk = strlen(str);
    for(int i = 0; i < kk; ++i)
        ini |= (str[i] - '0') << i;
    if(ini == (1 << kk)-1) exit( puts("0") * 0 );
    f[0][ini] = 1;
    for(int i = 1; i <= Step; ++i) {
        for(int k = 0; k < (1<<kk); ++k) f[i][k] = f[i-1][k];
        for(int k = 0; k < kk; ++k) {
            int tmp = 0;
            for(int j = 0; j < i && j+k < kk; ++j) tmp |= 1 << (j+k);
            for(int j = 0; j < (1<<kk); ++j) f[i][j] |= f[i-1][j^tmp];
        }
        if(f[i][(1<<kk)-1]) exit( printf("%d\n", i) * 0 );
    }
    assert(false);
    return 0;
}
