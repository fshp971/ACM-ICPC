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

struct Node {
    deque<int> *q1;
    deque<LL> *q2;
    Node() : q1(NULL), q2(NULL) {}
    Node(deque<int> *_q1, deque<LL> *_q2) {
        q1 = _q1, q2 = _q2;
        q1->clear(); q2->clear();
    }
};

const int maxn = 1e5;

LL ans = 0;
int n;
vector<int> G[maxn + 5];
deque<int> que1[maxn + 5];
deque<LL> que2[maxn + 5];

void Merge(Node &a, Node &b) {
    if(a.q1->size() < b.q1->size()) swap(a,b);
    for(int i = 0; i < b.q1->size(); ++i) {
        if(i < a.q2->size()) ans += (*b.q1)[i] * (*a.q2)[i];
        if(i < b.q2->size()) ans += (*b.q2)[i] * (*a.q1)[i];
        while(a.q2->size() <= i) a.q2->push_back(0);
        (*a.q2)[i] += LL((*a.q1)[i]) * (*b.q1)[i];
        (*a.q1)[i] += (*b.q1)[i];
        if(i < b.q2->size()) (*a.q2)[i] += (*b.q2)[i];
    }
}

Node dfs(int x, int p) {
    Node res = Node(&que1[x], &que2[x]);
    res.q1->push_back(1), res.q2->push_back(0);
    for(auto it : G[x])
        if(it != p) {
            Node tmp = dfs(it, x);
            tmp.q1->push_front(0);
            tmp.q2->pop_front();
            Merge(res, tmp);
        }
    return res;
}

int main() {
    //freopen("in.txt", "r", stdin);
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        REP(i,1,n) G[i].clear();
        for(int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            G[u].PB(v), G[v].PB(u);
        }
        ans = 0;
        dfs(1,0);
        printf("%lld\n", ans);
    }
    return 0;
}
