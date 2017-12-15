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

LL W, H;

bool Check(LL a, LL b, LL c) {
    if((b+c)*2 <= W && (a+c*2) <= H) return true;
    if((b+c)*2 <= H && (a+c*2) <= W) return true;
    if(a*3+b+c <= W && b+c <= H) return true;
    if(a*3+b+c <= H && b+c <= W) return true;
    return false;
}

int main() {
    LL a, b, c;
    scanf("%lld%lld%lld%lld%lld", &a, &b, &c, &W, &H);
    if(Check(a,b,c) || Check(a,c,b) || Check(b,a,c) || Check(b,c,a) || Check(c,a,b) || Check(c,b,a))
        puts("Yes");
    else puts("No");
    return 0;
}
