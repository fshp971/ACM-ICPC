typedef long long LL;

class Solution {
    static const LL INF = 1e16;
public:
    long long maximumValueSum(vector<vector<int>>& board) {
        int n = board.size(), m = board[0].size();
        auto U = board, D = board;
        for(int i = 1; i < n; ++i)
            for(int k = 0; k < m; ++k)
                U[i][k] = max(U[i][k], U[i-1][k]);
        for(int i = n-2; i >= 0; --i)
            for(int k = 0; k < m; ++k)
                D[i][k] = max(D[i][k], D[i+1][k]);
        auto max3 = [&](vector<int> &vec) -> vector<int> {
            vector<int> res(3, -1);
            for(int i = 0; i < vec.size(); ++i) {
                if(res[2] == -1 || vec[i] > vec[res[2]]) res[2] = i;
                for(int k = 2; k >= 1; --k) {
                    if(res[k-1] == -1 || vec[res[k]] > vec[res[k-1]])
                        swap(res[k-1], res[k]);
                }
            }
            return res;
        };
        LL ans = -INF;
        for(int i = 1; i < n-1; ++i) {
            auto uid = max3(U[i-1]), bid = max3(board[i]), did = max3(D[i+1]);
            for(auto ii : uid)
                for(auto kk : bid) if(ii != kk)
                    for(auto jj : did) if(ii != jj && kk != jj) {
                        ans = max(ans, LL(U[i-1][ii]) + board[i][kk] + D[i+1][jj]);
                    }
        }
        return ans;
    }
};
