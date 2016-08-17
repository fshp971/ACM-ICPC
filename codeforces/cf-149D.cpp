#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))
#define MP(a,b) make_pair(a,b)
#define sf scanf
#define pf printf

const int maxn = 700;
const int md = 1e9 + 7;

struct Node
{
	LL res[3][3];
}sta2[maxn+2];

char arr[maxn+2];
int n;
int sta1[maxn+2];
int top1, top2;

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	sf("%s", arr);
	n = strlen(arr);
	top1 = top2 = 0;
	for(int t=1; t<=n; ++t)
	{
		if(arr[t-1] == '(') sta1[++top1] = 1;
		else
		{
			if(sta1[top1] == 1)
			{
				sta1[top1] = 2;
				++top2;
				mem(sta2[top2].res, 0);
				sta2[top2].res[0][1] = sta2[top2].res[1][0] = 1;
				sta2[top2].res[0][2] = sta2[top2].res[2][0] = 1;
			}
			else
			{
				sta1[--top1] = 2;
				Node now;
				mem(now.res, 0);
				Node &pre = sta2[top2];
				for(int i=0; i<3; ++i)
					for(int k=0; k<3; ++k)
					{
						if(i!=1)
							now.res[1][0] = (now.res[1][0]+pre.res[i][k])%md;
						if(i!=2)
							now.res[2][0] = (now.res[2][0]+pre.res[i][k])%md;
						if(k!=1)
							now.res[0][1] = (now.res[0][1]+pre.res[i][k])%md;
						if(k!=2)
							now.res[0][2] = (now.res[0][2]+pre.res[i][k])%md;
					}
				sta2[top2] = now;
			}
		}
		while(top1>=2 && sta1[top1]==2 && sta1[top1-1]==2)
		{
			Node &t1 = sta2[top2-1], &t2 = sta2[top2];
			--top1, --top2;
			Node now;
			mem(now.res, 0);
			for(int i=0; i<3; ++i)
				for(int k=0; k<3; ++k)
				{
					for(int j1=0; j1<3; ++j1)
						for(int j2=0; j2<3; ++j2)
						{
							if(j1 && j2 && j1==j2) continue;
							now.res[i][k] = (now.res[i][k] + t1.res[i][j1]*t2.res[j2][k]%md) % md;
						}
				}
			sta2[top2] = now;
		}
	}
	LL ans = 0;
	FOR(i,0,3) FOR(k,0,3) ans = (ans+sta2[1].res[i][k]) % md;
	cout << ans << "\n";
	return 0;
}
