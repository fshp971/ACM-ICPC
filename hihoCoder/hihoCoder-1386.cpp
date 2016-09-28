#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define MP(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define PER(i,a,b) for(int i=a; i>=b; --i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define sf scanf
#define pf printf

const int maxn = 500;
const int maxN = 1e9;

struct Node
{
	int type, val, cost;
	Node(): type(0), val(0), cost(0){}
	Node(int _type, int _val, int _cost)
	{
		type = _type, val = _val, cost = _cost;
	}
	bool operator<(const Node &a)const
	{
		return val > a.val;
	}
}arr[maxn+5];

int n, lim;
int f[1005][6][6][4], g[1005][6][6][4];

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int T, type, val, cost, N, top;
	char name[20];
	sf("%d", &T);
	while(T--)
	{
		sf("%d", &n);
		mem(f, 0), mem(g, 0);
		top = 0;
		REP(i,1,n)
		{
			sf("%s", name);
			sf("%d%d", &val, &cost);
			if(name[0] == 'G')
			{
				if(val > f[cost][0][0][0])
				{
					f[cost][0][0][0] = val;
					g[cost][0][0][0] = 1;
				}
				else if(val == f[cost][0][0][0])
					++g[cost][0][0][0];
				continue;
			}
			else if(name[0] == 'D') type = 2;
			else if(name[0] == 'M') type = 3;
			else type = 4;
			arr[++top] = Node(type, val, cost);
		}
		sf("%d", &lim);
		sort(arr+1, arr+1+top);
		for(int p=1; p<=top; ++p)
		{
			Node &e = arr[p];
			PER(c,lim,e.cost)
			{
				PER(j,5,0)
				{
					PER(k,5,0) PER(l,3,0)
					{
						int tc = c-e.cost, tj = j, tk = k, tl = l;
						if(e.type == 2) --tj;
						else if(e.type == 3) --tk;
						else --tl;
						if(tj<0 || tk<0 || tl<0) continue;
						if(!g[tc][tj][tk][tl]) continue;
						int tf = f[tc][tj][tk][tl] + e.val;
						if(tj==0 && tk==0 && tl==0)
						{
							if(e.val > f[tc][tj][tk][tl])
								tf += e.val;
							else tf += f[tc][tj][tk][tl];
						}
						if(tf > f[c][j][k][l])
						{
							f[c][j][k][l] = tf;
							g[c][j][k][l] = g[tc][tj][tk][tl];
						}
						else if(tf == f[c][j][k][l])
						{
							g[c][j][k][l] += g[tc][tj][tk][tl];
							g[c][j][k][l] = min(g[c][j][k][l], maxN);
							/*
							if(g[c][i][j][k][l] > maxN)
								g[c][i][j][k][l] = maxN;
							*/
						}
					}
				}
			}
		}
		val = -1, cost = -1, N = 0;
		REP(c,0,lim)
		{
			REP(j,3,5) REP(k,2,5)
			{
				int l = 10 - j - k;
				if(l<1 || l>3) continue;
				/*
				if(l>3) continue;
				if(l<1) break;
				*/
				if(!g[c][j][k][l]) continue;
				if(f[c][j][k][l] > val)
				{
					val = f[c][j][k][l];
					cost = c;
					N = g[c][j][k][l];
				}
				else if(f[c][j][k][l] == val && c == cost)
				{
					N += g[c][j][k][l];
					N = min(N, maxN);
					//if(N > maxN) n = maxN;
				}
			}
		}
		pf("%d %d %d\n", val, cost, N);
	}
	return 0;
}
