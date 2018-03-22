#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cassert>
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

const int maxn = 1e5;

int top = 0;
char str[maxn + 5], sta[maxn + 5];
int main() {
    scanf("%s", str);
    for(int i = 0; str[i] != '\0'; ++i) {
        sta[++top] = str[i];
        if(top >= 2 && sta[top] == sta[top-1])
            top -= 2;
        if(top >= 5 && sta[top] == sta[top-2] && sta[top] == sta[top-4] && sta[top-1] == sta[top-3]) {
            str[i--] = sta[top-1];
            str[i--] = sta[top];
            str[i--] = sta[top-1];
            top -= 5;
        }
    }
    printf("%s\n", top ? "open" : "closed");
    return 0;
}
