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

const int maxn = 1e5;

int s1[2][maxn + 5], s2[2][maxn + 5];

int Chk(int l1, int r1, int l2, int r2) {
    int a1 = min(s2[0][r1], r1-l1+1);
    int a2 = min(s2[1][r2], r2-l2+1);
    if(a1 < a2) return 0;
    int rem = a1 - a2;
    int b1 = s1[0][r1] - s1[0][l1-1];
    int b2 = s1[1][r2] - s1[1][l2-1];
    if(b1 > b2) return 0;
    int del = b2 - b1;
    if(del&1) return 0;
    del >>= 1;
    if(del == 0) return rem%3 == 0;
    if(b1 == 0) return rem > 0;
    return 1;
}

char str[maxn + 5];

int main() {
    for(int i = 0; i < 2; ++i) {
        scanf("%s", str + 1);
        for(int k = 1; str[k] != '\0'; ++k) {
            if(str[k] == 'A')
                s1[i][k] = s1[i][k-1], s2[i][k] = s2[i][k-1] + 1;
            else
                s1[i][k] = s1[i][k-1] + 1, s2[i][k] = 0;
        }
    }
    int T, l1, l2, r1, r2;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
        printf("%d", Chk(l1, r1, l2, r2));
    }
    puts("");
    return 0;
}
