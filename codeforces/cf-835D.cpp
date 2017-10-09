#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 5e3, c_sz = 26;
struct PTree {
    int tot, last, S_len;
    int len[maxn + 5], fail[maxn + 5], S[maxn + 5];
    int nex[maxn + 5][c_sz];
    int NewNode(int l) {
        len[tot] = l, fail[tot] = 0;
        mem(nex[tot], 0);
        return tot++;
    }
    void Init() {
        tot = 0;
        NewNode(0), NewNode(-1);
        fail[0] = 1, last = 0;
        S[S_len = 0] = -1;
    }
    int GetFail(int x) {
        while(S[S_len-len[x]-1] != S[S_len])
            x = fail[x];
        return x;
    }
    void Add(int w) {
        S[++S_len] = w;
        last = GetFail(last);
        if(nex[last][w] == 0) {
            int u = NewNode(len[last] + 2);
            fail[u] = nex[GetFail(fail[last])][w];
            nex[last][w] = u;
        }
        last = nex[last][w];
    }
} tree;

int n, f[maxn + 5][maxn + 5], ans[maxn + 5];
char str[maxn + 5];

int main() {
    scanf("%s", str + 1);
    n = strlen(str + 1);
    tree.Init();
    for(int i = 1; i <= n; ++i) {
        tree.Add(str[i] - 'a');
        int u = tree.last, hf, ll;
        while(tree.len[u] >= 1) {
            ll = tree.len[u], hf = ll >> 1;
            f[i - ll + 1][i] = f[i - ll + 1][i - ll + hf] + 1;
            ++ans[ f[i - ll + 1][i] ];
            u = tree.fail[u];
        }
    }
    for(int i = n; i >= 1; --i)
        ans[i] += ans[i+1];
    for(int i = 1; i <= n; ++i) {
        if(i > 1) printf(" ");
        printf("%d", ans[i]);
    }
    printf("\n");
    return 0;
}
