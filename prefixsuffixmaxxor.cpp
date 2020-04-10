Problem : https://codeforces.com/contest/282/problem/E

#include<bits/stdc++.h>
#define int long long
using namespace std;

int ans = 0;

class TRIE{

	private:
		typedef struct node{
			node* bit[2];
			int cnt = 0;
		}* nodeptr;
		
		nodeptr root;

	public:

		TRIE(){
			root = new node();
		}

		void insert(int val){
			nodeptr curr = root;
			for(int i = 45; i >= 0; i--){
				int currBit = (val >> i) & 1LL;
				if(curr->bit[currBit] == NULL)
					curr->bit[currBit] = new node();
				curr = curr->bit[currBit];
				curr->cnt++;
			}
		}

		void remove(int val){
			nodeptr curr = root;
			for(int i = 45; i >= 0; i--){
				int currBit = (val >> i) & 1LL;
				curr = curr->bit[currBit];
				curr->cnt--;
			}
		}

		int query(int val){	//max xor with val query
			int ans = 0;
			nodeptr curr = root;
			for(int i = 45; i >= 0; i--){
				int currBit = (val >> i) & 1LL;
				if(curr->bit[currBit ^ 1] != NULL && curr->bit[currBit ^ 1]->cnt > 0){
					ans += (1LL << i);
					curr = curr->bit[currBit ^ 1];
				}else curr = curr->bit[currBit];
			}
			return ans;
		}

};

int32_t main(){

	#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
	#endif

	TRIE pref, suff;
	int n;	cin >> n;
	int a[n], suffXor[n], prefXor[n];
	int curr = 0;
	for(int i = 0; i < n; i++){
		cin >> a[i];
		suffXor[i] = a[i];
		prefXor[i] = a[i];
		if(i) prefXor[i] ^= prefXor[i-1];
		curr ^= a[i];
		ans = max(ans , curr);
		pref.insert(prefXor[i]);
	}

	curr = 0;
	for(int i = n - 1; i >= 0; i--){
		curr ^= a[i];
		if(i < n-1)
			suffXor[i] ^= suffXor[i+1];
		ans = max(ans , curr);
		suff.insert(suffXor[i]);
	}

	curr = 0;
	for(int i = 0; i < n; i++){
		curr ^= a[i];
		int toDel = suffXor[i];
		suff.remove(toDel);
		int mx = suff.query(curr);
		ans = max(ans , mx);
	}

	curr = 0;
	for(int i = n - 1; i >= 0; i--){
		curr ^= a[i];
		int toDel = prefXor[i];
		pref.remove(toDel);
		int mx = pref.query(curr);
		ans = max(ans , mx);
	}

	cout << ans << '\n';

}
