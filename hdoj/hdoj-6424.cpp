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

const int INF = 1e9+100;

struct Node {
    int x, y;
    Node() {}
    Node(int _x, int _y) {
        x = min(_x,INF), y = min(_y,INF);
        if(x>y) swap(x,y);
    }
};

// a < b: -1;
// a = b:  0;
// a > b;  1.
int cmp(Node a, Node b) {
    if(a.x<b.x) return 1;
    if(a.x>b.x) return -1;
    if(a.y<b.y) return 1;
    if(a.y>b.y) return -1;
    return 0;
}

int cmp(Node a, Node b, Node c, Node d) {
    if(cmp(a,b) < 0) swap(a,b);
    if(cmp(c,d) < 0) swap(c,d);
    if(cmp(a,c) < 0) return -1;
    if(cmp(a,c) > 0) return 1;
    return cmp(b,d);
}

int main() {
    int _; scanf("%d", &_);
    int a, b, A[10], B[10];
    Node aa, bb, cc, dd;
    while(_--) {
        REP(i,0,2) A[i] = B[i] = INF;
        scanf("%d%d", &a, &b);
        REP(i,0,a-1) scanf("%d", A+i);
        REP(i,0,b-1) scanf("%d", B+i);
        aa = Node(A[0]+2,INF), bb = Node(A[1]+1,A[2]);
        cc = Node(B[0]+2,INF), dd = Node(B[1]+1,B[2]);
        printf("%d\n", cmp(aa,bb,cc,dd));
    }
    return 0;
}
