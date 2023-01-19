// Problem :
// https://codedrills.io/contests/amrita-icpc-practice-session-2/problems/secure-city

#include <bits/stdc++.h>

#define int int64_t
#define pb push_back
#define sz(x) (int)(x.size())
#define ALL(x) (x).begin(), (x).end()
#define F0R(i, R) for (int i = (0); i < (R); ++i)
#define FOR(i, L, R) for (int i = (L); i <= (R); ++i)

using namespace std;

struct $ {
  $() {
    ios::sync_with_stdio(0);
    cin.tie(0);
  }
} $;

template <class T> bool cmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <class T> bool cmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

struct FlowEdge {
  int v, u;
  long long cap, flow = 0;
  FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
  const long long flow_inf = 1e18;
  vector<FlowEdge> edges;
  vector<vector<int>> adj;
  int n, m = 0;
  int s, t;
  vector<int> level, ptr;
  queue<int> q;

  Dinic(int n, int s, int t) : n(n), s(s), t(t) {
    adj.resize(n);
    level.resize(n);
    ptr.resize(n);
  }

  void add_edge(int v, int u, long long cap) {
    edges.emplace_back(v, u, cap);
    edges.emplace_back(u, v, 0);
    adj[v].push_back(m);
    adj[u].push_back(m + 1);
    m += 2;
  }

  bool bfs() {
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (int id : adj[v]) {
        if (edges[id].cap - edges[id].flow < 1)
          continue;
        if (level[edges[id].u] != -1)
          continue;
        level[edges[id].u] = level[v] + 1;
        q.push(edges[id].u);
      }
    }
    return level[t] != -1;
  }

  long long dfs(int v, long long pushed) {
    if (pushed == 0)
      return 0;
    if (v == t)
      return pushed;
    for (int &cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
      int id = adj[v][cid];
      int u = edges[id].u;
      if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
        continue;
      long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
      if (tr == 0)
        continue;
      edges[id].flow += tr;
      edges[id ^ 1].flow -= tr;
      return tr;
    }
    return 0;
  }

  long long flow() {
    long long f = 0;
    while (true) {
      fill(level.begin(), level.end(), -1);
      level[s] = 0;
      q.push(s);
      if (!bfs())
        break;
      fill(ptr.begin(), ptr.end(), 0);
      while (long long pushed = dfs(s, flow_inf)) {
        f += pushed;
      }
    }
    return f;
  }
};
const int inf = 1e18;
const int N = 5e5 + 5;

int32_t main() {
  int n, m;
  cin >> n >> m;

  vector<vector<char>> mat(n + 1, vector<char>(m + 1));
  vector<vector<int>> in(n + 1, vector<int>(m + 1));
  vector<vector<int>> out(n + 1, vector<int>(m + 1));
  int id = 1;
  FOR(i, 1, n) FOR(j, 1, m) {
    cin >> mat[i][j];
    in[i][j] = id;
    out[i][j] = id + 1;
    id += 2;
  }

  vector<vector<int>> border_pts;
  FOR(i, 1, n) FOR(j, 1, m) if (mat[i][j] == '_') {
    if (i == 1 || i == n || j == 1 || j == m)
      border_pts.push_back({in[i][j], out[i][j]});
  }

  if (sz(border_pts) ^ 4) {
    cout << "Unsecured\n";
    return 0;
  }

  const vector<int> dx = {1, -1, 0, 0};
  const vector<int> dy = {0, 0, 1, -1};

  auto add_graph = [&](Dinic &flower) {
    FOR(i, 1, n) FOR(j, 1, m) if (mat[i][j] == '_') {
      F0R(k, 4) {
        int ni = i + dx[k];
        int nj = j + dy[k];
        if (ni >= 1 && ni <= n && nj >= 1 && nj <= m)
          if (mat[ni][nj] == '_') {
            int u = out[i][j];
            int v = in[ni][nj];
            flower.add_edge(u, v, 1);
          }
      }
    }
    FOR(i, 1, n) FOR(j, 1, m) { flower.add_edge(in[i][j], out[i][j], 1); }
  };

  F0R(rev, 2) F0R(mask, 1 << 4) if (__builtin_popcount(mask) == 2) {
    vector<vector<int>> starts, ends;
    F0R(j, 4) {
      if (rev) {
        if (mask >> j & 1)
          starts.push_back(border_pts[j]);
        else
          ends.push_back(border_pts[j]);
      } else {
        if (mask >> j & 1)
          ends.push_back(border_pts[j]);
        else
          starts.push_back(border_pts[j]);
      }
    }

    assert(sz(starts) == 2 && sz(ends) == 2);

    int source = 0, sink = id;
    int nodes = sink + 1;

    Dinic flower(nodes, source, sink);

    flower.add_edge(source, starts[0][0], 1);
    flower.add_edge(source, starts[1][0], 1);
    flower.add_edge(ends[0][1], sink, 1);
    flower.add_edge(ends[1][1], sink, 1);

    add_graph(flower);

    int flow = flower.flow();
    if (flow >= 2) {
      cout << "Secured\n";
      return 0;
    }
  }

  cout << "Unsecured\n";
}
