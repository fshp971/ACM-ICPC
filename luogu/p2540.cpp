#include<cassert>
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int n, ans, cnt[20];

int cc[5];
int dp[25][25][25][25], vis[25][25][25][25];

int dfs2(int c1, int c2, int c3, int c4) {
    if(vis[c1][c2][c3][c4]) return dp[c1][c2][c3][c4];
    vis[c1][c2][c3][c4] = 1;

    int &res = dp[c1][c2][c3][c4];
    res = c1 + c2 + c3 + c4;

    // 4+22
    if(c4 && c2>=2) res = min(res, dfs2(c1, c2-2, c3, c4-1) + 1);

    // 4+2
    if(c4 && c2) res = min(res, dfs2(c1, c2-1, c3, c4-1) + 1);
    if(c4 && c1>=2) res = min(res, dfs2(c1-2, c2, c3, c4-1) + 1);

    // 3+2
    if(c3 && c2) res = min(res, dfs2(c1, c2-1, c3-1, c4) + 1);

    // 3+1
    if(c3 && c1) res = min(res, dfs2(c1-1, c2, c3-1, c4) + 1);

    // 1/2/3/4
    if(c1) res = min(res, dfs2(c1-1, c2, c3, c4) + 1);
    if(c2) res = min(res, dfs2(c1, c2-1, c3, c4) + 1);
    if(c3) res = min(res, dfs2(c1, c2, c3-1, c4) + 1);
    if(c4) res = min(res, dfs2(c1, c2, c3, c4-1) + 1);

    // 4 = 1+3 = 2+2
    if(c4) {
        res = min(res, dfs2(c1+1, c2, c3+1, c4-1));
        res = min(res, dfs2(c1, c2+2, c3, c4-1));
    }

    // 3 = 1+2
    if(c3) res = min(res, dfs2(c1+1, c2+1, c3-1, c4));

    // 2 = 1+1
    if(c2) res = min(res, dfs2(c1+2, c2-1, c3, c4));

    return res;
}

int calc() {
    cc[1] = cc[2] = cc[3] = cc[4] = 0;
    for(int i = 1; i <= 13; ++i)
        ++cc[cnt[i]];

    int res = dfs2(cc[1]+cnt[14]+cnt[15], cc[2], cc[3], cc[4]);
    if(cnt[14] && cnt[15])
        res = min(res, dfs2(cc[1], cc[2], cc[3], cc[4]) + 1);

    return res;
}

void dfs(int nc, int shun, int l) {
    if(shun == 0) {
        ans = min(ans, nc + calc());
        return;
    }

    if(nc+1 < ans) {
        int d;
        if(shun == 3) d = 2;
        else if(shun == 2) d = 3;
        else d = 5;

        for(int i = l; i <= 12; ++i) {
            int k = i;
            for(; k<=12 && cnt[k]>=shun; ++k) {
                cnt[k] -= shun;
                if(k-i+1 >= d) {
                    dfs(nc+1, shun, i);
                }
            }
            for(int j = i; j < k; ++j) cnt[j] += shun;
        }
    }
    dfs(nc, shun-1, 1);
}

int main() {
    ios::sync_with_stdio(0);
    int _, n; cin >> _ >> n;
    while(_--) {
        for(int i = 1; i <= 15; ++i) cnt[i] = 0;
        for(int i = 1, a,b; i <= n; ++i) {
            cin >> a >> b;
            if(a == 0) {
                if(b == 1) ++cnt[14];
                else ++cnt[15];
            }
            else if(a == 2) ++cnt[13];
            else if(a == 1) ++cnt[12];
            else ++cnt[a-2];
        }
        ans = n;
        dfs(0, 3, 1);
        cout << ans << "\n";
    }
    return 0;
}
