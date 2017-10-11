#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
typedef long long LL;
typedef pair<int,int> pii;

#define NO puts("Impossible"); return 0;

const int maxn = 1e6;

int pos[maxn + 5];
char str[maxn + 5];

int main() {
    LL a, b, c, d, zero, one;
    scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
    zero = sqrt(a << 1) + 1;
    one = sqrt(d << 1) + 1;
    if(zero*(zero-1) != a*2 || one*(one-1) != d*2) {NO}
    if(zero + one > maxn) {NO}
    if(b == 0 && c == 0) {
        if(a == 0) { REP(i,1,one) printf("1"); puts(""); return 0; }
        else if(d == 0) { REP(i,1,zero) printf("0"); puts(""); return 0; }
        else puts("Impossible");
        return 0;
    }
    LL rem1 = zero * one, rem2 = 0;
    for(int i = 1; i <= zero && rem1 > b && rem2 < c; ++i) {
        pos[i] = (c - rem2 > one) ? one : (c - rem2);
        rem2 += pos[i], rem1 -= pos[i];
    }
    if(rem1 != b || rem2 != c) {NO};
    int len = zero + one, pt1 = 1, pt2 = len - 1;
    str[len] = '\0';
    for(int i = 0; i <= one; ++i) {
        while(pt1 <= zero && pos[pt1] == one - i) {
            str[pt2--] = '0', ++pt1;
        }
        if(i < one) str[pt2--] = '1';
    }
    puts(str);
    return 0;
}
