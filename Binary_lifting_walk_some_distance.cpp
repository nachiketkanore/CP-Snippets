//Problem : https://www.codechef.com/problems/HTREE

#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)(x.size())
#define int long long

const int N = 1e5 + 2, LOG = 20;

int par[LOG][N], dep[N], n, q;
std::vector<int> g[N];

void dfs(int node, int p){
    par[0][node] = p;
    for(int i = 1; i < LOG; i++)
        par[i][node] = par[i - 1][par[i - 1][node]];
    for(int child : g[node])
        if(child != p){
            dep[child] = dep[node] + 1;
            dfs(child, node);
        }
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);  

    cin >> n >> q;
    for(int i = 1, u, v; i < n; ++i){
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);

    while(q--){
        int node, dist;
        cin >> node >> dist;
        if(dist > dep[node])
            cout << -1 << '\n';
        else{
            for(int i = 0; i < LOG; i++)
                if(dist >> i & 1)
                    node = par[i][node];
            cout << node << '\n';
        }
    }

}
