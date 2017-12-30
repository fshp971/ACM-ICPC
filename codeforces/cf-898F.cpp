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

const int maxn = 1e6, md = 1e9 + 7;

int n;
char str[maxn + 5];
LL ha[maxn + 5], pw[maxn + 5];
LL ha2[maxn + 5], pw2[maxn + 5];

inline LL GetHa(int ps, int l) {
    return (ha[ps+l-1] - ha[ps-1] * pw[l] % md + md) % md;
}

void Print(int s1, int l1, int s2, int l2, int s3, int l3) {
    for(int i = 0; i < l1; ++i)
        printf("%c", str[s1+i]);
    printf("+");
    for(int i = 0; i < l2; ++i)
        printf("%c", str[s2+i]);
    printf("=");
    for(int i = 0; i < l3; ++i)
        printf("%c", str[s3+i]);
    printf("\n");
    exit(0);
}

void Check(int s1, int l1, int s2, int l2, int s3, int l3) {
    if(l1 > 1 && str[s1] == '0') return;
    if(l2 > 1 && str[s2] == '0') return;
    if(l3 > 1 && str[s3] == '0') return;
    if(l3 < l1 || l3 < l2) return;
    if(l3 - l1 > 1 && l3 - l2 > 1) return;
    LL h1 = GetHa(s1, l1);
    LL h2 = GetHa(s2, l2);
    LL h3 = GetHa(s3, l3);
    if((h1 + h2) % md != h3) return;
    int ll = min(l1, l2), jin = 0, i, k, j;
    for(i = s1+l1-1, k=s2+l2-1, j=s3+l3-1; ll >= 1; --ll, --i, --k, --j) {
        int n1 = str[i] - '0', n2 = str[k] - '0', n3 = str[j] - '0';
        if((n1+n2+jin)%10 != n3) return;
        jin = (n1+n2+jin) / 10;
    }
    if(i < s1 && k < s2) {
        if(j < s3 && jin == 0)
            Print(s1, l1, s2, l2, s3, l3);
        if(j == s3 && jin == 1 && str[s3] == '1')
            Print(s1, l1, s2, l2, s3, l3);
        return;
    }
    else if(i < s1) {
        for(; k>=s2; --k, --j) {
            int n2 = str[k] - '0', n3 = str[j] - '0';
            if((n2+jin) % 10 != n3) return;
            jin = (n2+jin) / 10;
        }
        if(j < s3 && jin == 0)
            Print(s1, l1, s2, l2, s3, l3);
        if(j == s3 && jin == 1 && str[s3] == '1')
            Print(s1, l1, s2, l2, s3, l3);
        return;
    }
    else {
        for(; i>=s1; --i, --j) {
            int n1 = str[i] - '0', n3 = str[j] - '0';
            if((n1+jin) % 10 != n3) return;
            jin = (n1+jin) / 10;
        }
        if(j < s3 && jin == 0)
            Print(s1, l1, s2, l2, s3, l3);
        if(j == s3 && jin == 1 && str[s3] == '1')
            Print(s1, l1, s2, l2, s3, l3);
        return;
    }
    return;
}

int main() {
    pw[0] = 1;
    for(int i = 1; i <= maxn; ++i) pw[i] = pw[i-1] * 10 % md;
    scanf("%s", str + 1);
    n = strlen(str + 1);
    ha[1] = 0;
    for(int i = 1; i <= n; ++i) ha[i] = (ha[i-1] * 10 + str[i] - '0') % md;
    for(int i = 1; i <= (n >> 1); ++i) {
        int k = (n - i) >> 1;
        if(k >= i) Check(1, i, i+1, k, i+k+1, (n-i)-k);
        if(n-i-i > 0 && n-i-i <= i)
            Check(1, i, i+1, n-i-i, n-i+1, i);
        if(n-i-(i+1) > 0 && n-i-(i+1) <= i+1)
            Check(1, i, i+1, n-i-(i+1), n-i, i+1);
    }
    return 0;
}
