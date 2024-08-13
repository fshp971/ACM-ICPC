typedef long long LL;

template<typename T>
class Fenwick {
private:
    int n;
    T *tr;
public:
    Fenwick(int len) {
        n = len;
        tr = new T[n+1];
        for(int i = 0; i <= n; ++i) tr[i] = 0;
    }
    void add(int x, T v) {
        for(; x <= n; x += x&(-x)) tr[x] += v;
    }
    T sum(int x) {
        T r = 0;
        for(; x; x -= x&(-x)) r += tr[x];
        return r;
    }
    ~Fenwick() {
        delete[] tr;
        tr = NULL;
    }
};

class Solution {
private:
    static const int maxn = (5e4);
    int nex[maxn*2+5];
    Fenwick<LL> tr1{maxn+5}, tr2{maxn+5};
    map<int,int> seg;
public:
    vector<int> numberOfAlternatingGroups(vector<int>& colors, vector<vector<int>>& queries) {
        int n = colors.size();
        int ll = 1, rr = 1;
        for(int i = 2; i <= n; ++i) {
            if(colors[i-1] ^ colors[i-2]) rr = i;
            else seg[ll] = rr, ll = rr = i;
        }
        seg[ll] = rr;
        auto add_f = [&](int x, int fg) {
            tr1.add(x, x*fg);
            tr2.add(x, fg);
        };
        for(auto it : seg) {
            int tmp = it.second - it.first + 1;
            add_f(tmp, 1);
        }
        vector<int> ans;
        for(auto it : queries) {
            if(it[0] == 1) {
                LL tmp = tr1.sum(n) - tr1.sum(it[1]-1);
                tmp -= LL(it[1]-1) * (tr2.sum(n) - tr2.sum(it[1]-1));
                if((colors[0] ^ colors[n-1])) {
                    if(seg.size() == 1)
                        tmp = n;
                    else {
                        auto it1 = seg.begin(), it2 = (--seg.end());
                        int tmp1 = it1->second - it1->first + 1;
                        int tmp2 = it2->second - it2->first + 1;
                        if(tmp1 >= it[1]) tmp -= tmp1 - it[1] + 1;
                        if(tmp2 >= it[1]) tmp -= tmp2 - it[1] + 1;
                        if(tmp1+tmp2 >= it[1]) tmp += tmp1 + tmp2 - it[1] + 1;
                    }
                }
                ans.push_back(tmp);
            }
            else {
                if(colors[it[1]] == it[2]) continue;
                colors[it[1]] = it[2];
                auto ss = --seg.upper_bound(it[1]+1);
                int l = ss->first, r = ss->second;
                if(it[1]+1 < r) {
                    add_f(r-l+1, -1);
                    seg[l] = it[1]+1, add_f(it[1]+2-l, 1);
                    seg[it[1]+2] = r, add_f(r-it[1]-1, 1);
                }
                if(it[1]+1 > l) {
                    add_f(it[1]+2-l, -1);
                    seg[l] = it[1], add_f(it[1]-l+1, 1);
                    seg[it[1]+1] = it[1]+1, add_f(1, 1);
                }
                if(it[1]+1 == l && it[1]+1 > 1) {
                    auto ss1 = --seg.upper_bound(it[1]);
                    auto ss2 = --seg.upper_bound(it[1]+1);
                    int tl1 = ss1->first, tr1 = ss1->second;
                    int tl2 = ss2->first, tr2 = ss2->second;
                    add_f(tr1-tl1+1, -1), add_f(tr2-tl2+1, -1), add_f(tr2-tl1+1, 1);
                    seg.erase(tl2), seg[tl1] = tr2;
                }
                if(it[1]+1 == r && it[1]+1 < n) {
                    auto ss1 = --seg.upper_bound(it[1]+1);
                    auto ss2 = --seg.upper_bound(it[1]+2);
                    int tl1 = ss1->first, tr1 = ss1->second;
                    int tl2 = ss2->first, tr2 = ss2->second;
                    add_f(tr1-tl1+1, -1), add_f(tr2-tl2+1, -1), add_f(tr2-tl1+1, 1);
                    seg.erase(tl2), seg[tl1] = tr2;
                }
            }
        }
        return ans;
    }
};
