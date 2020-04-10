//With reference to the problem on HackerEarth : https://www.hackerearth.com/practice/data-structures/disjoint-data-strutures/basics-of-disjoint-data-structures/practice-problems/algorithm/ikshu-and-his-class-1/
//My Submission is below : 

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
#define rep1m for(int y=1;y<=m;y++)
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
const int N = 2e5+100;



 
struct DSU
{
	int connected;
	int par[N], sz[N];
    bool vis[N];
 
	void init(int n) 
	{
		for(int i=1;i<=n;i++)
		{
			par[i]=i;
			sz[i]=1;
            vis[i] = false;
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
 
 
int n;
DSU dsu;

int getFact(int n){

    int ans = 1;

    for(int x=1;x<=n;x++){
        ans =( ans * x ) % mod;
        ans %= mod;
    }

    return ans;


}


int32_t main(){
    FAST;


    cin >> n;
    dsu.init(n);
    int k;  cin >> k;
    while(k--){

        int u , v;  cin >> u >> v;  //nodes were 0 indexed , so needed to increment
        u++ , v++;
        dsu.unite(u,v);

    }


    int ans = 1;

    rep1n{
        int boss = dsu.getPar(x);
        if(dsu.vis[boss]) continue;

        dsu.vis[boss] = true;

        int sz = dsu.getSize(boss);
        
        ans = (ans * getFact(sz)) % mod;
        
        ans %= mod;
        
    }

    cout << ans << endl;


    return 0;
}
