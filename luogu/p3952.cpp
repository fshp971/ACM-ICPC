#include<bits/stdc++.h>

using namespace std;
typedef long long LL;

const int maxl = 100;

int L, use[30], sta[maxl+5], ooo[maxl+5];
string cpx, ss[maxl+5];

int order() {
    int pt = 4, res = 0;
    while('0' <= cpx[pt] && cpx[pt] <= '9')
        res = res*10 + cpx[pt++] - '0';
    return res;
}

int parse() {
    memset(use, 0, sizeof(use));
    int ft = 0, od = 0, cod = 0, zero = 0;
    for(int i = 1; i <= L; ++i) {
        if(ss[i][0] == 'F') {
            int pt = 1;
            while(ss[i][pt] == ' ') ++pt;
            if(use[ss[i][pt]-'a']) return -1;

            sta[++ft] = ss[i][pt]-'a';
            use[ss[i][pt]-'a'] = 1;
            ++pt;

            while(ss[i][pt] == ' ') ++pt;

            int x = 0, y = 0;

            if(ss[i][pt] == 'n') ++pt;
            else {
                while('0'<=ss[i][pt] && ss[i][pt]<='9')
                    x = x * 10 + ss[i][pt++] - '0';
            }

            while(ss[i][pt] == ' ') ++pt;
            if(ss[i][pt] == 'n') ++pt;
            else {
                while(pt < ss[i].size() && '0'<=ss[i][pt] && ss[i][pt]<='9')
                    y = y * 10 + ss[i][pt++] - '0';
            }

            if(x==0 && y==0) ooo[ft] = 0;
            else if(x==0 && y!=0) ooo[ft] = -1, zero += 1;
            else if(x!=0 && y==0) ooo[ft] = 1, cod += 1;
            else if(x <= y) ooo[ft] = 0;
            else ooo[ft] = -1, zero += 1;
            if(!zero) od = max(od, cod);
        }
        else {
            if(ft == 0) return -1;
            use[sta[ft]] = 0;
            if(ooo[ft] == -1) --zero;
            else if(ooo[ft] == 1) cod -= ooo[ft];
            --ft;
        }
    }
    if(ft) return -1;
    return od;
}

int main() {
    ios::sync_with_stdio(0);
    int _; cin >> _;
    while(_--) {
        cin >> L >> cpx;
        getline(cin, ss[0]);
        for(int i = 1; i <= L; ++i) getline(cin, ss[i]);
        // cout << ss[1] << "\n";
        // cout << ss[2] << "\n";
        int o = parse();
        if(o < 0) cout << "ERR\n";
        else if(o == order()) cout <<"Yes\n";
        else cout <<"No\n";
    }
    return 0;
}
