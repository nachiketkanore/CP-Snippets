// Problem : https://codeforces.com/contest/455/problem/D

/*
Author: Nachiket Kanore
Created: Friday 01 January 2021 10:47:47 PM IST
(ツ) Silence is a source of great strength.
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cassert>
#include <deque>
#include <cstring>

#define pb push_back
#define ALL(x) (x).begin(),(x).end()
#define sz(x) (int)(x.size())
#define FOR(i,L,R) for(int i = (L); i <= (R); i++)
using namespace std;

template<class T> bool cmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool cmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
 
const int N = 1e5 + 5;

int MAGIC;
int n, a[N];
int cnt[333][N];
deque<int> blocks[333];
int answer = 0;

void update(int L, int R) {
	L--;
	R--;

	int FIRST_BLOCK = L / MAGIC;
	int LAST_BLOCK = R / MAGIC;

	int idL = L % MAGIC;
	int idR = R % MAGIC;

	int val = blocks[LAST_BLOCK][idR];

	// Remove val from LAST_BLOCK 
	blocks[LAST_BLOCK].erase(blocks[LAST_BLOCK].begin() + idR);
	cnt[LAST_BLOCK][val]--;

	// Enter it at idL on FIRST_BLOCK
	blocks[FIRST_BLOCK].insert(blocks[FIRST_BLOCK].begin() + idL, val);
	cnt[FIRST_BLOCK][val]++;

	// Now, transfer last values to next block's beginning

	while (FIRST_BLOCK < LAST_BLOCK) {
		// Remove from i
		int last = blocks[FIRST_BLOCK].back();
		blocks[FIRST_BLOCK].pop_back();
		cnt[FIRST_BLOCK][last]--;

		// Add to i+1
		FIRST_BLOCK++;
		blocks[FIRST_BLOCK].push_front(last);
		cnt[FIRST_BLOCK][last]++;
	}

}

int query(int L, int R, int k) {
	L--;
	R--;

	int FIRST_BLOCK = L / MAGIC;
	int LAST_BLOCK = R / MAGIC;

	int idL = L % MAGIC;
	int idR = R % MAGIC;

	int ans = 0;

	if (FIRST_BLOCK == LAST_BLOCK) {
		for (int i = idL; i <= idR; i++)
			ans += blocks[FIRST_BLOCK][i] == k;
		return ans;
	}

	// traverse FIRST_BLOCK
	for (int i = idL; i < sz(blocks[FIRST_BLOCK]); i++)
		ans += blocks[FIRST_BLOCK][i] == k;

	// traverse LAST_BLOCK
	for (int i = 0; i <= idR; i++)
		ans += blocks[LAST_BLOCK][i] == k;

	// traverse MIDDLE_BLOCKS
	for (int BLOCK = FIRST_BLOCK + 1; BLOCK < LAST_BLOCK; BLOCK++) 
		ans += cnt[BLOCK][k];

	return ans;
}

int32_t main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	cin >> n;
	MAGIC = sqrt(n) + 1;

	for (int i = 0; i < n; i++) {
		cin >> a[i];
		int BLOCK = i / MAGIC;
		blocks[BLOCK].push_back(a[i]);
		cnt[BLOCK][a[i]]++;
	}

	int Q;
	cin >> Q;

	while (Q--) {
		int type;
		cin >> type;
		int L, R;
		cin >> L >> R;

		L = ((L + answer - 1) % n) + 1;
		R = ((R + answer - 1) % n) + 1;
		if (L > R) swap(L, R);

		if (type == 1) {
			update(L, R);
		} else {
			int val;
			cin >> val;
			val = ((val + answer - 1) % n) + 1;
			answer = query(L, R, val);
			cout << answer << "\n";
		}
	}
}
