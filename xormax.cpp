Problem : https://codeforces.com/contest/706/problem/D

#include<bits/stdc++.h>
#define int long long
using namespace std;

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
			for(int i = 30; i >= 0; i--){
				int currBit = (val >> i) & 1LL;
				if(curr->bit[currBit] == NULL)
					curr->bit[currBit] = new node();
				curr = curr->bit[currBit];
				curr->cnt++;
			}
		}

		void remove(int val){
			nodeptr curr = root;
			for(int i = 30; i >= 0; i--){
				int currBit = (val >> i) & 1LL;
				curr = curr->bit[currBit];
				curr->cnt--;
			}
		}

		int query(int val){	//max xor with val query
			int ans = 0;
			nodeptr curr = root;
			for(int i = 30; i >= 0; i--){
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

	TRIE T;
	T.insert(0);
	int q;	cin >> q;
	while(q--){
		char tc;	cin >> tc;
		int val;	cin >> val;
		if(tc == '+'){
			T.insert(val);
		}else if(tc == '-'){
			T.remove(val);
		}else{
			cout << T.query(val) << '\n';
		}
	}

}
