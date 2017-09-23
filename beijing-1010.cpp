#include<bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define FOR(i,a,b) for(int i = a; i < b; ++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int md = 1e9 + 7;
//const int base = 823543;
const int base = 16777216;
//const int maxm = base * 8;

int dest;
int ans, T;
//int f[maxm + 5];
//char vist[maxm + 5];
bool ffg[10];
char b[15];

unordered_map<int,int> Hash;

inline int GetHash(char *a, int &len, int pt) {
	int res = 0;
	for(int i = 0; i < len; ++i)
		res = res * 8 + a[i] - 'a' + 1;
	//return res;
	//printf("a = %s, now res = %d\n", a, res);
	return pt * base + res;
}

void dfs(char *a, int len, int pt, int dis) {
	int haha = GetHash(a,len,pt);
	//if(strcmp(a, b) == 0)
	//printf("a = %s, dis = %d\n", a, dis);
	if(haha % base == dest) {
		//printf("a = %s, len = %d, dest = %d, haha%%base = %d\n", a, len, dest, haha%base);
		ans = dis;
		return;
	}
	//if(vist[haha] == T && f[haha] <= dis) return;
	if(Hash.count(haha) && Hash[haha] <= dis) return;
	//vist[haha] = T, f[haha] = dis;
	Hash[haha] = dis;

	if(dis + 1 >= ans) return;
	if(pt > 0) dfs(a, len, pt - 1, dis + 1);
	if(pt < len) dfs(a, len, pt + 1, dis + 1);

	if(dis + 2 >= ans) return;
	if(len >= 0) {
		if(pt - 1 >= 0) {
			//printf("begin: a = %s, pt = %d\n", a, pt);
			char c = a[pt - 1];
			for(int i = pt - 1; i < len; ++i)
				a[i] = a[i + 1];
			--len;
			//printf("sta: a = %s, pt = %d\n", a, pt);
			dfs(a, len, pt - 1, dis + 2);
			for(int i = len; i >= pt; --i)
				a[i] = a[i - 1];
			++len, a[pt - 1] = c;
			//printf("end: a = %s, pt = %d\n", a, pt);
		}
		if(pt < len) {
			//printf("begin: a = %s, pt = %d\n", a, pt);
			char c = a[pt];
			for(int i = pt; i < len; ++i)
				a[i] = a[i + 1];
			--len;
			//printf("sta: a = %s, pt = %d\n", a, pt);
			dfs(a, len, pt, dis + 2);
			for(int i = len; i >= pt + 1; --i)
				a[i] = a[i - 1];
			++len, a[pt] = c;
			//printf("end: a = %s, pt = %d\n", a, pt);
		}
	}
	if(len < 7) {
		//printf("begin: %s, pt = %d\n", a, pt);
		mem(ffg, 0);
		for(int i = 0; i < len; ++i)
			ffg[a[i] - 'a'] = 1;
		//printf("done1: len = %d, pt = %d\n", len, pt);
		for(int i = len; i >= pt + 1; --i) {
			a[i] = a[i - 1];
		}
		++len;
		for(int k = 0; k < 7 && dis + 2 < ans; ++k) {
			if(!ffg[k]) {
				a[pt] = k + 'a';
				//printf("sta: %s, pt = %d\n", a, pt);
				//printf("end: %s\n", a);
				//continue;
				dfs(a, len, pt + 1, dis + 2);
			}
		}
		for(int i = pt; i <= len; ++i)
			a[i] = a[i + 1];
		--len;
		//printf("end: %s, pt = %d\n\n", a, pt);
	}
}

int main() {
	int pt, len;
	char a[10];//, b[10];
	//T = 0;
	while(~scanf("%s%d%s", a, &pt, b)) {
		//++T;
		Hash.clear();
		len = strlen(b);
		mem(ffg, 0);
		bool hh = true;
		for(int i = 0; i < len; ++i) {
			if(ffg[i]) { hh = false; break; }
			ffg[i] = b[i] - 'a';
		}
		if(!hh) {
			printf("-1\n");
			continue;
		}
		dest = GetHash(b, len, 0);
		//printf("len = %d, dest = %d\n", len, dest);
		ans = len;
		len = strlen(a);
		ans += len;
		ans *= 2;
		dfs(a, len, pt, 0);
		printf("%.1f\n", ans/2.0);
	}
	return 0;
}
