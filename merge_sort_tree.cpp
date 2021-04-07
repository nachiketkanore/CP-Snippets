// Problem : https://codeforces.com/problemset/problem/893/F
// About this code : MergeSort Tree without updates, precomputed prefix minimums for all segtree[u] vectors to query min( second value in pair, which is sorted by first value)

/**
 *	Author: Nachiket Kanore
 *	Created: Wednesday 07 April 2021 06:08:57 PM IST
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

const int inf = 2e9;
const int N = 1e5 + 5;

int root, n, a[N], depth[N], val[N], tin[N], tout[N], timer;
pair<int,int> keep[N];
vector<int> g[N];

struct MergeSortTree
{	
	vector<pair<int,int>> tree[N<<2];
	vector<int> prefix_minimums[N<<2];

	void merge(int u) {
		int x = 2*u, y = 2*u+1;
		assert(is_sorted(ALL(tree[x])) && is_sorted(ALL(tree[y])));
		int i = 0, j = 0;
		while (i < sz(tree[x]) || j < sz(tree[y])) {
			if (i == sz(tree[x])) {
				tree[u].push_back(tree[y][j++]);
			} else if (j == sz(tree[y])) {
				tree[u].push_back(tree[x][i++]);
			} else {
				if (tree[x][i] < tree[y][j]) {
					tree[u].push_back(tree[x][i++]);
				} else {
					tree[u].push_back(tree[y][j++]);
				}
			}
		}
	}

	void init() {
		build(1, 1, n);
		F0R (i,N<<2) {
			int mn = inf;
			for (auto [h, v] : tree[i]) {
				cmin(mn, v);
				prefix_minimums[i].push_back(mn);
			}
		}
	}

	void build(int u, int tl, int tr) {
		if (tl == tr) {
			tree[u].emplace_back(keep[tl]);
		} else {
			int mid = (tl + tr) >> 1;
			build(2*u, tl, mid);
			build(2*u+1, mid+1, tr);
			merge(u);
		}
	}

	int qry(int u, int tl, int tr, int ql, int qr, int max_depth) {
		if (tl > tr || ql > qr || qr < tl || ql > tr) return inf;
		if (tl == ql && tr == qr) {
			int ret = inf;
			int id = -1, lo = 0, hi = sz(tree[u]) - 1;
			while (lo <= hi) {
				int mid = (lo + hi) >> 1;
				if (tree[u][mid].first <= max_depth) {
					id = mid;
					lo = mid + 1;
				} else {
					hi = mid - 1;
				}
			}
			if (~id) ret = prefix_minimums[u][id];
			return ret;
		}
		int mid = (tl + tr) >> 1;
		return min(qry(2*u, tl, mid, ql, min(mid, qr), max_depth),
				qry(2*u+1, mid+1, tr, max(mid+1, ql), qr, max_depth));
	}

	int query(int L, int R, int max_depth) {
		return qry(1, 1, n, L, R, max_depth);
	}
} T;

void dfs(int u, int par, int dep) {
	depth[u] = dep;
	tin[u] = ++timer;
	keep[timer] = make_pair(depth[u], val[u]);
	for (int v : g[u]) if (v ^ par) dfs(v, u, dep+1);
	tout[u] = timer;
}

int32_t main() {
	ios::sync_with_stdio(0); cin.tie(0);

	cin >> n >> root;
	FOR (i,1,n) cin >> val[i];
	FOR (i,2,n) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(root, root, 0);
	T.init();
	int Q, last = 0;
	cin >> Q;
	while (Q--) {
		int u, dist;
		cin >> u >> dist;
		u = (u + last) % n + 1;
		dist = (dist + last) % n;
		dist += depth[u];
		last = T.query(tin[u], tout[u], dist);
		cout << last << '\n';
	}
}
