#include "bits/stdc++.h"
using namespace std;

#define int long long

inline int rand(int l, int r) {
  static std::mt19937 rng(
      std::chrono::steady_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> uid(l, r);
  return uid(rng);
}
const int N = 1e5 + 4;
#define rep(i, a, n) for (int i = a; i <= n; ++i)

int parent[N];

int find(int x) {
  if (x == parent[x]) {
    return x;
  }
  return parent[x] = find(parent[parent[x]]);
}

void join(int x, int y) {
  int px = find(x);
  int py = find(y);
  parent[px] = py;
}

signed main() {
  int n = rand(1, 10);
  rep(i, 1, n) parent[i] = i;
  cout << "1\n" << n << '\n';
  vector<pair<int, int>> v;
  rep(i, 1, n) rep(j, i + 1, n) v.push_back({i, j});
  random_shuffle(v.begin(), v.end());
  int cnt = 0;
  for (auto i : v) {
    if (find(i.first) != find(i.second)) {
      join(i.first, i.second);
      ++cnt;
      cout << i.first << ' ' << i.second << ' ' << rand(1, n) << '\n';
    }
    if (cnt == n - 1)
      break;
  }
}
