class Solution {
public:
    static const int maxn = 4e4, maxv = 2e2;
    vector<int> pre = vector<int>(maxn+5);
    vector<int> nex = vector<int>(maxn+5);
    int numberOfSubstrings(string s) {
        int n = s.size();
        int las = 0;
        for(int i = 1; i <= n; ++i) {
            if(s[i-1] == '1') continue;
            nex[las] = i, pre[i] = las, las = i;
        }
        nex[las] = n+1, pre[n+1] = las;
        if(las == 0) {
            return (n*(n+1)) >> 1;
        }
        int ans = 0;
        for(int i = 0; i <= n; i = nex[i]) {
            int len = nex[i]-1 - i;
            ans += (len * (len+1)) >> 1;
        }
        for(int t = 1; t <= maxv; ++t) {
            int lim = t*t;
            int c = 1, l = nex[0], r = nex[0];
            while(r <= n) {
                while(c<t && r<=n) ++c, r = nex[r];
                if(r > n) break;
                int c1 = l-1-pre[l], c2 = nex[r]-1-r;
                int v = lim - (r-l+1 - t);
                if(v <= 0) {
                    ans += (c1+1) * (c2+1);
                }
                else {
                    {
                        int tl = max(v-c2-1, 0), tr = min(c1, v);
                        if(tl <= tr) {
                            ans += ((tl+tr) * (tr-tl+1)) >> 1;
                            ans += (tr-tl+1) * (c2-v+1);
                        }
                    }
                    {
                        int tl = max(0, v+1), tr = c1;
                        if(tl <= tr) ans += (tr-tl+1) * (c2+1);
                    }
                }
                --c, l = nex[l];
            }
        }
        return ans;
    }
};
