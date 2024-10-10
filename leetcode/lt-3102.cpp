class Solution {
public:
    int minimumDistance(vector<vector<int>>& points) {
        int n = points.size();
        vector<pair<int,int>> vec[4];
        for(int i = 0; i < n; ++i) {
            int x = points[i][0], y = points[i][1];
            vec[0].push_back(pair<int,int>(x+y, i));
            vec[1].push_back(pair<int,int>(x-y, i));
            vec[2].push_back(pair<int,int>(-x-y, i));
            vec[3].push_back(pair<int,int>(-x+y, i));
        }
        for(int i = 0; i < 4; ++i)
            sort(vec[i].begin(), vec[i].end());
        int ans = 1e9;
        for(int i = 0; i < n; ++i) {
            int tmp = -1e9;
            for(int k = 0; k < 4; ++k) {
                int l = 0, r = n-1;
                if(vec[k][l].second == i) ++l;
                if(vec[k][r].second == i) --r;
                tmp = max(tmp, vec[k][r].first - vec[k][l].first);
            }
            ans = min(ans, tmp);
        }
        return ans;
    }
};
