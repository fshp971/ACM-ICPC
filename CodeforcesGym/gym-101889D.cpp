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

const int maxn = 1e5;

int L, C, N;
map<pii,int> odt;
unordered_map<int,int> cnt;

void Split(int x) {
    if(x<0 || x>L-1) return;
    auto it = odt.lower_bound( MP(x,-1) );
    if(it!=odt.end() && it->fi.fi==x) return;
    --it;
    int l = it->fi.fi, r = it->fi.se, c = it->se;
    //printf("l = %d, r = %d, x = %d\n", l, r, x);
    odt.erase(it);
    odt[MP(l,x-1)] = c;
    odt[MP(x,r)] = c;
}

void Run(int l, int r, int c) {
    Split(l), Split(r+1);
    map<pii,int>::iterator it = odt.lower_bound(MP(l,-1)), pit;
    while(it != odt.end() && it->fi.fi <= r) {
        pit = it++;
        cnt[pit->se] -= pit->fi.se - pit->fi.fi + 1;
        odt.erase(pit);
    }
    odt[MP(l,r)] = c, cnt[c] += r-l+1;
}

int main() {
	scanf("%d%d%d", &L, &C, &N);
    odt[MP(0,L-1)] = 1, cnt[1] = L;
	while(N--) {
		int P, X, A, B;
		scanf("%d%d%d%d", &P, &X, &A, &B);
        int S = cnt[P];
		int M1 = (A+LL(S)*S) % L;
		int M2 = (A+LL(S+B)*(S+B)) % L;
		if(M1>M2) swap(M1,M2);
        //printf("P = %d, X = %d, S = %d, M1 = %d, M2 = %d\n", P, X, S, M1, M2);
		Run(M1,M2,X);
	}
    int ans = 0;
    for(auto it : cnt) ans = max(ans, it.se);
    printf("%d\n", ans);
	return 0;
}
