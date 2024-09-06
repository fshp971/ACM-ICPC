class Solution {
    static const int INF = 1e8;
    int calc(vector<vector<int>> &grid, int ln, int lm, int rn, int rm) {
        int lx = INF, rx = -INF, ly = INF, ry = -INF;
        for(int i = ln; i <= rn; ++i)
            for(int k = lm; k <= rm; ++k) if(grid[i][k]) {
                lx = min(lx, i);
                rx = max(rx, i);
                ly = min(ly, k);
                ry = max(ry, k);
            }
        if(lx==INF || ly==INF) return INF;
        return (rx-lx+1) * (ry-ly+1);
    }
public:
    int minimumSum(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int ans = INF;
        for(int i = 0; i+1 < n; ++i)
            for(int k = 0; k+1 < m; ++k) {
                ans = min(ans, calc(grid,0,0,i,k) + calc(grid,0,k+1,i,m-1) + calc(grid,i+1,0,n-1,m-1));
                ans = min(ans, calc(grid,0,0,n-1,k) + calc(grid,0,k+1,i,m-1) + calc(grid,i+1,k+1,n-1,m-1));
                ans = min(ans, calc(grid,0,0,i,k) + calc(grid,i+1,0,n-1,k) + calc(grid,0,k+1,n-1,m-1));
                ans = min(ans, calc(grid,0,0,i,m-1) + calc(grid,i+1,0,n-1,k) + calc(grid,i+1,k+1,n-1,m-1));
            }
        for(int i = 0; i+2 < n; ++i)
            for(int k = i+1; k+1 < n; ++k)
                ans = min(ans, calc(grid,0,0,i,m-1) + calc(grid,i+1,0,k,m-1) + calc(grid,k+1,0,n-1,m-1));
        for(int i = 0; i+2 < m; ++i)
            for(int k = i+1; k+1 < m; ++k)
                ans = min(ans, calc(grid,0,0,n-1,i) + calc(grid,0,i+1,n-1,k) + calc(grid,0,k+1,n-1,m-1));
        return ans;
    }
};
