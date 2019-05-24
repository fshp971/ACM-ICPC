#include<bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define PER(i,a,b) for(int i = a; i >= b; --i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef double DB;

class LongJump2 {
    public:
    int countNewLeaders(int N, vector<int> jumpLengths) {
        int mx = -1, id = -1;
        int ans = 0, pt = 0;
        for(int i = 0; i < 3; ++i) {
            for(int k = 1; k <= N; ++k) {
                if(mx < jumpLengths[pt]) {
                    mx = jumpLengths[pt];
                    if(id != k) id = k, ++ans;
                }
                ++pt;
            }
        }
        return ans;
    }
};
