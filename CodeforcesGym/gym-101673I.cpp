#include<bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define FOR(i,a,b) for(int i = a; i < b; ++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
#define PB push_back
#define fi first
#define se second

typedef long long LL;

LL Gcd(LL a, LL b) { return b ? Gcd(b,a%b) : a; }

//opt: 0:+ 1:- 2:* 3:/

LL sta[10];
int hh[10];
bool Calc(LL &res, int tot, vector<LL> &seg, vector<int> &opt) {
    if(tot == 1) { res = seg[0]; return true; }
    int top = 0;
    sta[top++] = seg[0];
    for(int i = 1; i < tot; ++i) {
        if(opt[i-1] <= 1) {
            sta[top] = seg[i], hh[top++] = opt[i-1];
        }
        else if(opt[i-1] == 2) sta[top-1] *= seg[i];
        else {
            if(seg[i] == 0) return false;
            if(sta[top-1] % seg[i]) return false;
            sta[top-1] /= seg[i];
        }
    }
    for(int i = 1; i < top; ++i) {
        if(hh[i] == 0) sta[i] = sta[i-1] + sta[i];
        else sta[i] = sta[i-1] - sta[i];
    }
    res = sta[top-1];
    return true;
}

int ans = 1 << 30;
int num[10];

bool Run1(LL &res, vector<int> &o) { //ABCD
    vector<LL> seg; vector<int> opt;
    seg.resize(4); opt = o;
    seg[0] = num[0], seg[1] = num[1], seg[2] = num[2], seg[3] = num[3];
    return Calc(res,4,seg,opt);
}

bool Run2(LL &res, vector<int> &o) { //(AB)CD
    vector<LL> seg; vector<int> opt;
    seg.resize(2); opt.resize(1); seg[0] = num[0], seg[1] = num[1], opt[0] = o[0];
    if(!Calc(res,2,seg,opt)) return false;
    seg.resize(3); opt.resize(2); seg[0] = res, seg[1] = num[2], seg[2] = num[3], opt[0] = o[1], opt[1] = o[2];
    return Calc(res,3,seg,opt);
}

bool Run3(LL &res, vector<int> &o) { //AB(CD)
    vector<LL> seg; vector<int> opt;
    seg.resize(2); opt.resize(1); seg[0] = num[2], seg[1] = num[3], opt[0] = o[2];
    if(!Calc(res,2,seg,opt)) return false;
    seg.resize(3); opt.resize(2); seg[2] = res, seg[0] = num[0], seg[1] = num[1], opt[0] = o[0], opt[1] = o[1];
    return Calc(res,3,seg,opt);
}

bool Run4(LL &res, vector<int> &o) {
    vector<LL> seg; vector<int> opt;
    seg.resize(2); opt.resize(1); seg[0] = num[1], seg[1] = num[2], opt[0] = o[1];
    if(!Calc(res,2,seg,opt)) return false;
    seg.resize(3); opt.resize(2); seg[1] = res, seg[0] = num[0], seg[2] = num[3], opt[0] = o[0], opt[1] = o[2];
    return Calc(res,3,seg,opt);
}

bool Run5(LL &res, vector<int> &o) {
    vector<LL> seg; vector<int> opt;
    LL r1, r2;
    seg.resize(2); opt.resize(1); seg[0] = num[0], seg[1] = num[1], opt[0] = o[0];
    if(!Calc(r1,2,seg,opt)) return false;
    seg.resize(2); opt.resize(1); seg[0] = num[2], seg[1] = num[3], opt[0] = o[2];
    if(!Calc(r2,2,seg,opt)) return false;
    seg.resize(2); opt.resize(1); seg[0] = r1, seg[1] = r2, opt[0] = o[1];
    return Calc(res,2,seg,opt);
}

bool Run6(LL &res, vector<int> &o) {
    vector<LL> seg; vector<int> opt;
    seg.resize(2); opt.resize(1); seg[0] = num[1], seg[1] = num[2], opt[0] = o[1];
    if(!Calc(res,2,seg,opt)) return false;
    seg.resize(2); opt.resize(1); seg[0] = num[0], seg[1] = res, opt[0] = o[0];
    if(!Calc(res,2,seg,opt)) return false;
    seg.resize(2); opt.resize(1); seg[0] = res, seg[1] = num[3], opt[0] = o[2];
    return Calc(res,2,seg,opt);
}

bool Run7(LL &res, vector<int> &o) {
    vector<LL> seg; vector<int> opt;
    seg.resize(2); opt.resize(1); seg[0] = num[1], seg[1] = num[2], opt[0] = o[1];
    if(!Calc(res,2,seg,opt)) return false;
    seg.resize(2); opt.resize(1); seg[0] = res, seg[1] = num[3], opt[0] = o[2];
    if(!Calc(res,2,seg,opt)) return false;
    seg.resize(2); opt.resize(1); seg[0] = num[0], seg[1] = res, opt[0] = o[0];
    return Calc(res,2,seg,opt);
}

bool Run8(LL &res, vector<int> &o) {
    vector<LL> seg; vector<int> opt;
    seg.resize(2); opt.resize(1); seg[0] = num[0], seg[1] = num[1], opt[0] = o[0];
    if(!Calc(res,2,seg,opt)) return false;
    seg.resize(2); opt.resize(1); seg[0] = res, seg[1] = num[2], opt[0] = o[1];
    if(!Calc(res,2,seg,opt)) return false;
    seg.resize(2); opt.resize(1); seg[0] = res, seg[1] = num[3], opt[0] = o[2];
    return Calc(res,2,seg,opt);
}

bool Run9(LL &res, vector<int> &o) {
    vector<LL> seg; vector<int> opt;
    seg.resize(2); opt.resize(1); seg[0] = num[2], seg[1] = num[3], opt[0] = o[2];
    if(!Calc(res,2,seg,opt)) return false;
    seg.resize(2); opt.resize(1); seg[0] = num[1], seg[1] = res, opt[0] = o[1];
    if(!Calc(res,2,seg,opt)) return false;
    seg.resize(2); opt.resize(1); seg[0] = num[0], seg[1] = res, opt[0] = o[0];
    return Calc(res,2,seg,opt);
}

bool Run10(LL &res, vector<int> &o) {
    vector<LL> seg; vector<int> opt;
    seg.resize(3); opt.resize(2); seg[0]=num[0], seg[1]=num[1], seg[2]=num[2], opt[0] = o[0], opt[1]=o[1];
    if(!Calc(res,3,seg,opt)) return false;
    seg.resize(2); opt.resize(1); seg[0] = res, seg[1] = num[3], opt[0] = o[2];
    return Calc(res,2,seg,opt);
}

bool Run11(LL &res, vector<int> &o) {
    vector<LL> seg; vector<int> opt;
    seg.resize(3); opt.resize(2); seg[0]=num[1], seg[1]=num[2], seg[2]=num[3], opt[0] = o[1], opt[1]=o[2];
    if(!Calc(res,3,seg,opt)) return false;
    seg.resize(2); opt.resize(1); seg[0] = num[0], seg[1] = res, opt[0] = o[0];
    return Calc(res,2,seg,opt);
}

void Upd(int dd) {
    LL res;
    vector<int> opt; opt.resize(3);
    FOR(p1,0,4) FOR(p2,0,4) FOR(p3,0,4) {
        opt[0] = p1, opt[1] = p2, opt[2] = p3;
        int pa = ans;
        if(Run1(res,opt)&&res==24) ans = min(ans,dd);
        if(Run2(res,opt)&&res==24) ans = min(ans,dd+1);
        if(Run3(res,opt)&&res==24) ans = min(ans,dd+1);
        if(Run4(res,opt)&&res==24) ans = min(ans,dd+1);
        if(Run5(res,opt)&&res==24) ans = min(ans,dd+2);
        if(Run6(res,opt)&&res==24) ans = min(ans,dd+2);
        if(Run7(res,opt)&&res==24) ans = min(ans,dd+2);
        if(Run8(res,opt)&&res==24) ans = min(ans,dd+2);
        if(Run9(res,opt)&&res==24) ans = min(ans,dd+2);
        if(Run10(res,opt)&&res==24) ans = min(ans,dd+1);
        if(Run11(res,opt)&&res==24) ans = min(ans,dd+1);
    }
}

int cnt[24] = {0,1,1,2,2,3,1,2,2,3,3,4,2,3,3,4,4,5,3,4,4,5,5,6};
int fk[10];

int main() {
    FOR(i,0,4) scanf("%d", fk + i);
    int T = 0;
    for(int i = 0; i < 4; ++i) {
        for(int k = 0; k < 4; ++k) {
            if(i == k) continue;
            for(int j = 0; j < 4; ++j) {
                if(j==i || j==k) continue;
                for(int t = 0; t < 4; ++t) {
                    if(t==i || t==k || t==j) continue;
                    num[0] = fk[i], num[1] = fk[k], num[2] = fk[j], num[3] = fk[t];
                    Upd(cnt[T]<<1); ++T;
                }
            }
        }
    }
    if(ans == (1 << 30)) puts("impossible");
    else printf("%d\n", ans);
    return 0;
}
