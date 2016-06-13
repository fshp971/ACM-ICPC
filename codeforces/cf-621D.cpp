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

#define LD long double

string aa[] = {"x^y^z",
			   "x^z^y",
			   "(x^y)^z",
			   "(x^z)^y",
			   "y^x^z",
			   "y^z^x",
			   "(y^x)^z",
			   "(y^z)^x",
			   "z^x^y",
			   "z^y^x",
			   "(z^x)^y",
			   "(z^y)^x"
			  };

//x^y^z
LD cal_t1(LD x, LD y, LD z)
{
	/*pf("type1\n");
	cout << "x = " << x << ", y = " << y << ", z = " << z << endl;
	LD now = logl(logl(x)) + logl(y) * z;
	cout << " now = " << now << endl << endl;*/
	//return logl(logl(x)) + logl(y) * z;
	return pow(y, z) * log(x);
}

//(x^y)^z
LD cal_t2(LD x, LD y, LD z)
{
	/*pf("type2\n");
	cout << "x = " << x << ", y = " << y << ", z = " << z << endl;
	LD now = logl(log(x)) + logl(y*z);
	cout << " now = " << now << endl << endl;*/
	//return logl(logl(x)) + logl(y*z);
	return y*z * log(x);
}

void init()
{
	//FOR(i,0,12) cout << aa[i] << endl;
	LD x, y, z;
	cin >> x >> y >> z;
	int ans = 1;
	LD tmp = cal_t1(x, y, z), now;
	if(tmp < (now = cal_t1(x, z, y))) ans = 2, tmp = now;

	if(tmp < (now = cal_t2(x, y, z))) ans = 3, tmp = now;
	if(tmp < (now = cal_t2(x, z, y))) ans = 4, tmp = now;

	if(tmp < (now = cal_t1(y, x, z))) ans = 5, tmp = now;
	if(tmp < (now = cal_t1(y, z, x))) ans = 6, tmp = now;

	if(tmp < (now = cal_t2(y, x, z))) ans = 7, tmp = now;
	if(tmp < (now = cal_t2(y, z, x))) ans = 8, tmp = now;

	if(tmp < (now = cal_t1(z, x, y))) ans = 9, tmp = now;
	if(tmp < (now = cal_t1(z, y, x))) ans = 10, tmp = now;

	if(tmp < (now = cal_t2(z, x, y))) ans = 11, tmp = now;
	if(tmp < (now = cal_t2(z, y, x))) ans = 12, tmp = now;

	cout << aa[ans-1] << endl;
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
