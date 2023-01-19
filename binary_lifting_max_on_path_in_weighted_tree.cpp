// Problem : Minimum spanning tree for each edge
//  Link to problem : https://codeforces.com/contest/609/problem/E

#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 5e5 + 10;
int n, m, anc[20][N], mx[20][N], dep[N], total, ans[N], par[N];
vector<array<int, 2>> g[N];

struct edge {
  int u, v, w, id;
  bool operator<(const edge &other) const { return w < other.w; }
} E[N];

int find(int u) {
  if (u == par[u])
    return u;
  par[u] = find(par[u]);
  return par[u];
}

bool unite(int u, int v) {
  u = find(u), v = find(v);
  if (u == v)
    return false;
  par[v] = u;
  return true;
}

void dfs(int node, int p = -1, int currWeight = -1, int dist = 0) {
  dep[node] = dist;
  anc[0][node] = p;
  mx[0][node] = currWeight;
  for (int i = 1; i < 20; i++) {
    anc[i][node] = anc[i - 1][anc[i - 1][node]];
    mx[i][node] = max(mx[i - 1][node], mx[i - 1][anc[i - 1][node]]);
  }

  for (auto next : g[node]) {
    if (next[0] != p) {
      dfs(next[0], node, next[1], dist + 1);
    }
  }
}

int maxOnPath(int u, int v) {
  if (dep[u] < dep[v])
    swap(u, v);
  int diff = dep[u] - dep[v];
  int ret = 0;
  for (int i = 0; i < 20; i++) {
    if (diff & (1LL << i)) {
      ret = max(ret, mx[i][u]);
      u = anc[i][u];
    }
  }

  assert(dep[u] == dep[v]);

  for (int i = 19; i >= 0; i--) {
    if (anc[i][u] != anc[i][v]) {
      ret = max({ret, mx[i][u], mx[i][v]});
      u = anc[i][u];
      v = anc[i][v];
    }
  }
  if (u != v)
    ret = max({ret, mx[0][u], mx[0][v]});
  return ret;
}

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n >> m;

  for (int i = 0; i < m; i++) {
    cin >> E[i].u >> E[i].v >> E[i].w;
    E[i].id = i;
  }

  for (int i = 1; i <= n; i++)
    par[i] = i;

  sort(E, E + m);

  for (int i = 0; i < m; i++) {
    if (unite(E[i].u, E[i].v)) {
      total += E[i].w;
      g[E[i].u].push_back({E[i].v, E[i].w});
      g[E[i].v].push_back({E[i].u, E[i].w});
    }
  }

  dfs(1);

  for (int i = 0; i < m; i++) {
    ans[E[i].id] = total - maxOnPath(E[i].u, E[i].v) + E[i].w;
  }

  for (int i = 0; i < m; i++)
    cout << ans[i] << '\n';
}