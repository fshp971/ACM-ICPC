static const int maxk = 14;
static int f[maxk+5][maxk+5][(1<<maxk)+5];

class Solution {
public:
    int dfs(int st, int ed, int msk, vector<int> &nums) {
        if(f[st][ed][msk] != -1) return f[st][ed][msk];
        if(!msk) return f[st][ed][msk] = abs(ed - nums[st]);
        int kk = nums.size();
        auto &res = f[st][ed][msk];
        res = 1e9;
        for(int i = 0; i < kk; ++i) if(msk>>i&1) {
            int tmp = dfs(st, i, msk^(1<<i), nums) + abs(ed - nums[i]);
            res = min(res, tmp);
        }
        return f[st][ed][msk];
    }
    vector<int> findPermutation(vector<int>& nums) {
        int n = nums.size();
        memset(f, -1, sizeof(f));
        vector<int> ans;
        int st = -1, val = 1e9, msk = (1<<n) - 1, ed = -1;
        for(int i = 0; i < n; ++i) {
            int tmp = dfs(i, i, msk - (1<<i), nums);
            if(tmp < val) st = i, val = tmp;
        }
        ans.push_back(st);
        msk ^= (1<<st), ed = st;
        for(int i = 1; i < n; ++i) {
            int nx = -1, nv = 1e9;
            for(int k = 0; k < n; ++k) if(msk>>k&1) {
                int tmp = dfs(st, k, msk - (1<<k), nums) + abs(ed - nums[k]);
                if(tmp < nv) nx = k, nv = tmp;
            }
            ans.push_back(nx);
            msk ^= 1<<nx, ed = nx;
        }
        return ans;
    }
};
