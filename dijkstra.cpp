class Dijkstra {
  int n, m;
  vi *G;
  set<int> res;
  int *vis, *U, *V;

  typedef pair<ll, pii> node;

public:
  void init(int no, int edges) {
    n = no;
    m = edges;
    U = new int[m + 3];
    V = new int[m + 3];
    W = new int[m + 3];
    G = new vi[n + 3];
    vis = new int[n + 3];
    int i;
    fo(i, n + 1) vis[i] = 0;
    clr(vis);
  }

  int adj(int u, int e) { return u == U[e] ? V[e] : U[e]; }
  void addEdge(int pos, int u, int v, int w) {
    U[pos] = u;
    V[pos] = v;
    W[pos] = w;
    G[u].pb(pos);
    G[v].pb(pos);
  }
  void compute(int source) {
    priority_queue<node, vector<node>, f> Q;
    Q.push({0, {source, -1}});
    while (!Q.empty()) {
      node cur = Q.top();
      Q.pop();
      if (vis[cur.S.F])
        continue;
      vis[cur.S.F] = 1;
      res.insert(cur.S.S);
      for (int e : G[cur.S.F]) {
        int to = adj(cur.S.F, e);
        int w = W[e];
        Q.push({cur.F + w, {to, e}});
      }
    }
    res.erase(-1);
    ll sum = 0;
    tr(it, res) sum += W[*it];
    cout << sum << endl;
    tr(it, res) cout << *it << " ";
  }
};
