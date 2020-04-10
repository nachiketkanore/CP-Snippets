Problem : https://www.hackerearth.com/practice/data-structures/advanced-data-structures/trie-keyword-tree/practice-problems/algorithm/cost-of-data-11/

#include <bits/stdc++.h>
#define int long long
#define sz(x) (int)(x.size())
using namespace std;

class TRIE{

	private:
		typedef struct node{
			node* bit[26];
			int cnt = 0;
		}* nodeptr;
		
		nodeptr root;

	public:
		int totalNodes;

		TRIE(){
			root = new node();
			totalNodes = 1;
		}

		void insert(string val){
			nodeptr curr = root;
			for(int i = 0; i < sz(val); i++){
				int currBit = val[i] - 'a';
				if(curr->bit[currBit] == NULL)
					curr->bit[currBit] = new node(),
					totalNodes++;
				curr = curr->bit[currBit];
				curr->cnt++;
			}
		}

		int query(){
			return totalNodes;
		}

};


int32_t main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
 	#ifndef ONLINE_JUDGE
     freopen("input.txt", "r", stdin);
     freopen("output.txt", "w", stdout);
 	#endif

	TRIE T;
	int n;	cin >> n;
	for(int i = 0; i < n; i++){
		string s;
		cin >> s;
		T.insert(s);
	}

	cout << T.query() << '\n';

}

