#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define pii pair<int,int>
#define MP make_pair
#define sf scanf
#define pf printf

const int maxn = 1e7;
const string Lam("lambda");

int n;
int tot, cont[maxn+5];
int top, sta[maxn+5];
char arr[maxn+5], fg[maxn+5];
map<string, int> Name;

void GetStr(int &ptr, string &str)
{
	str.clear();
	while(ptr<n && arr[ptr]!=' ' && arr[ptr]!='(' && arr[ptr]!=')')
	{
		str.push_back(arr[ptr]);
		++ptr;
	}
}

void run(int &ptr)
{
	string str;
	while(ptr < n)
	{
		while(ptr<n && arr[ptr] == ' ') ++ptr;
		if(ptr >= n) break;
		if(arr[ptr] == '(')
		{
			++ptr;
			run(ptr);
		}
		else if(arr[ptr] == ')')
		{
			++ptr;
			return;
		}
		else
		{
			GetStr(ptr, str);
			if(str == Lam)
			{
				while(arr[ptr] == ' ' || arr[ptr] == '(')
					++ptr;
				GetStr(ptr, str);
				while(arr[ptr] == ' ' || arr[ptr] == ')')
					++ptr;

				if(!Name.count(str))
				{
					Name[str] = tot;
					cont[tot] = 0, fg[tot] = 0;
					tot++;
				}
				int num = Name[str];
				sta[++top] = num;
				++cont[num];
				run(ptr);
				--cont[num], --top;
				return;
			}
			else
			{
				if(!Name.count(str))
				{
					Name[str] = tot;
					cont[tot] = 0, fg[tot] = 0;
					tot++;
				}
				int num = Name[str];
				if(cont[num] == 0)
					fg[num] = 1;
			}
		}
	}
}

int main()
{
	int T, ptr, wtf;
	map<string,int>::iterator it;
	sf("%d\n", &T);
	/* cnm hdu WA n+
	sf("%d", &T);
	getchar();
	*/
	for(int t=1; t<=T; ++t)
	{
		fgets(arr, maxn+2, stdin);
		n = strlen(arr)-1;
		top = tot = ptr = 0;
		Name.clear();
		run(ptr);
		printf("Case #%d:", t);
		wtf = 0;
		for(it=Name.begin(); it!=Name.end(); ++it)
		{
			if(fg[it->second])
				printf(" %s", (it->first).c_str()), wtf = 1;
		}
		if(!wtf) pf(" ");
		printf("\n");
	}
	return 0;
}
