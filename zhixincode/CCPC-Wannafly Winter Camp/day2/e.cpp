#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define PER(i,a,b) for(int i = a; i >= b; --i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;

const int maxn = 65;

LL kk, l, r;
LL n1[maxn+5], n2[maxn+5];
LL pw[maxn+5];
int len1, len2;

int main() {
    int __; scanf("%d", &__);
    for(int _ = 1; _ <= __; ++_) {
        scanf("%lld%lld%lld", &kk, &l, &r);
        mem(n1,0); mem(n2,0);
        len1 = len2 = 0;
        while(l) n1[++len1] = l%kk, l/=kk;
        while(r) n2[++len2] = r%kk, r/=kk;
        pw[0] = 1;
        for(int i = 1; i <= len2; ++i) pw[i] = pw[i-1]*kk;

        LL m, a, b;
        LL tm, ta, tb;
        bool fg, fg1, fg2, bg;

        // calc m and maximum n
        m = 0, b = 0, tm = 0, tb = 0;
        fg = 1;
        for(int i = len2; i >= 1; --i) {
            fg = fg && n1[i]==n2[i];
            if(!fg) {
                LL tmp = tm + (n2[i]-1+1) + (i-1)*kk;
                if(i==len2 && n2[i]-1==0) --tmp;
                if(m<=tmp) m = tmp, b = tb + (n2[i]-1)*pw[i-1] + (pw[i-1]-1);
            }
            tm += (n2[i]+1);
            tb += n2[i]*pw[i-1];
        }
        if(m<=tm) m = tm, b = tb;

        // calc m and minimum n
        tm = 0, a = 0;
        fg1 = 1, fg2 = 1, bg = 0;
        for(int i = len2; i >= 1; --i) {
            LL c = -1;
            if(fg1) {
                if(fg2 && n1[i]==n2[i]) c = n1[i];
                else {
                    LL tmp = tm + (n1[i]+1) + (i-1)*kk;
                    if(!bg && n1[i]==0) --tmp;
                    if(tmp == m) c = n1[i];
                }
            }
            if(c==-1) {
                LL r = fg2 ? n2[i]-1 : kk-1;
                if(r>=0) {
                    LL tmp = tm + (r+1) + (i-1)*kk;
                    if(!bg && r==0) --tmp;
                    if(tmp == m) c = r;
                }
            }
            if(c==-1) c = n2[i];
            fg1 = fg1 && c==n1[i];
            fg2 = fg2 && c==n2[i];
            bg = bg || c;
            a += c * pw[i-1];
            tm += bg ? (c+1) : 0;
        }
        printf("Case #%d: %lld %lld %lld\n", _, m-2, a, b);
    }
    return 0;
}
