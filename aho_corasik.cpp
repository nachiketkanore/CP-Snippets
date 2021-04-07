// Problem : https://codeforces.com/problemset/problem/710/F
// struct credit : TadijaSebez on codeforces

/**
 *	Author: Nachiket Kanore
 *	Created: Wednesday 07 April 2021 02:17:46 PM IST
**/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cassert>
#include <array>
#include <string>
#include <cstring>
#include <queue>
#include <map>

#define pb push_back
#define sz(x) (int)(x.size())
#define ALL(x) (x).begin(),(x).end()
#define F0R(i,R) for(int i = (0); i < (R); ++i)
#define FOR(i,L,R) for(int i = (L); i <= (R); ++i)
using namespace std;

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '{'; string sep; for (const auto &x : v) os << sep << x, sep = ", "; return os << '}'; }
template<typename T, size_t size> ostream& operator<<(ostream &os, const array<T, size> &arr) { os << '{'; string sep; for (const auto &x : arr) os << sep << x, sep = ", "; return os << '}'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

#ifdef DEBUG
#define see(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define see(...)
#endif

template<class T> bool cmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool cmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; } 

const int N=300050;
struct AhoCorasik
{
	struct Node
	{
		map<char,int> go;
		int link,val;
		Node(int a=0, int b=0){ link=a;val=b;}
	};
	vector<Node> node;
	int root;
	int AddNode(int a=0, int b=0)
	{ 
		node.pb(Node(a,b));
		return node.size()-1;
	}
	void Clear()
	{ 
		root=0;
		node.clear();
	}
	void init()
	{ 
		root=AddNode();
	}
	void Add(string s)
	{
		int cur=root;
		for(int i=0;i<(int)s.size();i++)
		{
			if(!node[cur].go.count(s[i]))
				node[cur].go[s[i]]=AddNode();
			cur=node[cur].go[s[i]];
		}
		node[cur].val++;
	}
	void Build()
	{
		queue<int> q;
		for(auto p:node[root].go)
		{
			q.push(p.second);
			node[p.second].link=root;
		}
		for(int i=0;i<26;i++)
		{
			if(!node[root].go.count('a'+i))
				node[root].go['a'+i]=root;
		}
		while(q.size())
		{
			int x=q.front();
			q.pop();
			for(auto p:node[x].go)
			{
				int link=node[x].link;
				while(!node[link].go.count(p.first)) link=node[link].link;
				node[p.second].link=node[link].go[p.first];
				node[p.second].val+=node[node[p.second].link].val;
				q.push(p.second);
			}
		}
	}
	int Count(string s)
	{
		int cur=root;
		int ans=0;
		for(int i=0;i<(int)s.size();i++)
		{
			while(!node[cur].go.count(s[i])) cur=node[cur].link;
			cur=node[cur].go[s[i]];
			ans+=node[cur].val;
		}
		return ans;
	}
};

struct DynamicAhoCorasik
{
	vector<string> all;
	AhoCorasik container[19];
	DynamicAhoCorasik() {}

	void add(string s) 
	{
		all.push_back(s);
		int len = sz(all);
		int lowbit = 0;
		for (; lowbit < 19 && (len >> lowbit & 1) == 0; lowbit++) {
			container[lowbit].Clear();
		}
		container[lowbit].Clear();
		container[lowbit].init();
		for (int bit = 1; bit <= (1<<lowbit); bit++) {
			assert(len-bit >= 0 && len-bit < sz(all));
			container[lowbit].Add(all[len-bit]);
		}
		container[lowbit].Build();
	}

	int count(string s) 
	{
		int len = sz(all);
		int ret = 0;
		for (int i = 0; i < 19; i++) if (len >> i & 1) {
			ret += container[i].Count(s);
		}
		return ret;
	}
} add, sub;

int32_t main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int Q;
	cin >> Q;
	while (Q--) {
		int type;	string s;
		cin >> type >> s;
		if (type == 1) add.add(s);
		else if (type == 2) sub.add(s);
		else cout << (add.count(s) - sub.count(s)) << endl;
	}
}
