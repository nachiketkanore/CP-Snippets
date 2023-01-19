
const int N = 2e5 + 10;
int n, m;

vector<int> g[N], gr[N];
int used[N];
vector<int> order, component;
const int inf = 1e18;
const int mod = 1e9 + 7;

void dfs1(int v) {
  used[v] = true;
  for (size_t i = 0; i < g[v].size(); ++i)
    if (!used[g[v][i]])
      dfs1(g[v][i]);
  order.push_back(v);
}

void dfs2(int v) {
  used[v] = true;
  component.push_back(v);
  for (size_t i = 0; i < gr[v].size(); ++i)
    if (!used[gr[v][i]])
      dfs2(gr[v][i]);
}

int32_t main() {

  cin >> n;
  cin >> m;
  while (m--) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    gr[v].push_back(u);
  }

  memset(used, false, sizeof(used));

  for (int i = 1; i <= n; ++i)
    if (!used[i])
      dfs1(i);

  memset(used, false, sizeof(used));

  for (int i = 0; i < n; ++i) {
    int v = order[n - 1 - i];
    if (!used[v]) {
      dfs2(v);

      // WORK WITH THE SCC here

      component.clear();
    }
  }

  return 0;
}
