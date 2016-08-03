/**************************************************************
    Problem: 3309
    User: fshp971
    Language: C++
    Result: Accepted
    Time:17684 ms
    Memory:89180 kb
****************************************************************/
 
#include<bits/stdc++.h>
 
using namespace std;
 
#define LL long long
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))
#define MP(a,b) make_pair(a,b)
#define sf scanf
#define pf printf
 
const int maxn = 1e7;
 
bool vis[maxn+5];
int G[maxn+5], cnt[maxn+5];
 
void init()
{
    mem(cnt, 0);
    mem(vis, 0);
    mem(G, 0);
    G[1] = 0, G[0] = 0;
    int tmp, cont;
    for(int i=2; i<=maxn; ++i) if(!vis[i])
    {
        G[i] = 1;
        for(int k = i+i; k<=maxn; k+=i)
        {
            tmp = k, cont = 0;
            while(tmp%i == 0) tmp /= i, ++cont;
            if(!vis[k])
                cnt[k] = cont;
            else if(cnt[k] != cont) G[k] = 0;
            if(!vis[k]) G[k] = 1;
            else G[k] *= (-1);
            vis[k] = true;
        }
    }
    for(int i=2; i<=maxn; ++i) G[i] += G[i-1];
    return;
}
 
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    init();
    int T, a, b, nex;
    LL ans;
    sf("%d", &T);
    while(T--)
    {
        sf("%d%d", &a, &b);
        ans = 0;
        for(int i=1; i<=min(a,b); i=nex+1)
        {
            nex = min(a/(a/i), b/(b/i));
            ans += (LL)(a/i) * (b/i) * (G[nex]-G[i-1]);
        }
        cout << ans << "\n";
    }
    return 0;
}
