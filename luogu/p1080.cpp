#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>

using namespace std;
typedef long long LL;

const int maxn = 1000;
const int P = 1e4, fixlen=4;

struct BigInteger {
    int len;
    vector<int> vi;

    BigInteger(const int &x) {
        len = 1;
        vi = vector<int>(1050);
        vi[0] = x;
        while(vi[len-1] >= P) {
            vi[len] = vi[len-1] / P;
            vi[len-1] %= P;
            ++len;
        }
    }

    BigInteger& operator*=(const int &x) {
        vi[0] *= x;
        for(int i = 1; i < len; ++i) {
            vi[i] = vi[i]*x + vi[i-1]/P;
            vi[i-1] %= P;
        }
        while(vi[len-1] >= P) {
            vi[len] = vi[len-1] / P;
            vi[len-1] %= P;
            ++len;
        }
        return *this;
    }

    BigInteger operator/(const int &x) {
        BigInteger res(0);
        int tmp = 0;
        for(int i = len-1; i >= 0; --i) {
            tmp = tmp * P + vi[i];
            res.vi[i] = tmp / x;
            tmp %= x;
        }
        res.len = len;
        while(res.len >= 1 && res.vi[res.len-1] == 0)
            --res.len;
        return res;
    }

    bool operator<(const BigInteger &x) {
        if(len != x.len) return len < x.len;
        for(int i = len-1; i >= 0; --i) {
            if(vi[i] != x.vi[i])
                return vi[i] < x.vi[i];
        }
        return false;
    }

    friend ostream& operator<<(ostream &out, const BigInteger &x) {
        out << x.vi[x.len-1];
        for(int i = x.len-2; i >= 0; --i)
            out << setw(fixlen) << setfill('0') << x.vi[i];
        return out;
    }
};

int n;
vector<int> ai(maxn+5), bi(maxn+5), id(maxn+5);

bool cmp(const int &i, const int &k) {
    return max(ai[i]*bi[i], bi[k]) < max(ai[k]*bi[k], bi[i]);
}

int main() {
    ios::sync_with_stdio(0);
    cin >> n;
    for(int i = 0; i <= n; ++i)
        cin >> ai[i] >> bi[i], id[i] = i;
    sort(id.begin()+1, id.begin()+(1+n), cmp);

    BigInteger ans(0), mul(ai[0]);
    for(int i = 1; i <= n; ++i) {
        BigInteger tmp = mul / bi[id[i]];
        if(ans < tmp) ans = tmp;
        mul *= ai[id[i]];
    }

    cout << ans << "\n";
    return 0;
}
