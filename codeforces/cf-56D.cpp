#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define MP(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define sf scanf
#define pf printf

const int maxn = 1000;

int n, m;
int f[maxn+5][maxn+5];
int pre[maxn+5][maxn+5], type[maxn+5][maxn+5];
char aa[maxn+5], bb[maxn+5];

char ord[3][10] = {"INSERT", "DELETE", "REPLACE"};

int wd[maxn*2+5], poi[maxn*2+5];
char word[maxn*2+5];

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	sf("%s%s", aa, bb);
	n = strlen(aa), m = strlen(bb);
	mem(f, 0x7f); mem(type, 0);
	f[0][0] = 0;
	REP(i,1,n) f[i][0] = i, type[i][0] = 2, pre[i][0] = (i-1)*10000;
	REP(k,1,m) f[0][k] = k, type[0][k] = 1, pre[0][k] = k-1;
	for(int k=1; k<=m; ++k)
	{
		for(int i=1; i<=n; ++i)
		{
			//type 3: replace
			if(aa[i-1] == bb[k-1])
			{
				if(f[i][k] > f[i-1][k-1])
				{
					f[i][k] = f[i-1][k-1];
					pre[i][k] = (i-1)*10000 + (k-1);
					type[i][k] = 0;
				}
			}
			else if(f[i][k] > f[i-1][k-1]+1)
			{
				f[i][k] = f[i-1][k-1] + 1;
				pre[i][k] = (i-1)*10000 + (k-1);
				type[i][k] = 3;
			}

			//type 1: insert
			if(f[i][k] > f[i][k-1]+1)
			{
				f[i][k] = f[i][k-1] + 1;
				pre[i][k] = i*10000 + (k-1);
				type[i][k] = 1;
			}

			//type 2: delete
			if(f[i][k] > f[i-1][k]+1)
			{
				f[i][k] = f[i-1][k] + 1;
				pre[i][k] = (i-1)*10000 + k;
				type[i][k] = 2;
			}
		}
	}

	pf("%d\n", f[n][m]);
	int tn = n, tm = m, tmp;
	while(tn || tm)
	{
		int &x = f[tn][tm];
		if(type[tn][tm] == 3)
			wd[x] = 2, poi[x] = tm, word[x] = bb[tm-1];
		else if(type[tn][tm] == 1)
			wd[x] = 0, poi[x] = tm, word[x] = bb[tm-1];
		else if(type[tn][tm] == 2)
			wd[x] = 1, poi[x] = tm+1;
		tmp = pre[tn][tm];
		tn = tmp/10000, tm = tmp%10000;
	}
	REP(i,1,f[n][m])
		if(wd[i] != 1)
			pf("%s %d %c\n", ord[wd[i]], poi[i], word[i]);
		else pf("%s %d\n", ord[wd[i]], poi[i]);
	return 0;
}
