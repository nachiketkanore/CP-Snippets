class Tree{
    public:
        Tree (int _n){
            n = _n;
            edges.resize(n + 1);
            tin.resize(n + 1);
            tout.resize(n + 1);
            parent.resize(LG);
            for(int i = 0; i < LG; i++)
                parent[i] = std::vector<int> (n + 1, 0);
        }

        void dfs(int k, int par, int lvl){
            tin[k] = ++time;
            parent[0][k] = par;
            level[k] = lvl;

            for(auto it : edges[k]){
                if(it == par)
                    continue;
                dfs(it, k, lvl+1);
            }
            tout[k] = time;
        }

        int walk(int u, int h){
            for(int i = LG-1; i >= 0; i--){
                if((h >> i) & 1)
                    u = parent[i][u];
            }
            return u;
        }

        void precompute(){
            for(int i = 1; i < LG; i++)
                for(int j = 1; j <= n; j++)
                    if(parent[i-1][j])
                        parent[i][j] = parent[i-1][parent[i-1][j]];
        }

        int LCA(int u, int v){
            if(level[u] < level[v])
                swap(u,v);
            int diff = level[u] - level[v];
            for(int i= LG-1; i >= 0; i--){
                if((1<<i) & diff){
                    u=parent[i][u];
                }
            }
            if(u == v)
                return u;
            for(int i = LG-1; i >= 0; i--){
                if(parent[i][u] && parent[i][u] != parent[i][v]){
                    u=parent[i][u];
                    v=parent[i][v];
                }
            }
            return parent[0][u];
        }

        int dist(int u, int v){
            return level[u] + level[v] - 2 * level[LCA(u, v)];
        }

        void setRoot(int u){
            dfs(u, -1, 1);
        }

        void setLCA(int u = 1){
            setRoot(u);
            precompute();
        }

        void addEdge(int u, int v) {
            edges[u].push_back(v);
            edges[v].push_back(u);
        }

    private:
        int n, time = 0, LG = 20;
        std::vector<int> tin, tout, level;
        std::vector<std::vector<int>> edges, parent;

};
