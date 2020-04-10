//With reference to problem on codeforces : https://codeforces.com/problemset/problem/659/E
//Submission : https://codeforces.com/contest/659/submission/66555010

// Author : Nachiket Kanore
// Institute : PICT, Pune

/* It does not matter how slowly you go as long as you do not stop.*/

#include <bits/stdc++.h>

using namespace std;

#define int long long
#define endl '\n'
#define rep(x,s,e) for(int x=s;x<=(e);x++)
#define repn for(int x=0;x<n;x++)
#define rep1n for(int x=1;x<=n;x++)
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(), x.rend()
#define precise(x) cout << fixed << setprecision(x)
#define bits(x) __builtin_popcount(x)
#define pb push_back
#define mp make_pair
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
void debarr(int arr[] , int n){
    cout << "arr : ";
    rep(i,0,n-1) cout << arr[i] << " ";     cout << '\n';
}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif
 
const int mod = 1e9+7;
const int inf = 1e18;
const int N = 5e5+20;

struct DSU
{
	int connected;
	int par[N], sz[N];
 
	void init(int n) 
	{
		for(int i=1;i<=n;i++)
		{
			par[i]=i;
			sz[i]=1;
		}
		connected=n;
	}
 
	int getPar(int k)
	{
		while(k!=par[k])
		{
			par[k]=par[par[k]];
			k=par[k];
		}
		return k;
	}
 
	int getSize(int k)
	{
		return sz[getPar(k)];
	}
 
	void unite(int u, int v)
	{
		int par1=getPar(u), par2=getPar(v);
 
		if(par1==par2)
			return;
 
		connected--;
 
		if(sz[par1]>sz[par2])
			swap(par1, par2);
 
		sz[par2]+=sz[par1];
		sz[par1]=0;
		par[par1]=par[par2];
	}
};
 
int n,m;
DSU dsu;

vector<vector<int>> components;
vector<int> temp;
int compo;
vector<int> graph[N];
int vis[N];
vector<int> edges[N];

void dfs(int node){
	vis[node] = 1;
	temp.push_back(node);

	for(auto adj : graph[node]){
		if(!vis[adj]){
			dfs(adj);
		}
	}
}

int ans;

int32_t main(){
    FAST;

    cin >> n >> m;

	dsu.init(n);

	for(int x = 0; x < m; x++){
		int a , b;	cin >> a >> b;
		graph[a].pb(b) , graph[b].pb(a);
		edges[a].pb(b);
	}

	rep1n{
		int node = x;
		if(!vis[node]){
			compo++;
			dfs(node);
			components.push_back(temp);
			temp.clear();
		}
	}

	for(auto &ch : components){
		//debug(ch);

		vi &curr = ch;
		vii component_edges;

		for(auto &node : curr){

			for(auto &target : edges[node]){
				component_edges.push_back({node , target});
			}

		}

		//debug(component_edges);

		bool cycle = 0;

		for(auto &edge : component_edges){
			int one = edge.first;
			int two = edge.second;

			if(dsu.getPar(one) == dsu.getPar(two)){
				cycle = 1;
				break;
			}else{
				dsu.unite(one , two);
			}

		}

		ans += !cycle;


	}

	cout << ans << endl;
    
    return 0;
}


