class Solution {
    typedef long long LL;
public:
    vector<int> findProductsOfElements(vector<vector<long long>>& queries) {
        auto calc = [&](LL x) -> LL {
            vector<int> vec(105, 0);
            int len = 0;
            LL res = 0, sfx = 0;
            while(true) {
                LL ii = 0, cc = 0, ss = 0;
                while(cc + (1 + len) * (1LL<<ii) <= x) {
                    x -= cc + (1+len) * (1LL<<ii);
                    res += ss + (ii+sfx) * (1LL<<ii);
                    cc += cc + (1LL<<ii);
                    ss += ss + ii * (1LL<<ii);
                    ++ii;
                }
                vec[++len] = ii;
                sfx += ii;
                if(x <= len) break;
                x -= len, res += sfx;
            }
            for(int i = len; i >= len-x+1; --i) res += vec[i];
            return res;
        };
        auto powMod = [&](LL a, LL b, LL p) -> LL {
            LL r = 1 % p;
            while(b) { if(b&1) r = r*a%p; a = a*a%p, b >>= 1; }
            return r;
        };
        vector<int> ans;
        for(auto &q : queries)
            ans.push_back( powMod(2, calc(q[1]+1) - calc(q[0]), q[2]) );
        return ans;
    }
};
