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

LL Gcd(LL a, LL b) { return b ? Gcd(b,a%b) : a; }

int main() {
    int n; scanf("%d", &n);
    for(int i = 2; i*i<=n; ++i) {
        if(n%i) continue;
        if(Gcd(i,n/i)==1) {
            int a = i, b = n/i;
            for(int k = 1; k*a < n-1; ++k) {
                if((n-1-k*a)%b == 0) {
                    int j = (n-1-k*a) / b;
                    puts("YES");
                    puts("2");
                    printf("%d %d\n", k, b);
                    printf("%d %d\n", j, a);
                }
            }
            exit(0);
        }
    }
    puts("NO");
    return 0;
}
