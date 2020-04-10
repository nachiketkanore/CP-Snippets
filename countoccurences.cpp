Problem : https://codeforces.com/contest/714/problem/C

#include <bits/stdc++.h>
#define int long long
#define sz(x) (int)(x.size())
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

		void insert(string val){
			nodeptr curr = root;
			for(int i = 0; i < sz(val); i++){
				int currBit = val[i] - '0';
				if(curr->bit[currBit] == NULL)
					curr->bit[currBit] = new node();
				curr = curr->bit[currBit];
				curr->cnt++;
			}
		}

		void remove(string val){
			nodeptr curr = root;
			for(int i = 0; i < sz(val); i++){
				int currBit = val[i] - '0';
				curr = curr->bit[currBit];
				curr->cnt--;
			}
		}

		int query(string val){	//count number of strings equal to given string
			int ans = 0;
			nodeptr curr = root;
			for(int i = 0; i < sz(val); i++){
				int currBit = val[i] - '0';
				if(curr->bit[currBit] != NULL && curr->bit[currBit]->cnt > 0){
					curr = curr->bit[currBit];
				}else 
					return ans;
			}
			ans = curr->cnt;
			return ans;
		}

};


int32_t main(){
	#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
	#endif

	TRIE T;
	
    int tc;	cin >> tc;
    while(tc--){
    	char ch;	cin >> ch;
    	int val;	cin >> val;
    	string curr = to_string(val);
    	while(sz(curr) < 18)
    		curr = "0" + curr;
    	for(char &cc : curr){
    		int dig = cc - '0';
    		if(dig % 2 == 0) cc = '0';
    			else cc = '1';
    	}
    	
    	if(ch == '+')
    		T.insert(curr);
    	else if(ch == '-')
    		T.remove(curr);
    	else cout << T.query(curr) << '\n';

    }

}
