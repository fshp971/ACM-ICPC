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

const int maxn = 1e6;

int n;
char str[maxn + 5];
int main() {
    scanf("%s", str + 1);
    n = strlen(str + 1);
    int l = 1, r = n;
    while(l <= n && str[l] == 'L') ++l;
    while(r >= 1 && str[r] == 'R') --r;
    int t = r - l + 1;
    printf("%d\n", n - t + ((t>0) ? 1 : 0));
    return 0;
}
