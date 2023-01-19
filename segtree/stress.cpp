#include <cassert>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

#define int long long
#define sz(x) (int)(x.size())
#define FOR(i, L, R) for (int i = (L); i <= (R); i++)
using namespace std;

int a[1002];

class node {
public:
  static const int inf = 1e18;
  int mn, mx, sum;

  node(int _mn, int _mx, int _sum) {
    mn = _mn;
    mx = _mx;
    sum = _sum;
  }

  node() {
    mn = inf;
    mx = -inf;
    sum = 0;
  }
};

struct segtree {
  int N;
  vector<node> st;
  vector<bool> cLazy;
  vector<int> lazy;

  void init(int n) {
    N = n;
    st.resize((N << 2) + 2);
    cLazy.assign((N << 2) + 2, false);
    lazy.assign((N << 2) + 2, 0);
    build(1, 1, N);
  }

  // Write reqd merge functions
  void merge(node &ret, node &left, node &right) {
    ret.mn = min(left.mn, right.mn);
    ret.mx = max(left.mx, right.mx);
    ret.sum = left.sum + right.sum;
  }

  // Handle lazy propagation appriopriately
  void propagate(int u, int L, int R) {
    // Propagate down?
    if (L != R) {
      cLazy[u * 2] = 1;
      cLazy[u * 2 + 1] = 1;
      lazy[u * 2] += lazy[u];
      lazy[u * 2 + 1] += lazy[u];
    }

    // Updating the range [L, R] with lazy[u]
    {
      // Default range update operation is :
      // adding lazy[u] to all elements in range [...]
      st[u].sum += (R - L + 1) * lazy[u];
      st[u].mx += lazy[u];
      st[u].mn += lazy[u];
    }
    cLazy[u] = 0;
    lazy[u] = 0;
  }

  void build(int u, int L, int R) {
    if (L == R) {
      // Leaf value
      st[u] = node(a[L], a[L], a[L]);
      return;
    }
    int M = (L + R) / 2;
    build(u * 2, L, M);
    build(u * 2 + 1, M + 1, R);
    merge(st[u], st[u * 2], st[u * 2 + 1]);
  }

  node Query(int u, int L, int R, int i, int j) {
    if (cLazy[u])
      propagate(u, L, R);
    if (j < L || i > R)
      return node();
    if (i <= L && R <= j)
      return st[u];
    int M = (L + R) / 2;
    node left = Query(u * 2, L, M, i, j);
    node right = Query(u * 2 + 1, M + 1, R, i, j);
    node ret;
    merge(ret, left, right);
    return ret;
  }

  node pQuery(int u, int L, int R, int pos) {
    if (cLazy[u])
      propagate(u, L, R);
    if (L == R)
      return st[u];
    int M = (L + R) / 2;
    if (pos <= M)
      return pQuery(u * 2, L, M, pos);
    else
      return pQuery(u * 2 + 1, M + 1, R, pos);
  }

  void Update(int u, int L, int R, int i, int j, int val) {
    if (cLazy[u])
      propagate(u, L, R);
    if (j < L || i > R)
      return;
    if (i <= L && R <= j) {
      // Default range update operation is :
      // adding val to all elements in range [...]
      cLazy[u] = 1;
      lazy[u] = val;
      propagate(u, L, R);
      return;
    }
    int M = (L + R) / 2;
    Update(u * 2, L, M, i, j, val);
    Update(u * 2 + 1, M + 1, R, i, j, val);
    merge(st[u], st[u * 2], st[u * 2 + 1]);
  }

  void pUpdate(int u, int L, int R, int pos, int val) {
    if (cLazy[u])
      propagate(u, L, R);
    if (L == R) {
      cLazy[u] = 1;
      lazy[u] = val;
      propagate(u, L, R);
      return;
    }
    int M = (L + R) / 2;
    if (pos <= M)
      pUpdate(u * 2, L, M, pos, val);
    else
      pUpdate(u * 2 + 1, M + 1, R, pos, val);
    merge(st[u], st[u * 2], st[u * 2 + 1]);
  }

  node query(int pos) { return pQuery(1, 1, N, pos); }

  node query(int l, int r) { return Query(1, 1, N, l, r); }

  void update(int pos, int val) { pUpdate(1, 1, N, pos, val); }

  void update(int l, int r, int val) { Update(1, 1, N, l, r, val); }
};

inline int rand(int l, int r) {
  static std::mt19937 rng(
      std::chrono::steady_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> uid(l, r);
  return uid(rng);
}

int getSum(int L, int R) {
  int ret = 0;
  FOR(i, L, R) ret += a[i];
  return ret;
}

int getMin(int L, int R) {
  int ret = a[L];
  FOR(i, L, R) ret = min(ret, a[i]);
  return ret;
}

int getMax(int L, int R) {
  int ret = a[L];
  FOR(i, L, R) ret = max(ret, a[i]);
  return ret;
}

int32_t main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int N = rand(1, 1000);
  segtree tree;
  FOR(i, 1, N) { a[i] = rand(1, 2121); }
  tree.init(N);

  int Q = 200;
  while (Q--) {
    int type = rand(1, 4);
    if (type >= 3) {
      // Add `val` to all [L, R]
      int L = rand(1, N);
      int R = rand(L, N);
      int val = rand(1, 2121);
      FOR(i, L, R) a[i] += val;
      tree.update(L, R, val);
    } else {
      // Query functions in range [L, R]
      int L = rand(1, N);
      int R = rand(L, N);
      node get = tree.query(L, R);
      node slow(getMin(L, R), getMax(L, R), getSum(L, R));
      assert(get.mn == slow.mn);
      assert(get.mx == slow.mx);
      assert(get.sum == slow.sum);
    }

    // checking whole array is correct
    FOR(i, 1, N) {
      node val = tree.query(i);
      assert(val.mn == val.mx && val.mx == val.sum);
      assert(a[i] == val.mn);
    }
  }
}
