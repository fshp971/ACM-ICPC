#include<bits/stdc++.h>
//#include<complex>

using namespace std;

#define LL long long
#define MP(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define sf scanf
#define pf printf

typedef complex<double> Comp;
const double PI = acos(-1.0);

const int maxn = 1<<17;

Comp aa[maxn+5], bb[maxn+5];
char arr[maxn+5];
int ans[maxn+5];

void fft(Comp *a, int len, int type)
{
	int i, j, k, l;
	for(i=1, j=len>>1; i<len-1; ++i)
	{
		if(i<j) swap(a[i], a[j]);
		k = len>>1;
		while(j>=k)
			j -= k, k >>= 1;
		j += k;
	}
	Comp var, step, u, v;
	for(l=2; l<=len; l<<=1)
	{
		step = Comp( cos(PI*2 / l * type), sin(PI*2 / l * type) );
		for(k=0; k<len; k+=l)
		{
			var = Comp(1,0);
			for(i=k; i<k+l/2; ++i)
			{
				u = a[i], v = var * a[i+l/2];
				a[i] = u+v;
				a[i+l/2] = u-v;
				var *= step;
			}
		}
	}
	if(type == -1)
		for(i=0; i<len; ++i) a[i] /= len;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int n, m;
	while(~sf("%s", arr))
	{
		mem(aa, 0); mem(bb, 0);
		n = strlen(arr);
		for(int i=n-1; i>=0; --i)
			aa[n-i-1] = Comp(arr[i]-48, 0);
		sf("%s", arr);
		m = strlen(arr);
		for(int i=m-1; i>=0; --i)
			bb[m-i-1] = Comp(arr[i]-48, 0);
		m = n+m, n = 1;
		while(n<m) n <<= 1;
		fft(aa, n, 1);
		fft(bb, n, 1);
		for(int i=0; i<n; ++i) aa[i] *= bb[i];
		fft(aa, n, -1);
		mem(ans, 0);
		for(int i=0; i<n; ++i)
		{
			ans[i+1] += (int)(aa[i].real() + 0.5);
			if(ans[i+1]>=10)
			{
				ans[i+2] = ans[i+1]/10;
				ans[i+1] %= 10;
			}
		}
		while(ans[n+1])
		{
			++n;
			ans[n+1] += ans[n]/10;
			ans[n] %= 10;
		}
		while(!ans[n] && n>1) --n;
		for(int i=n; i>=1; --i) pf("%d", ans[i]);
		pf("\n");
	}
	return 0;
}
