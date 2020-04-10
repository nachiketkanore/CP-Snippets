struct UnionFind {
  vector<int> p;
 
  UnionFind(int n) : p(vector<int>(n, 0)) { for(int i = 0; i < n; i++) p[i] = i; }
 
  int findset(int x) { return x == p[x] ? x : p[x] = findset(p[x]); }
 
  void merge(int x, int y) { p[findset(x)] = findset(y); }
};
