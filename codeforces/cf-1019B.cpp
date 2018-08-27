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

int ask(int x) {
    cout << "? " << x << endl;
    fflush(stdout);
    cin >> x;
    return x;
}

void print(int x) {
    cout << "! " << x << endl;
    exit(0);
}

int main() {
    int n, hf;
    cin >> n, hf = n>>1;
    if(hf&1) print(-1);
    int a = ask(1), b = ask(1+hf);
    if(a == b) print(1);
    int l, r;
    if(a<b) l = 2, r = hf;
    else l = hf+2, r = n;
    while(l < r) {
        int mid = (l + r) >> 1, pim = (mid-1+hf+n)%n + 1;
        a = ask(mid), b = ask(pim);
        if(a == b) print(mid);
        if(a < b) l = mid+1;
        else r = mid-1;
    }
    print(l);
    return 0;
}
