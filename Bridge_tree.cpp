// https://codeforces.com/contest/1000/problem/E

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;
const int M = 3e5 + 5;

int n, m, node = 1, maxdist;
int tim = 0, grp = 1;
int u[N], v[N], comp[N];
bool vis[N], vis2[N], isBridge[M];
int tin[N], tout[N], minAncestor[N];
queue<int> Q[N];
vector<pair<int, int> > g[N];
vector<int> tree[N], vertices[N]; //Tree stores Bridge Tree, vertices stores the nodes in each component 

void dfs(int k, int par)
{
    vis[k]=1;
    tin[k]=++tim;
    minAncestor[k]=tin[k];
    for(auto it:g[k])
    {
        if(it.first==par)
            continue;
        if(vis[it.first])
        {   
            minAncestor[k]=min(minAncestor[k], tin[it.first]);
            continue;
        }
        dfs(it.first, k);
        minAncestor[k]=min(minAncestor[k], minAncestor[it.first]);
        if(minAncestor[it.first]>tin[k])
            isBridge[it.second]=1;
    }
    tout[k]=tim;
}

void dfs2(int k)
{
    int comp=grp;
    Q[comp].push(k);
    vis2[k]=1;
    while(!Q[comp].empty())
    {
        int u=Q[comp].front();
        Q[comp].pop();
        vertices[comp].push_back(u);
        for(auto it:g[u])
        {
            int v=it.first;
            int edgeidx=it.second;
            if(vis2[v])
                continue;
            if(isBridge[edgeidx])
            {
                grp++;
                tree[comp].push_back(grp);
                tree[grp].push_back(comp);
                dfs2(v);
            }
            else
            {
                Q[comp].push(v);
                vis2[v]=1;
            }
        }
    }
}

void create_bridge_tree() {
    dfs(1, 0);
    dfs2(1);
}  

void GO(int u, int par, int dist, int &end1, int &diam) {
    if (diam < dist) {
        diam = dist;
        end1 = u;
    }

    for (int v : tree[u]) if(par != v) GO(v, u, dist + 1, end1, diam);
}

int diameter() {
    int end1 = 0;
    int diam = 0;

    GO(1,1,0,end1,diam);
    GO(end1,0,0,end1,diam);
    
    return diam;
}

int32_t main(){ 
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        cin >> u[i] >> v[i];
        g[u[i]].push_back({v[i], i});
        g[v[i]].push_back({u[i], i});
    }

    create_bridge_tree();

    cout << diameter() << '\n';
}
