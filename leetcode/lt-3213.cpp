typedef long long LL;

class Solution {
    static const int maxn = 26*26;
    static const int INF = 1e9;
    static const int B = 37, P = 1e9+9;
public:
    int minimumCost(string target, vector<string>& words, vector<int>& costs) {
        int n = target.size(), m = words.size();
        vector<int> idx(m);
        for(int i = 0; i < m; ++i) idx[i] = i;
        sort(idx.begin(), idx.end(), [&](const int &a, const int &b){return costs[a]<costs[b];});
        vector<int> one(28, (int)INF);
        vector<vector<int>> two(28, vector<int>(28, (int)INF));
        map<pair<int,int>, int> mp[28][28];
        for(int i = m-1; i >= 0; --i) {
            int &ii = idx[i];
            int len = words[ii].size();
            if(words[ii].size() == 1)
                one[words[ii][0]-'a'] = costs[ii];
            else if(words[ii].size() == 2)
                two[words[ii][1]-'a'][words[ii][0]-'a'] = costs[ii];
            else {
                int tmp = 0;
                for(int k = 0; k+2 < words[ii].size(); ++k)
                    tmp = (LL(tmp) * B + words[ii][k] - 'a') % P;
                mp[words[ii][len-1]-'a'][words[ii][len-2]-'a'][pair<int,int>(tmp, words[ii].size())] = ii;
            }
        }
        vector<int> ha(n+5, 0), pow(n+5, 0);
        pow[0] = 1;
        for(int i = 1; i <= n; ++i) {
            ha[i] = (LL(ha[i-1]) * B + target[i-1]-'a') % P;
            pow[i] = LL(pow[i-1]) * B % P;
        }
        vector<int> dp(n+5, (int)INF);
        dp[0] = 0;
        for(int i = 1; i <= n; ++i) {
            int c1 = target[i-1]-'a', c2 = -1;
            if(i >= 2) c2 = target[i-2]-'a';
            dp[i] = min(dp[i], dp[i-1] + one[c1]);
            if(c2 != -1) dp[i] = min(dp[i], dp[i-2] + two[c1][c2]);
            if(i >= 3) {
                for(auto &it : mp[c1][c2]) {
                    auto &key = it.first;
                    int id = it.second;
                    int len = words[id].size(), co = costs[id];
                    if(i < len) continue;
                    int t = (ha[i-2] - LL(ha[i-len]) * pow[len-2] % P + P) % P;
                    if(t == key.first && len == key.second)
                        dp[i] = min(dp[i], dp[i-len] + co);
                }
            }
        }
        if(dp[n] >= INF) return -1;
        return dp[n];
    }
};
