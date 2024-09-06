class Solution {
public:
    int maxTotalReward(vector<int>& rewardValues) {
        auto vec = rewardValues;
        sort(vec.begin(), vec.end());
        int n = vec.size();
        const int maxn = 10e4;
        bitset<maxn+5> bt, mk;
        int pt = 0;
        bt[0] = 1;
        for(auto v : vec) {
            while(pt < v) mk[pt++] = 1;
            bt |= (bt & mk) << v;
        }
        int ans = 0;
        for(int i = maxn; i >= 1; --i)
            if(bt[i]) { ans = i; break; }
        return ans;
    }
};
