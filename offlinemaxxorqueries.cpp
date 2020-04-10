
Problem : https://www.codechef.com/problems/MCO16404

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
const int inf = 1e18;
const int N = 3e5 + 10;

int a[N], ans[N];
vector<pair<int,pair<int,int>>> queries[N];

class TRIE{

	private:
		typedef struct node{
			node* bit[2];
			int cnt = 0;
			int fromId = 0;
		}* nodeptr;
		
		nodeptr root;

	public:

		TRIE(){
			root = new node();
		}

		void insert(int val, int idx){
			nodeptr curr = root;
			for(int i = 30; i >= 0; i--){
				int currBit = (val >> i) & 1LL;
				if(curr->bit[currBit] == NULL)
					curr->bit[currBit] = new node();
				curr = curr->bit[currBit];
				curr->cnt++;
				curr->fromId = idx;
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

		int query(int val, int want){	//max xor with val query
			int ans = 0;
			nodeptr curr = root;
			for(int i = 30; i >= 0; i--){
				int currBit = (val >> i) & 1LL;
				if(curr->bit[currBit ^ 1] != NULL && curr->bit[currBit ^ 1]->cnt > 0 && (curr->bit[currBit ^ 1]->fromId >= want)){
					ans += (1LL << i);
					curr = curr->bit[currBit ^ 1];
				}else curr = curr->bit[currBit];
			}
			return ans;
		}

};


int32_t main(){ 
   ios::sync_with_stdio(false);
   cin.tie(NULL); cout.tie(NULL);

    TRIE T;
    
   int n ;  cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }   
    int m;  cin >> m;
    for(int i = 1; i <= m; i++){
        int l , r, val; cin >> l >> r >> val;
        queries[r].push_back({l, {val , i}});
    }
    
    for(int i = 1; i <= n; i++){
        T.insert(a[i], i);
        for(auto &it : queries[i]){
            int idx = it.second.second;
            int left = it.first, right = i;
            int val = it.second.first;
            ans[idx] = T.query(val , left);
        }
    }
    
    for(int i = 1; i <= m; i++)
        cout << ans[i] << '\n';
    
}
