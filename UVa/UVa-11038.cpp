#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<iostream>
#include<algorithm>
#include<queue>
#include<string>
#include<utility>
#include<map>
#include<set>
#include<vector>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define MP(a,b) make_pair(a,b)
#define LL long long
#define pii pair<int,int>
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define sf scanf
#define pf printf

const int max_len = 11;

LL ten[max_len+2], f[max_len+2];

void run()
{
	ten[0] = 1;
	REP(i,1,max_len) ten[i] = ten[i-1] * 10;
	f[1] = f[2] = 1;
	REP(i,3,max_len) f[i] = ten[i-2] + f[i-1] * 10;
	/*REP(i,1,max_len)
	{
		printf("f[%d] = %lld\n",i,f[i]);
	}
	printf("\n--------------------------\n\n");*/
	return;
}

LL cal(LL x)
{
	if(x < 0) return 0;
	if(x < 10) return 1;
	int len = 2;
	LL res = 1, tmp = 0;
	while(ten[len]-1 < x)
	{
		res += f[len] * 9;
		++len;
	}
	//printf("len = %d\n",len);
	//printf("res = %d\n",res);
	for(int i = len; i>=2; --i)
	{
		int t = 0;
		while(ten[i-1]*(t+1) <= x) ++t;
		//printf("t = %d, x = %lld\n",t,x);
		x -= ten[i-1]*t;
		//printf("t = %d, x = %lld\n",t,x);
		if(!t) res += x+1;
		else
		{
			if(i != len)
				res += f[i] + ten[i-1];
			//printf("res1 = %lld\n",res);
			res += f[i]*(t-1);
			//printf("res2 = %lld\n",res);
		}
		/*res += tmp+1;
		//printf("res = %lld, i = %d\n",res,i);
		tmp += x % 10 * ten[i-1];
		printf("tmp = %lld\n",tmp);
		x /= 10;*/
	}
	++res;
	//printf("x = %lld\n",x);
	//res += (x-1) * f[len];
	/*while(x > 0)
	{
		res += tmp;
		tmp = tmp*10 + x%10;
		x /= 10;
	}*/
	return res;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	LL a,b;
	run();
	/*while(1)
	{
		cin>>a;
		printf("cal(%lld) = %lld\n",a,cal(a));
		printf("\n---------------------------\n\n");
	}*/
	while(cin>>a>>b, a!=-1)
	{
		//printf("cal(%lld) = %lld\n",a-1,cal(a-1));
		//printf("cal(%lld) = %lld\n",b,cal(b));
		//printf("\n---------------------------\n\n");
		cout << cal(b) - cal(a-1) << "\n";
	}
	return 0;
}
