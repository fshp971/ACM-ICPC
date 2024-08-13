typedef long long LL;
class Solution {
    static const int maxn = 1000;
    vector<int> col = vector<int>(maxn+5, 0);
    vector<int> fa = vector<int>(maxn+5, 0);
    int find(int x) {
        return fa[x]==x ? x : fa[x] = find(fa[x]);
    }
public:
    bool canReachCorner(int xCorner, int yCorner, vector<vector<int>>& circles) {
        auto chk1 = [&](int x, int y, int r, int lxx, int rxx, int yy) -> bool {
            int d = abs(y-yy);
            if(d > r) return false;
            if(lxx<=x && x<=rxx) return true;
            int dd2 = LL(r)*r - LL(d)*d;
            if(x < lxx) return LL(lxx-x)*(lxx-x) <= dd2;
            if(rxx < x) return LL(x-rxx)*(x-rxx) <= dd2;
            assert(false);
        };
        auto chk2 = [&](int x, int y, int r, int xx, int lyy, int ryy) -> bool {
            int d = abs(x-xx);
            if(d > r) return false;
            if(lyy<=y && y<=ryy) return true;
            int dd2 = LL(r)*r - LL(d)*d;
            if(y < lyy) return LL(lyy-y)*(lyy-y) <= dd2;
            if(ryy < y) return LL(y-ryy)*(y-ryy) <= dd2;
            assert(false);
        };
        auto chk11 = [&](int x, int y, int r) -> bool {
            return chk1(x, y, r, 0, xCorner, 0) | chk2(x, y, r, xCorner, 0, yCorner);
        };
        auto chk22 = [&](int x, int y, int r) -> bool {
            return chk1(x, y, r, 0, xCorner, yCorner) | chk2(x, y, r, 0, 0, yCorner);
        };
        auto inter = [&](vector<int> &pt1, vector<int> &pt2) -> bool {
            LL dd2 = LL(pt1[0]-pt2[0])*(pt1[0]-pt2[0]) + LL(pt1[1]-pt2[1])*(pt1[1]-pt2[1]);
            LL rr2 = LL(pt1[2]+pt2[2]) * (pt1[2]+pt2[2]);
            return dd2 <= rr2;
        };
        auto dir = [&](int x1, int y1, int x2, int y2) -> int {
            LL d = LL(x1)*y2 - LL(y1)*x2;
            if(d == 0) return 0;
            if(d > 0) return 1;
            return -1;
        };
        int n = circles.size();
        for(int i = 1; i <= n; ++i) fa[i] = i;
        for(int i = 1; i <= n; ++i) {
            auto &pt = circles[i-1];
            bool fg1 = chk11(pt[0], pt[1], pt[2]);
            bool fg2 = chk22(pt[0], pt[1], pt[2]);
            if(fg1 && fg2) return false;
            if(fg1) col[i] = 1;
            else if(fg2) col[i] = 2;
        }
        for(int i = 1; i <= n; ++i) {
            auto &pt1 = circles[i-1];
            for(int k = i+1; k <= n; ++k) {
                auto &pt2 = circles[k-1];
                if(!inter(pt1, pt2)) continue;
                int fg1 = dir(xCorner-pt1[0], yCorner-pt1[1], pt2[0]-pt1[0], pt2[1]-pt1[1]);
                int fg2 = dir(pt2[0]-pt1[0], pt2[1]-pt1[1], 0-pt1[0], 0-pt1[1]);
                if(fg1*fg2 < 0) continue;
                int x = find(i), y = find(k);
                if(col[x] && col[y] && col[x]!=col[y])
                    return false;
                if(col[x] == col[y]) fa[x] = y;
                else if(col[x]==0) fa[x] = y;
                else fa[y] = x;
            }
        }
        return true;
        
    }
};
