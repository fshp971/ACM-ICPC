#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

#define fi first
#define se second

const int maxn = 500;
const int MaxTop = 500 * 500;
LL md = 1e9 + 7;

int inv[5] = {0, 1, 3, 2, 4};
int A[maxn + 2][maxn + 2], B[maxn + 2];

int opt[MaxTop + 2], key[MaxTop + 2], top, zero;
pii sta[MaxTop + 2];

int Gauss(int n, int m) {
	top = 0;
	int row = 0, col = 0;
	for(int i = 0; i < m; ++i) {
		if(A[row][i] == 0) {
			int r = row;
			for(int j = r + 1; j < n; ++j)
				if(A[j][i]) { r = j; break; }
			if(r != row) {
				opt[top] = 2, sta[top++] = MP(r, row);
				for(int j = 0; j < m; ++j)
					swap(A[row][j], A[r][j]);
			}
			else continue;
		}
		for(int j = row + 1; j < n; ++j) {
			opt[top] = 1, sta[top] = MP(row, j);
			key[top] = inv[A[row][i]] * (5 - A[j][i]) % 5;
			for(int k = m - 1; k >= i; --k)
				A[j][k] = (A[j][k] + key[top] * A[row][k]) % 5;
			++top;
		}
		++row;
		if(row == n) break;
	}
	zero = 0;
	for(int i = n - 1; i >= 0; --i) {
		int fg = 1;
		for(int k = 0; k < m; ++k)
			if(A[i][k]) { fg = 0; break; }
		if(!fg) break;
		++zero;
	}
	return max(0, m - (n - zero));
}

int main() {
	char str[maxn + 2];
	int n, m, T;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i) {
		scanf("%s", str);
		for(int k = 0; k < m; ++k)
			A[k][i] = str[k] - 'a';
	}
	int Rem = Gauss(m, n), ans = 1;
	for(int i = 1; i <= Rem; ++i)
		ans = ans * LL(5) % md;
	scanf("%d", &T);
	while(T--) {
		scanf("%s", str);
		for(int i = 0; i < m; ++i)
			B[i] = str[i] - 'a';
		for(int i = 0; i < top; ++i) {
			if(opt[i] == 1)
				B[sta[i].se] = (B[sta[i].se] + B[sta[i].fi] * key[i]) % 5;
			else
				swap(B[sta[i].fi], B[sta[i].se]);
		}
		int fg = 1;
		for(int i = 1; i <= zero; ++i)
			if(B[m - i]) { fg = 0; break; }
		printf("%d\n", fg ? ans : 0);
	}
	return 0;
}
