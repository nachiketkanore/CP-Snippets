Problem : https://www.hackerearth.com/practice/data-structures/advanced-data-structures/trie-keyword-tree/practice-problems/algorithm/search-engine/

/*
    __  __               __                    __      __               __          ______      __           __ 
   / / / /___ __________/ /      ______  _____/ /__   / /_  ___  ____ _/ /______   /_  __/___ _/ /__  ____  / /_
  / /_/ / __ `/ ___/ __  / | /| / / __ \/ ___/ //_/  / __ \/ _ \/ __ `/ __/ ___/    / / / __ `/ / _ \/ __ \/ __/
 / __  / /_/ / /  / /_/ /| |/ |/ / /_/ / /  / ,<    / /_/ /  __/ /_/ / /_(__  )    / / / /_/ / /  __/ / / / /_  
/_/ /_/\__,_/_/   \__,_/ |__/|__/\____/_/  /_/|_|  /_.___/\___/\__,_/\__/____/    /_/  \__,_/_/\___/_/ /_/\__/  
                                                                                                                
*/
#include <bits/stdc++.h>

using namespace std;
#define int long long
#define sz(x) (int)(x.size())

class TRIE{
	private:
		typedef struct node{
			node* child[26];
			int val;
			node(){
				val = 0;
				for(int i = 0; i < 26; i++)
					child[i] = NULL;
			}
		}* nodeptr;
		nodeptr root;
	public:
		TRIE(){
			root = new node();
		}

		void insert(string &s, int p){
			nodeptr curr = root;
			for(int i = 0; i < sz(s); i++){
				int bx = s[i] - 'a';
				if(curr->child[bx] == NULL)
					curr->child[bx] = new node();
				curr = curr->child[bx];
				curr->val = max(curr->val, p);
			}
		}

		int query(string &s){
			nodeptr curr = root;
			int ans = -1;
			for(int i = 0; i < sz(s); i++){
				int bx = s[i] - 'a';
				if(curr->child[bx] == NULL)
					return ans;
				curr = curr->child[bx];
			}
			return curr->val;
		}

};

int32_t main(){ 
   ios::sync_with_stdio(false);
   cin.tie(NULL); cout.tie(NULL);

	TRIE T;
	int n;	cin >> n;
	int q;	cin >> q;
	for(int i = 0; i < n; i++){
		string s;	cin >> s;
		int val;	cin >> val;
		T.insert(s, val);
	}
	while(q--){
		string s;	cin >> s;
		cout << T.query(s) << '\n';
	}
   
}
