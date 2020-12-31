// Problem : https://codeforces.com/contest/474/problem/E
// use : Generalized implicit segtree (can store multiple info inside node)

/*
Author: Nachiket Kanore
Created: Thursday 31 December 2020 06:53:21 PM IST
(ツ) A goal is a dream with a deadline.
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cassert>
#include <string>
#include <cstring>

#define int long long
#define pb push_back
#define ALL(x) (x).begin(),(x).end()
#define sz(x) (int)(x.size())
#define FOR(i,L,R) for(int i = (L); i <= (R); i++)
using namespace std;

template<class T> bool cmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool cmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
 
const int INF = 1e15;
const int N = 1e5 + 5;
int n, d;
int next_id[N];
int h[N];

class implicit_segtree {
public:
	struct node{
	    pair < int , int > val;
	    node* left;
	    node* right;
	    node(pair < int , int > _val = make_pair(0 , n + 1) , node* _left = NULL , node* _right = NULL){
	        val = _val;
	        left = _left;
	        right = _right;
	    }
	};
	typedef node* pnode;
	pair < int , int > val(pnode tree){
	    if(tree){
	        return tree -> val;
	    }
	    return make_pair(0 , n + 1);
	}
	void update(long long l , long long r , pnode &tree , long long idx , int value , int pos){
	    if(!tree){
	        tree = new node();
	    }
	    if(l == r){
	        tree -> val = max(tree -> val , make_pair(value , pos));
	        return;
	    }
	    long long mid = (l + r) >> 1;
	    if(idx <= mid){
	        update(l , mid , tree -> left , idx , value , pos);
	    }
	    else{
	        update(mid + 1 , r , tree -> right , idx , value , pos);
	    }
	    tree -> val = max(val(tree -> left) , val(tree -> right));
	}
	pair < int , int > query(long long l , long long r , pnode tree , long long ql , long long qr){
	    if(!tree || l > qr || r < ql || ql > qr){
	        return make_pair(0 , n + 1);
	    }
	    if(l >= ql && r <= qr){
	        return val(tree);
	    }
	    long long mid = (l + r) >> 1;
	    return max(query(l , mid , tree -> left , ql , qr) , query(mid + 1 , r , tree -> right , ql , qr));
	}
	pnode root = NULL;
} T;

int32_t main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	cin >> n;
	cin >> d;

	for (int i = 1; i <= n; i++) {
		cin >> h[i];
		next_id[i] = INF;
	}

	for (int L = n; L >= 1; L--) {
		pair<int,int> best_ans_ahead = max(T.query(1, INF, T.root, h[L] + d, INF), T.query(1, INF, T.root, 1, h[L] - d));
		int ans_here = best_ans_ahead.first + 1;
		int idx = best_ans_ahead.second;
		next_id[L] = idx;
		T.update(1, INF, T.root, h[L], ans_here, L);
	}

	pair<int,int> best_ans = T.val(T.root);
	int best_len = best_ans.first;
	int start = best_ans.second;

	assert(best_len > 0);
	cout << best_len << '\n';

	assert(start >= 1 && start <= n);
	while (start <= n) {
		cout << start << ' ';
		start = next_id[start];
	}
}
