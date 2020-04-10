Problem : https://www.codechef.com/problems/PPTREE

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
#define ld long double
#define endl '\n'
#define rep(x,s,e) for(int x=s;x<=(e);x++)
#define repn for(int x=0;x<n;x++)
#define rep1n for(int x=1;x<=n;x++)
#define rep1m for(int y=1;y<=m;y++)
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(), x.rend()
#define precise(x) cout << fixed << setprecision(x)
#define bits(x) __builtin_popcount(x)
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define sz(x) (int)(x.size())
#define test int t; cin>>t; while(t--)
#define FAST                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

typedef vector<int> vi;
typedef vector<pair<int,int>> vii;
typedef pair<int,int> pii;


void __print(int x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}


template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define see(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define see(x...)
#endif

const int inf = 1e18;
const int N = 1e5+5;

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


vector<pair<int,int>> tree[N];
int a[N];

void dfs(int node , int par, int curr){
   a[node] = curr;
   for(auto ch : tree[node]){
      if(ch.first != par){
         dfs(ch.first, node, curr ^ ch.second);
      }
   }
}

void solve(){
   int n;   cin >> n;
   TRIE T;
   int ans = 0;
   for(int i = 1; i < n; i++){
      int u, v, w;   cin >> u >> v >> w;
      tree[u].push_back({v, w});
      tree[v].push_back({u, w});
   }

   dfs(1, -1, 0);

   for(int i = 1; i <= n; i++){
      T.insert(a[i]);
   }

   for(int i = 1; i <= n; i++){
      T.remove(a[i]);
      int curr = T.query(a[i]);
      ans = max(ans, curr);
      T.insert(a[i]);
   }
   cout << ans << '\n';
   for(int i = 1; i <= n; i++)
      tree[i].clear(), a[i] = 0;

}


int32_t main(){ 
   FAST;

   test solve();
   
     return 0;
}
