// Problem : (codechef) https://www.codechef.com/problems/ANUGCD/

/*
Author: Nachiket Kanore
Created: Sunday 13 December 2020 04:51:12 PM IST
(ツ) In order to live free and happily you must sacrifice boredom. It is not always an easy sacrifice.
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <string>

#define int long long
#define sz(x) (int)(x.size())
#define FOR(i,L,R) for(int i = (L); i <= (R); i++)
using namespace std;

const int N = 1e5 + 5, inf = 1e18;

int best_mx = -1;

// Implicit segment tree node
// Each node is some range in [1, N]
// Point updates with RangeMax queries
struct node {
	int mx;
	node* left;
	node* right;

	node() {
		mx = -1;
		left = NULL;
		right = NULL;
	}

	node* upd(int l, int r, int id, int val) {
		mx = max(mx, val);
		if (l < r) {
			int mid = (l + r) >> 1;
			if (id <= mid) {
				if (left == NULL)
					left = new node();
				left = left->upd(l, mid, id, val);
			} else {
				if (right == NULL)
					right = new node();
				right = right->upd(mid+1, r, id, val);
			}
		}
		return this;
	}

	void get_max(int tl, int tr, int ql, int qr) {
		if (tl > qr || tr < ql) return ;
		if (ql <= tl && tr <= qr) {
			best_mx = max(best_mx, mx);
			return;
		}
		int mid = (tl + tr) / 2;
		if (left != NULL)
			left->get_max(tl, mid, ql, qr);
		if (right != NULL)
			right->get_max(mid+1, tr, ql, qr);
	}

};

node* roots[N+5];
int n, Q;
vector<int> pfs[N+5];
vector<int> pos[N+5];


void pre() {
	for (int i = 2; i <= N; i++) {
		if (!sz(pfs[i]))
			for (int j = i; j <= N; j += i)
				pfs[j].push_back(i);
	}
	for (int i = 2; i <= N; i++)
		roots[i] = new node();
}

int32_t main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	pre();

	cin >> n >> Q;
	FOR (i,1,n) {
		int val;	cin >> val;
		pos[val].push_back(i);
		for (int p : pfs[val]) {
			roots[p] = roots[p]->upd(1, n, i, val);
		}
	}

	while (Q--) {
		int G, L, R;
		cin >> G >> L >> R;
		best_mx = -1;

		for (int p : pfs[G]) {
			roots[p]->get_max(1, n, L, R);
		}
		if (best_mx == -1) cout << "-1 -1\n";
		else {
			int occ = upper_bound(pos[best_mx].begin(), pos[best_mx].end(), R) - 
					  lower_bound(pos[best_mx].begin(), pos[best_mx].end(), L);
			assert(occ > 0);
			cout << best_mx << " " << occ << "\n";
		}
	}
}
