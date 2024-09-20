class Solution {
public:
    int minValidStrings(vector<string>& words, string target) {
        int n = target.size();
        vector<int> g(n+5, 0);
        for(auto &w : words) {
            int m = w.size();
            vector<int> f(m+5, 0);
            for(int i = 2, p = 0; i <= m; ++i) {
                while(p > 0 && w[p+1-1] != w[i-1]) p = f[p];
                if(w[p+1-1] == w[i-1]) f[i] = ++p;
            }
            for(int i = 1, p = 0; i <= n; ++i) {
                while(p > 0 && w[p+1-1] != target[i-1]) p = f[p];
                if(w[p+1-1] == target[i-1]) {
                    g[i] = max(g[i], ++p);
                    if(p == m) p = f[p];
                }
            }
        }
        for(int i = 1; i <= n; ++i) {
            if(g[i] == 0) return -1;
            g[i] = g[i-g[i]] + 1;
        }
        return g[n];
    }
};
