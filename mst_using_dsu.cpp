#include<bits/stdc++.h>
#define int long long
using namespace std;



const int N = 2e5 + 5;
 
struct DSU  //DSU struct credits : ashishgup _/\_
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
 
 
int n;
DSU dsu;

struct Edge {
    int u, v, weight;
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

vector<Edge> Edges;

int32_t main(){

    int n;  cin >> n;
    int e;  cin >> e;

    DSU dsu;
    dsu.init(n);

    while(e--){
        int u , v , w;  cin >> u >> v >> w;
        Edges.push_back({u , v ,w});
    }

    sort(Edges.begin() , Edges.end());

    int cost = 0;
    vector<Edge> result;


    for (Edge &e : Edges) {
        if (dsu.getPar(e.u) != dsu.getPar(e.v)) {
            cost += e.weight;
            result.push_back(e);
            dsu.unite(e.u, e.v);
        }
    }

    cout << "Tree should have " << dsu.connected << " connected components " << endl;
    cout << "The cost of the minimum spanning tree is " << cost << endl;
    for (Edge &e : result) {
        cout << e.u << " " << e.v << " => " << e.weight << endl;
    }

    return 0;
}
