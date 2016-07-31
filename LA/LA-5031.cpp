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

struct Treap
{
	struct Node
	{
		int key, size, val;
		Node *ch[2];

		void resize(){ size = ch[0]->size + ch[1]->size + 1; }
		Node(int _val = 0, Node *x = NULL, int _size = 1)
		{
			val = _val, key = rand(), size = _size;
			ch[0] = ch[1] = x;
		}
	}*root = NULL, *null = NULL;
	
	void _clear(Node* &x)
	{
		if(x->ch[0] != null) _clear(x->ch[0]);
		if(x->ch[1] != null) _clear(x->ch[1]);
		delete x;
		x = null;
	}

	void _rotate(Node* &x, int type)
	{
		Node* t = x->ch[type^1]; x->ch[type^1] = t->ch[type]; t->ch[type] = x;
		x->resize(); t->resize(); x = t;
	}

	void _insert(Node* &x, int _val)
	{
		if(x == null){ x = new Node(_val, null); return; }
		int type = _val > x->val ? 0 : 1;
		_insert(x->ch[type], _val);
		if(x->ch[type]->key < x->key)
			_rotate(x, type^1);
		x->resize();
	}

	void _remove(Node* &x, int _val)
	{
		if(_val == x->val)
		{
			if(x->ch[0] == null){ Node *t = x->ch[1]; delete x; x = t; }
			else if(x->ch[1] == null){ Node *t = x->ch[0]; delete x; x = t; }
			else
			{
				int type = x->ch[0]->key < x->ch[1]->key ? 0 : 1;
				_rotate(x, type^1);
				_remove(x->ch[type^1], _val);
			}
		}
		else
			_remove(x->ch[_val < x->val ], _val);
		if(x != null) x->resize();
	}

	int _kth(Node* &x, int dat)
	{
		if(dat > x->size || dat<=0) return 0;
		if(dat == x->ch[0]->size + 1) return x->val;
		if(dat <= x->ch[0]->size) return _kth(x->ch[0], dat);
		else return _kth(x->ch[1], dat - x->ch[0]->size - 1);
	}

	void _merge(Node* &x, Treap *dest)
	{
		if(x->ch[0] != null) _merge(x->ch[0], dest);
		if(x->ch[1] != null) _merge(x->ch[1], dest);
		dest->insert(x->val);
		delete x;
		x = null;
	}

	void merge(Treap *dest){ _merge(root, dest); }
	void insert(int _val){ _insert(root, _val); }
	void remove(int _val)
	{
		if(root == null) return;
		_remove(root, _val);
	}
	int kth(int dat)
	{
		if(root == null) return 0;
		return _kth(root, dat);
	}
	void clear()
	{
		if(null == NULL)
		{
			null = new Node(0, null, 0);
			root = null;
			return;
		}
		if(root != null)
			_clear(root);
	}

};

struct Command
{
	char ord;
	int X, Y;
};

const int maxn = 200000, maxm = 600000, max_ord = 2000000;

int fat[maxn+5];
int find_fat(int x){ return x == fat[x] ? x : fat[x] = find_fat(fat[x]); }

int n, m, weight[maxn+5];
pii edge[maxm+5];
bool removed[maxm+5];

Treap tree[maxn+5];
Command com[max_ord+5];

void merge_tree(int u, int v)
{
	u = find_fat(u); v = find_fat(v);
	if(u == v) return;
	if(tree[u].root->size < tree[v].root->size){ tree[u].merge(&tree[v]); fat[u] = v; }
	else{ tree[v].merge(&tree[u]); fat[v] = u; }
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	srand(time(NULL));
	int a, b, c, tot, tot_Q, NT = 1;
	double sum;
	char ord[4];
	while(sf("%d%d", &n, &m), n)
	{
		REP(i,1,n) sf("%d", weight+i);
		REP(i,1,m) sf("%d%d", &edge[i].first, &edge[i].second);
		mem(removed, 0);
		tot = 0;
		for(;;)
		{
			sf("%s", ord);
			if(ord[0] == 'E'){ break; }
			com[++tot].ord = ord[0];
			if(com[tot].ord == 'D')
			{
				sf("%d", &com[tot].X);
				removed[com[tot].X] = true;
			}
			else if(com[tot].ord == 'Q')
				sf("%d%d", &com[tot].X, &com[tot].Y);
			else
			{
				sf("%d%d", &com[tot].X, &com[tot].Y);
				swap(com[tot].Y, weight[com[tot].X]);
			}
		}

		REP(i,1,n)
		{
			tree[i].clear(); tree[i].insert(weight[i]); fat[i] = i;
		}
		REP(i,1,m) if(!removed[i])
			merge_tree(edge[i].first, edge[i].second);

		tot_Q = 0, sum = 0.0;
		for(int i=tot; i>=1; --i)
		{
			if(com[i].ord == 'D')
			{
				merge_tree(edge[com[i].X].first, edge[com[i].X].second);
			}
			else if(com[i].ord == 'Q')
				sum += tree[find_fat(com[i].X)].kth(com[i].Y), ++tot_Q;
			else
			{
				tree[find_fat(com[i].X)].remove(weight[com[i].X]);
				tree[find_fat(com[i].X)].insert(com[i].Y);
				weight[com[i].X] = com[i].Y;
			}
		}
		pf("Case %d: %.6f\n", NT++, tot_Q ? sum/tot_Q : 0);
	}
	return 0;
}
