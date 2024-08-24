typedef long long LL;

class Solution {
    static const LL INF = 1e16;
public:
    long long maximumScore(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<LL>> f(n+5, vector<LL>(n+5, 0));
        vector<vector<LL>> g(n+5, vector<LL>(n+5, 0));
        vector<vector<LL>> ss(n+5, vector<LL>(n+5, 0));
        for(int i = 0; i < n; ++i)
            for(int k = 0; k < n; ++k)
                ss[i+1][k+1] = ss[i][k+1] + grid[i][k];
        for(int i = 1; i <= n; ++i) f[i][0] = -INF;
        for(int k = 1; k <= n; ++k) {
            LL tmp = 0;
            for(int i = n; i >= 0; --i) {
                tmp = max(tmp, f[i][k-1] + ss[i][k]);
                f[i][k] = max(g[i][k-1], tmp - ss[i][k]);
            }
            LL tmp1 = 0, tmp2 = 0;
            for(int i = 0; i <= n; ++i) {
                tmp1 = max(tmp1, f[i][k-1]);
                tmp2 = max(tmp2, g[i][k-1] - ss[i][k]);
                g[i][k] = max(tmp1, tmp2) + ss[i][k];
            }
        }
        LL ans = 0;
        for(int i = 0; i <= n; ++i) ans = max(ans, f[i][n]);
        return ans;
    }
};
