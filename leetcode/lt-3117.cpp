class Solution {
    static const int INF = 1e9;
public:
    int minimumValueSum(vector<int>& nums, vector<int>& andValues) {
        int n = nums.size();
        int m = andValues.size();
        vector<vector<int>> f(2, vector<int>(n+5, 1*INF));
        int fg = 0;
        f[fg][0] = 0;
        for(int k = 1; k <= m; ++k) {
            unordered_map<int,int> mp[2];
            int ffg = 0;
            f[fg^1][0] = INF;
            for(int i = 1; i <= n; ++i) {
                mp[ffg^1].clear();
                for(auto &pp : mp[ffg]) {
                    int v = pp.first & nums[i-1];
                    if(v < andValues[k-1]) continue;
                    if(mp[ffg^1].find(v) == mp[ffg^1].end())
                        mp[ffg^1][v] = pp.second;
                    else mp[ffg^1][v] = min(mp[ffg^1][v], pp.second);
                }
                if(f[fg][i-1] < INF) {
                    int v = nums[i-1];
                    if(mp[ffg^1].find(v) == mp[ffg^1].end())
                        mp[ffg^1][v] = f[fg][i-1];
                    else
                        mp[ffg^1][v] = min(mp[ffg^1][v], f[fg][i-1]);
                }
                if(mp[ffg^1].find(andValues[k-1]) != mp[ffg^1].end())
                    f[fg^1][i] = mp[ffg^1][andValues[k-1]] + nums[i-1];
                else
                    f[fg^1][i] = INF;
                ffg ^= 1;
            }
            fg ^= 1;
        }
        if(f[fg][n] < INF) return f[fg][n];
        return -1;
    }
};
