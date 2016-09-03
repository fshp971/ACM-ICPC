#include<bits/stdc++.h>
 
using namespace std;
 
#define LL long long
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP(a,b) make_pair(a,b)
#define pii pair<int,int>
#define sf scanf
#define pf printf
 
const int maxn = 1e5;
 
int n, m;
int h[maxn*3+5], e[maxn*5+5], nex[maxn*5+5], cost[maxn*5+5], col[maxn*5+5];
 
inline void addedge(int u, int v, int &top, int ci, int ti)
{
    e[++top] = v, col[top] = ci, cost[top] = ti, nex[top] = h[u]; h[u] = top;
}
 
char inq[maxn*3+5];
LL dis[maxn*3+5];

struct Node
{
	int x;
	LL dist;
	Node(): x(0), dist(0){}
	Node(int _x, LL _dist){ x = _x, dist = _dist; }
	//bool operator<(const Node a){ return dist > a.dist; }
};
 
bool operator<(Node a, Node b){ return a.dist > b.dist; }

void bfs()
{
    int x, nx, ci;
    LL res;
	Node tmp;
    priority_queue< Node > que;
    mem(dis, 0x7f);
    mem(inq, 0);
    dis[1] = 0;
    for(int i=h[1]; i; i=nex[i])
    {
        if(cost[i] < dis[e[i]])
        {
            dis[e[i]] = cost[i];
            if(!inq[e[i]])
            {
                que.push( Node(e[i], dis[e[i]]) );
                inq[e[i]] = 1;
            }
        }
    }
    while(!que.empty())
    {
        tmp = que.top(); que.pop();
		x = tmp.x;
        inq[x] = 0;
        nx = e[h[x]];
        ci = col[h[x]];
        dis[nx] = min(dis[nx], dis[x]);
        for(int i=h[nx]; i; i=nex[i])
        {
            res = dis[x] + cost[i] + abs(ci-col[i]);
            if(res < dis[e[i]])
            {
                dis[e[i]] = res;
                if(!inq[e[i]])
                {
                    que.push( Node(e[i], dis[e[i]]) );
                    inq[e[i]] = 1;
                }
            }
        }
    }
}
 
int main()
{
    int top, ai, bi, ci, ti;
    while(~sf("%d%d", &n, &m))
    {
        mem(h, 0);
        top = 0;
        REP(i,1,m)
        {
            sf("%d%d%d%d", &ai, &bi, &ci, &ti);
            addedge(ai, n+m+i, top, ci, ti);
            addedge(bi, n+i, top, ci, ti);
            addedge(n+i, ai, top, ci, 0);
            addedge(n+m+i, bi, top, ci, 0);
        }
        bfs();
        cout << dis[n] << "\n";
    }
    return 0;
}
