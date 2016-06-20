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

const int maxn = 100000;

struct Line
{
	LL A, B, C;
	
	LL check(LL x, LL y)
	{
		return A*x + B*y + C;
	}

	double dis(double x, double y)
	{
		return fabs(x*A + y*B + C) / sqrt(pow(A,2.0) + pow(B,2.0));
	}
};

int n;
LL ax[maxn+10], ay[maxn+10];
pair<long double, int> type1[maxn+10], type2[maxn+10];

double cal_dis(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x1-x2, 2.0) + pow(y1-y2, 2.0));
}

void init()
{
	cin >> n;
	Line lt;
	int top1 = 0, top2 = 0;
	REP(i,1,n) cin >> ax[i] >> ay[i];

	int xx = 2;
	double tmp_dis = cal_dis(ax[1], ay[1], ax[2], ay[2]);

	lt.A = ay[1]-ay[2]; lt.B = ax[2]-ax[1]; lt.C = ax[1]*ay[2] - ax[2]*ay[1];
	//pf("A = %lld, B = %lld, C = %lld\n", lt.A, lt.B, lt.C);
	REP(i,3,n)
	{
		LL tp = lt.check(ax[i], ay[i]);
		if(!tp)
		{
			double tt = cal_dis(ax[1], ay[1], ax[i], ay[i]);
			if(tt < tmp_dis)
			{
				tmp_dis = tt;
				xx = i;
			}
		}
		else if(tp>0)
		{
			//pf("dasfs\n");
			type1[++top1].first = lt.dis(ax[i], ay[i]);
			type1[top1].second = i;
		}
		else
		{
			type2[++top2].first = lt.dis(ax[i], ay[i]);
			type2[top2].second = i;
		}
	}
	//pf("top1 = %d, top2 = %d\n", top1, top2);
	if(top1)
	{
		sort(type1+1, type1+1+top1);
		/*REP(i,1,top1)
		{
			cout << "dis[" << i << "] = " << type1[i].first << ", num[" << i << "] = " << type1[i].second << endl;
		}*/
		//cout << "dis = " << type1[1].first << endl;
		pf("1 %d %d\n", xx, type1[1].second);
	}
	else
	{
		sort(type2+1, type2+1+top2);
		/*REP(i,1,top2)
		{
			cout << "dis[" << i << "] = " << type2[i].first << ", num[" << i << "] = " << type2[i].second << endl;
		}*/
		//cout << "dis = " << type2[1].first << endl;
		pf("1 %d %d\n", xx, type2[1].second);
	}
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
