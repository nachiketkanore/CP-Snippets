//Problem : https://www.hackerearth.com/practice/algorithms/dynamic-programming/2-dimensional/practice-problems/algorithm/killjee-and-saraff-35617645/

#include "bits/stdc++.h"
#define sz(x) (int)(x.size())
using namespace std;

const int N = 2e5 + 5, LG = 19;

int tim=0;
int parent[LG][N];
int tin[N], tout[N], level[N];
std::vector<int> g[N];
int n, q, pref[N];
bool prime[N];

void dfs(int k, int par, int lvl)
{
	tin[k]=++tim;
	parent[0][k]=par;
	level[k]=lvl;
	for(auto it:g[k])
	{
		if(it==par)
			continue;
		dfs(it, k, lvl+1);
	}
	tout[k]=tim;
}

void precompute()
{
	for(int i=1;i<LG;i++)
		for(int j=1;j<=n;j++)
			if(parent[i-1][j])
				parent[i][j]=parent[i-1][parent[i-1][j]];
}

int LCA(int u, int v)
{
	if(level[u]<level[v])
		swap(u,v);
	int diff=level[u]-level[v];
	for(int i=LG-1;i>=0;i--)
	{
		if((1<<i) & diff)
		{
			u=parent[i][u];
		}
	}
	if(u==v)
		return u;
	for(int i=LG-1;i>=0;i--)
	{
		if(parent[i][u] && parent[i][u]!=parent[i][v])
		{
			u=parent[i][u];
			v=parent[i][v];
		}
	}
	return parent[0][u];
}

void dfs2(int node, int par, int cnt) {
	pref[node] = cnt;
	for(int child : g[node]) if(child != par) {
		dfs2(child, node, cnt + prime[child]);
	}
}


int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);	

    fill(prime + 2, prime + N, true);
    for(int i = 2; i < N; i++) if(prime[i]) {
    	for(int j = 2*i; j < N; j+=i)
    		prime[j] = false;
    }

    cin >> n;
    for(int i = 1,u,v; i < n; i++){
    	cin >> u >> v;
    	g[u].push_back(v);
    	g[v].push_back(u);
    }

    dfs(1, 0, 1);
    precompute();
    dfs2(1,0,0);

    cin >> q;
    while(q--){
    	int u, v;
    	cin >> u >> v;
    	int L = LCA(u,v);
    	int ans = pref[u] + pref[v] - 2 * pref[L] + (prime[L]);
    	cout << ans << '\n';
    }
}
