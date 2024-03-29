const int N = 2e5 + 50;
struct DSU {
  int connected;
  int par[N], sz[N];

  void init(int n) {
    for (int i = 1; i <= n; i++) {
      par[i] = i;
      sz[i] = 1;
    }
    connected = n;
  }

  int getPar(int k) {
    while (k != par[k]) {
      par[k] = par[par[k]];
      k = par[k];
    }
    return k;
  }

  int getSize(int k) { return sz[getPar(k)]; }

  bool same(int u, int v) { return (getPar(u) == getPar(v)); }

  bool unite(int u, int v) {
    int par1 = getPar(u), par2 = getPar(v);

    if (par1 == par2)
      return false;

    connected--;

    if (sz[par1] > sz[par2])
      swap(par1, par2);

    sz[par2] += sz[par1];
    sz[par1] = 0;
    par[par1] = par[par2];
    return true;
  }
};

DSU dsu;
