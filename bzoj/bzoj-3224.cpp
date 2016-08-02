/**************************************************************
	Problem: 3224
	User: fshp971
	Language: C++
	Result: Accepted
	Time:380 ms
	Memory:2224 kb
****************************************************************/

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

struct Treap
{
	struct Node
	{
		int val, key, size;
		Node *ch[2];

		Node(int _val = 0, Node *x = NULL)
		{
			val = _val, key = rand(), size = 1;
			ch[0] = ch[1] = x;
		}

		void maintain(){ size = ch[0]->size + ch[1]->size + 1; }
	}*root, *null;

	void init()
	{
		delete root; delete null;
		null = new Node();
		null->size = 0;
		root = null;
	}

	void rotate(Node* &x, int type)
	{
		Node *t = x->ch[type^1]; x->ch[type^1] = t->ch[type]; t->ch[type] = x;
		x->maintain(); t->maintain(); x = t;
	}

	void insert(Node* &x, int dat)
	{
		if(x == null){ x = new Node(dat, null); return; }
		int type = dat < x->val ? 0 : 1;
		insert(x->ch[type], dat);
		if(x->ch[type]->key < x->key)
			rotate(x, type^1);
		x->maintain();
	}

	void remove(Node* &x, int dat)
	{
		if(x->val == dat)
		{
			if(x->ch[0] == null){ Node *t = x; x = x->ch[1]; delete t; }
			else if(x->ch[1] == null){ Node *t = x; x = x->ch[0]; delete t; }
			else
			{
				int type = x->ch[0]->key < x->ch[1]->key ? 0 : 1;
				rotate(x, type^1);
				remove(x->ch[type^1], dat);
			}
		}
		else
			remove(x->ch[ dat > x->val ], dat);
		if(x != null)
			x->maintain();
	}

	int rank(Node* &x, int dat)
	{
		if(x == null) return 0;
		if(dat <= x->val) return rank(x->ch[0], dat);
		else if(dat > x->val) return x->ch[0]->size + 1 + rank(x->ch[1], dat);
		return x->ch[0]->size;
	}

	int kth(Node* &x, int dat)
	{
		if(dat == x->ch[0]->size+1) return x->val;
		if(dat <= x->ch[0]->size) return kth(x->ch[0], dat);
		else return kth(x->ch[1], dat - (x->ch[0]->size+1));
	}

	int prev(Node* &x, int dat)
	{
		if(x == null) return -1<<30;
		if(dat <= x->val) return prev(x->ch[0], dat);
		return max(x->val, prev(x->ch[1], dat));
	}

	int next(Node* &x, int dat)
	{
		if(x == null) return 1<<30;
		if(dat >= x->val) return next(x->ch[1], dat);
		return min(x->val, next(x->ch[0], dat));
	}
}tree;

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int n, ord, a;
	tree.init();
	sf("%d", &n);
	REP(i,1,n)
	{
		sf("%d%d", &ord, &a);
		if(ord == 1) tree.insert(tree.root, a);
		else if(ord == 2) tree.remove(tree.root, a);
		else if(ord == 3) pf("%d\n", tree.rank(tree.root, a)+1);
		else if(ord == 4) pf("%d\n", tree.kth(tree.root, a));
		else if(ord == 5) pf("%d\n", tree.prev(tree.root, a));
		else pf("%d\n", tree.next(tree.root, a));
	}
	return 0;
}
