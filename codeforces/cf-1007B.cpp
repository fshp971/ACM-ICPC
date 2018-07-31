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
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e5;

const int cho[3][4] = { {0,3,5,6}, {1,3,4,6}, {2,4,5,6} };

int A, B, C, cnt[7];
vector<int> dA, dB, dC;

void Deco(int x, vector<int> &deco) {
    deco.clear();
    for(int i = 1; i*i <= x; ++i) {
        if(x%i) continue;
        deco.PB(i);
        if(i*i != x) deco.PB(x/i);
    }
}

unordered_set<int> Hash;
LL Calc(int x, int y, int z) {
    if(x>y) swap(x,y);
    if(y>z) swap(y,z);
    if(x>y) swap(x,y);
    int ha = x*100 + y*10 + z;
    if(Hash.find(ha) != Hash.end()) return 0LL;
    Hash.insert(ha);
    if(x==y && y==z) {
        LL ret = LL(cnt[x]) * (cnt[x]-1) * (cnt[x]-2) / 6;
        ret += LL(cnt[x]) * (cnt[x]-1);
        ret += LL(cnt[x]);
        return ret;
    }
    if(x==y) return LL(cnt[x]) * (cnt[x]+1) / 2 * cnt[z];
    if(y==z) return LL(cnt[y]) * (cnt[y]+1) / 2 * cnt[x];
    return LL(cnt[x]) * cnt[y] * cnt[z];
}

int main() {
    int T; scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d", &A, &B, &C);
        Deco(A,dA); Deco(B,dB); Deco(C,dC);
        mem(cnt, 0);
        for(auto it : dA) {
            int fg1 = 0, fg2 = 0;
            if(B%it == 0) ++fg1;
            if(C%it == 0) ++fg2;
            if(fg1 && fg2) ++cnt[6];
            else if(fg1) ++cnt[3];
            else if(fg2) ++cnt[5];
            else ++cnt[0];
        }
        for(auto it : dB) {
            if(A%it == 0) continue;
            if(C%it == 0) ++cnt[4];
            else ++cnt[1];
        }
        cnt[2] = int(dC.size()) - cnt[6] - cnt[5] - cnt[4];
        LL ans = 0;
        Hash.clear();
        FOR(i,0,4) FOR(k,0,4) FOR(j,0,4) { ans += Calc(cho[0][i], cho[1][k], cho[2][j]); }
        printf("%lld\n", ans);
    }
    return 0;
}
