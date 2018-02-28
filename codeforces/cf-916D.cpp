#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e5, MaxStep = 30;
const int maxnode = maxn * (MaxStep+2) * 2;

int tot = 0, rot[maxn + 5];
int nx[maxnode + 5][2], cnt[maxnode + 5];

int Upd(int px, int vv, int pp, int del) {
    int x = ++tot;
    nx[x][0] = nx[px][0], nx[x][1] = nx[px][1], cnt[x] = cnt[px]+del;
    if(pp < 0) return x;
    int t = vv>>pp&1;
    nx[x][t] = Upd(nx[px][t], vv, pp-1, del);
    return x;
}

int Query(int x, int vv, int pp) {
    if(pp < 0) return 0;
    int t = vv>>pp&1, rem = 0;
    if(t) rem += cnt[ nx[x][0] ];
    rem += Query(nx[x][t], vv, pp-1);
    return rem;
}

int tot2 = 0, rot2[maxn + 5];
int nx2[maxnode + 5][2], col[maxnode + 5];

int Upd2(int px, int vv, int pp, int ccc) {
    int x = ++tot2;
    nx2[x][0] = nx2[px][0], nx2[x][1] = nx2[px][1];
    if(pp < 0) { col[x] = ccc; return x; }
    int t = vv>>pp&1;
    nx2[x][t] = Upd2(nx2[px][t], vv, pp-1, ccc);
    return x;
}

int Query2(int x, int vv, int pp) {
    if(pp < 0) return col[x];
    int t = vv>>pp&1;
    if(nx2[x][t]) return Query2(nx2[x][t], vv, pp-1);
    return 0;
}

map<string, int> Id;
int GetId(char *buf) {
    static int iid = 0;
    string str(buf);
    if(Id.find(str) == Id.end()) Id[str] = iid++;
    return Id[str];
}

int main() {
    int T, id, x, dd;
    char ord[10], buf[30];
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%s", ord);
        if(ord[0] == 's') {
            scanf("%s%d", buf, &x);
            id = GetId(buf);
            int be = Query2(rot2[t-1], id, MaxStep-1), rt = rot[t-1];
            if(be) rt = Upd(rt, be, MaxStep-1, -1);
            rot[t] = Upd(rt, x, MaxStep-1, 1);
            rot2[t] = Upd2(rot2[t-1], id, MaxStep-1, x);
        }
        else if(ord[0] == 'r') {
            scanf("%s", buf);
            id = GetId(buf);
            int be = Query2(rot2[t-1], id, MaxStep-1);
            if(be) {
                rot[t] = Upd(rot[t-1], be, MaxStep-1, -1);
                rot2[t] = Upd2(rot2[t-1], id, MaxStep-1, 0);
            }
            else rot[t] = rot[t-1], rot2[t] = rot2[t-1];
        }
        else if(ord[0] == 'q') {
            rot[t] = rot[t-1], rot2[t] = rot2[t-1];
            scanf("%s", buf);
            id = GetId(buf);
            int be = Query2(rot2[t-1], id, MaxStep-1);
            printf("%d\n", be ? Query(rot[t-1], be, MaxStep-1) : -1);
            fflush(stdout);
        }
        else {
            scanf("%d", &dd);
            rot[t] = rot[t-dd-1], rot2[t] = rot2[t-dd-1];
        }
    }
    return 0;
}
