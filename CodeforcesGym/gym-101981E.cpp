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
typedef pair<int,int> pii;

const int maxn = 1e6;

int n, kk;
char s1[maxn+5], s2[maxn+5];
char d1[maxn+5], d2[maxn+5];

int ch[maxn+5], nu[maxn+5];
void Work(char *a, char *b) {
    int top = 0, all = 0;
    REP(i,1,n) {
        int c = a[i]-'0';
        if(top && ch[top]==c) ++nu[top];
        else ++top, ch[top] = c, nu[top] = 1;
        if(nu[top] == kk) {
            REP(k,1,kk) b[++all] = '0';
            --top;
        }
    }
    REP(i,1,top) {
        REP(k,1,nu[i]) b[++all] = ch[i]+'0';
    }
}

int main() {
    scanf("%d%d", &n, &kk);
    scanf("%s%s", s1+1, s2+1);
    Work(s1,d1), Work(s2,d2);
    REP(i,1,n) if(d1[i]!=d2[i]) exit( puts("No")*0 );
    puts("Yes");
    return 0;
}
