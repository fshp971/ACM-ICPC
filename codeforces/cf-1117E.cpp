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

const int maxn = 1e4;

const int base[] = {1, 26, 26*26};
int n;
int f[maxn+5];
char s[maxn+5], t[maxn+5];

int main() {
    scanf("%s", s);
    n = strlen(s);
    for(int i = 0; i < 3; ++i) {
        int c = 0, cc = 0;
        for(int k = 0; k < n; ++k) {
            t[k] = c+'a';
            ++cc;
            if(cc == base[i]) c = (c+1)%26, cc = 0;
        }
        t[n] = '\0';
        printf("? %s\n", t);
        fflush(stdout);
        scanf("%s", t);
        for(int k = 0; k < n; ++k) f[k] += (t[k]-'a') * base[i];
    }
    for(int i = 0; i < n; ++i) {
        t[f[i]] = s[i];
    }
    t[n] = '\0';
    printf("! %s\n", t);
    fflush(stdout);
    return 0;
}
