/**************************************************************
    Problem: 3529
    User: fshp971
    Language: C++
    Result: Accepted
    Time:3560 ms
    Memory:3732 kb
****************************************************************/
 
#include<bits/stdc++.h>
 
using namespace std;
 
#define LL long long
#define MP(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define sf scanf
#define pf printf
 
const int maxn = 1e5, maxQ = 2e4;
 
bool vis[maxn+5];
int prime[maxn+5], mu[maxn+5];
int tree[maxn+5];
 
pii data[maxn+5];
 
void mobius()
{
    mem(vis, 0);
    mu[1] = 1;
    int tot = 0;
    for(int i=2; i<=maxn; ++i)
    {
        if(!vis[i]) prime[++tot] = i, mu[i] = -1;
        for(int j=1; j<=tot && i*prime[j] <= maxn; ++j)
        {
            vis[i*prime[j]] = true;
            if(i%prime[j]) mu[i*prime[j]] = -mu[i];
            else{ mu[i*prime[j]] = 0; break; }
        }
    }
    mem(data, 0);
    for(int i=1; i<=maxn; ++i)
    {
        data[i].second = i;
        for(int k=i; k<=maxn; k+=i)
            data[k].first += i;
    }
    sort(data+1, data+1+maxn);
    return;
}
 
inline int lowbit(int x){ return x & (-x); }
 
void add(int x, int dat)
{
    while(x<=maxn){ tree[x] += dat; x += lowbit(x); }
}
 
int sum(int x)
{
    int res = 0;
    while(x>0){ res += tree[x]; x -= lowbit(x); }
    return res;
}
 
struct Node
{
    int n, m, lim, id;
    bool operator<(const Node &a)const{ return lim < a.lim; }
}arr[maxQ+5];
int ans[maxQ+5];
 
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    mobius();
    int T, now = 1, nex;
    sf("%d", &T);
    for(int i=1; i<=T; ++i) sf("%d%d%d", &arr[i].n, &arr[i].m, &arr[i].lim), arr[i].id = i;
    sort(arr+1, arr+1+T);
    mem(tree, 0);
    for(int t=1; t<=T; ++t)
    {
        while(data[now].first <= arr[t].lim)
        {
            for(int k = data[now].second; k <= maxn; k += data[now].second)
                add(k, data[now].first * mu[k/data[now].second]);
            ++now;
        }
        ans[arr[t].id] = 0;
        for(int k=1; k<=min(arr[t].n, arr[t].m); ++k)
        {
            nex = min(arr[t].n / (arr[t].n/k), arr[t].m / (arr[t].m/k));
            ans[arr[t].id] += (sum(nex) - sum(k-1)) * (arr[t].n/k) * (arr[t].m/k);
            k = nex;
        }
    }
    for(int i=1; i<=T; ++i) pf("%d\n", ans[i] & 2147483647);
    return 0;
}
