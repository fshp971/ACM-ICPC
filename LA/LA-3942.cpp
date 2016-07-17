#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define MP(a,b) make_pair(a,b)
#define pii pair<int,int>
#define sf scanf
#define pf printf

const int md = 20071027;
const int max_size = 4000 * 100;

struct Tire
{
	int sum[max_size], nex[max_size][27], size;
	int res[300010];
	void clear(){ size = 0; mem(nex[0], 0); }
	void insert(int x, char* tar)
	{
		if(*(tar) == '\0')
			++sum[x];
		else
		{
			int t = *(tar) - 97;
			if(!nex[x][t])
			{
				nex[x][t] = (++size);
				sum[size] = 0; mem(nex[size], 0);
			}
			insert(nex[x][t], tar+1);
		}
	}
	void cal(int x, char* tar, int now, int pp)
	{
		res[now] = (res[now] + sum[x] * res[pp] % md) % md;
		//pf("*tar = %c, sum[%d] = %d\n", *tar, x, sum[x]);
		if(*(tar) != '\0')
		{
			int t = *(tar) - 97;
			if(nex[x][t])
				cal(nex[x][t], tar+1, now, pp+1);
		}
		return;
	}
}tree;

int n;
char arr[300010];

int init()
{
	sf("%d", &n);
	char aa[110];
	tree.clear();
	REP(i,1,n)
	{
		sf("%s", aa);
		tree.insert(0, aa);
	}
	mem(tree.res, 0);
	tree.res[strlen(arr)] = 1;
	for(int i=strlen(arr)-1; i>=0; --i)
	{
		tree.cal(0, arr+i, i, i);
		/*REP(k,0,strlen(arr))
		{
			pf("res[%d] = %d\n", k, tree.res[k]);
		}
		pf("\n");*/
	}
	//pf("tree.sum[0] = %d\n", tree.sum[0]);
	return tree.res[0];
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int t = 0;
	while(~sf("%s", arr))
		pf("Case %d: %d\n", ++t, init());
	return 0;
}
