#include<cassert>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
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

const int maxn = 4000;
//const int md = 19260817, base = 23;
const int md = 998244353, base = 37;
const int md2 = 1e9 + 7, base2 = 79;

int cnt[26];
pair<LL,LL> GetHa() {
    LL ret = 0, ret2 = 0;
    for(int i = 0; i < 26; ++i) {
        ret = (ret * base + cnt[i]) % md;
        ret2 = (ret2 * base2 + cnt[i]) % md2;
    }
    return MP(ret, ret2);
}
/*
LL GetHa() {
    LL ret = 0;
    for(int i = 0; i < 26; ++i)
        ret = (ret * base + cnt[i]) % md;
    return ret;
}
*/

//int vist[md + 5];
char str1[maxn + 5], str2[maxn + 5];

//unordered_set<LL> Hash;
set<pair<LL,LL>> Hash;

int main() {
    scanf("%s%s", str1, str2);
    int n = strlen(str1), m = strlen(str2);
    for(int T = min(n,m); T >= 1; --T) {
        mem(cnt, 0);
        Hash.clear();
        for(int i = 0; i < T-1; ++i)
            ++cnt[str1[i]-'a'];
        for(int l = 0, r = T-1; r < n; ++l, ++r) {
            ++cnt[str1[r]-'a'];
            Hash.insert(GetHa());
            //vist[GetHa()] = T;
            --cnt[str1[l]-'a'];
        }

        mem(cnt, 0);
        for(int i = 0; i < T-1; ++i)
            ++cnt[str2[i]-'a'];
        for(int l = 0, r = T-1; r < m; ++l, ++r) {
            ++cnt[str2[r]-'a'];
            //if(vist[GetHa()] == T) exit(0 * printf("%d\n", T));
            if(Hash.find(GetHa()) != Hash.end())
                exit(0 * printf("%d\n", T));
            --cnt[str2[l]-'a'];
        }
    }
    puts("0");
    return 0;
}
