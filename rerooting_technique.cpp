// Problem : https://codeforces.com/problemset/problem/1324/F
//  https://www.hackerrank.com/contests/all-india-contest-by-mission-helix-19-september/challenges/0-1-tree-again
/*
Basic Idea :
1. Root the tree at some node (say 1).
2. Calculate DP considering 1 as root.
3. When we shift root from 1 to one of its child, only DP[1] and DP[child]
change.
4. Remove contribution of child from par, then add contribution of par to child.
(order is imp)
5. Now DP[child] is answer considering child as root.
6. Don't forget to reassign old values when you exit from a subtree.

*/

#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)(x.size())
#define FOR(x, y, z) for (int x = y; x <= z; x++)
#define int long long

const int N = 2e5 + 2, inf = 1e18;

int n, u, v, a[N], dp[N], best[N];
vector<int> g[N];

void dfs1(int u, int par) {
  dp[u] = a[u];
  for (int child : g[u])
    if (child != par) {
      dfs1(child, u);
      if (dp[child] > 0) // take only positive branches to maximize answer
        dp[u] += dp[child];
    }
}

void dfs2(int u, int par) {
  best[u] = dp[u];

  for (int child : g[u])
    if (child != par) {
      dp[u] -= max(0LL, dp[child]);
      dp[child] += max(0LL, dp[u]);
      dfs2(child, u);
      dp[child] -= max(0LL, dp[u]);
      dp[u] += max(0LL, dp[child]);
    }
}

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n;
  FOR(i, 1, n) {
    cin >> a[i];
    if (a[i] == 0)
      a[i] = -1;
  }
  FOR(i, 2, n) {
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  dfs1(1, 1);
  dfs2(1, 1);

  FOR(i, 1, n)
  cout << best[i] << ' ';
}
