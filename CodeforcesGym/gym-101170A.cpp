#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 40, maxm = 400;

int n, m;
int f[maxm + 2][maxn + 2][maxn + 2][10], nx[maxm + 2][maxn + 2][maxn + 2][10];
char arr[maxn + 2][maxm + 2];

inline int NumCnt(int pos, int l, int r, int num) {
	int res = 0;
	REP(i,l,r)
		res += (arr[i][pos] != num + '0');
	return res;
}

int dfs(int pos, int l, int r, int num) {
	if(pos >= m) return 0;
	if(f[pos][l][r][num] != -1) return f[pos][l][r][num];
	if(num == 9) {
		nx[pos][l][r][num] = r;
		return f[pos][l][r][num] = NumCnt(pos, l, r, num) + dfs(pos+1, l, r, 0);
	}
	int temp;
	nx[pos][l][r][num] = l - 1;
	f[pos][l][r][num] = dfs(pos, l, r, num + 1);
	temp = NumCnt(pos, l, r, num) + dfs(pos+1, l, r, 0);
	if(f[pos][l][r][num] > temp)
		f[pos][l][r][num] = temp, nx[pos][l][r][num] = r;
	for(int i = l; i < r; ++i) {
		temp = NumCnt(pos, l, i, num) + dfs(pos+1, l, i, 0) + dfs(pos, i+1, r, num+1);
		if(f[pos][l][r][num] > temp)
			f[pos][l][r][num] = temp, nx[pos][l][r][num] = i;
	}
	return f[pos][l][r][num];
}

void dfs2(int pos, int l, int r, int num) {
	if(f[pos][l][r][num] == -1) return;
	for(int i = l; i <= nx[pos][l][r][num]; ++i)
		arr[i][pos] = num + '0';
	if(nx[pos][l][r][num] >= l)
		dfs2(pos + 1, l, nx[pos][l][r][num], 0);
	if(nx[pos][l][r][num] < r)
		dfs2(pos, nx[pos][l][r][num] + 1, r, num + 1);
}

int main() {
	scanf("%d%d", &n, &m);
	FOR(i,0,n) scanf("%s", arr[i]);
	mem(f, -1);
	dfs(0, 0, n - 1, 0);
	dfs2(0, 0, n - 1, 0);
	FOR(i,0,n) printf("%s\n", arr[i]);
	return 0;
}
