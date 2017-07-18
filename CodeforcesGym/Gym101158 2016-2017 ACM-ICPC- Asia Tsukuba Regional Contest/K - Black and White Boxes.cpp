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

const int maxm = 1 << 20;

int n;
LL half[50];
pair<LL, int> arr[50], seqA[maxm + 2], seqB[maxm + 2];

LL Calc(char *wd) {
	int len = strlen(wd), pos = 0, cnt = 1;
	LL res = 0;
	while(wd[pos] == wd[0] && pos < len)
		res += (wd[0] == 'W') ? half[0] : -half[0], ++pos;
	while(pos < len) {
		res += (wd[pos] == 'W') ? half[cnt] : -half[cnt];
		++pos, ++cnt;
	}
	return res;
}

int main() {
	half[40] = 1;
	for(int i = 39; i >= 0; --i)
		half[i] = half[i+1] * 2;

	char wd[100];
	scanf("%d", &n);
	REP(i,1,n) {
		scanf("%s", wd);
		arr[i] = MP( Calc(wd), strlen(wd) );
	}

	int n1 = n/2, n2 = n - n1;
	for(int i = 0; i < (1 << n1); ++i) {
		for(int j = 1; j <= n1; ++j)
			if(i & (1 << (j-1) ) )
				seqA[i].fi += arr[j].fi, seqA[i].se += arr[j].se;
	}
	for(int i = 0; i < (1 << n2); ++i) {
		for(int j = 1; j <= n2; ++j)
			if(i & (1 << (j-1) ) )
				seqB[i].fi += arr[n1 + j].fi, seqB[i].se += arr[n1 + j].se;
	}
	sort(seqA, seqA + (1 << n1));
	sort(seqB, seqB + (1 << n2));

	int ans = 0;
	n1 = 1 << n1, n2 = (1 << n2) - 1;
	for(int i = 0; i < n1; ++i) {
		while(n2 >= 0 && seqA[i].fi + seqB[n2].fi > 0)
			--n2;
		if(n2 < 0) break;
		while(i + 1 < n1 && seqA[i].fi == seqA[i + 1].fi)
			++i;
		if(seqA[i].fi + seqB[n2].fi == 0)
			ans = max(ans, seqA[i].se + seqB[n2].se);
	}
	printf("%d\n", ans);
	return 0;
}
