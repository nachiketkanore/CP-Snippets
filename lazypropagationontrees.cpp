//Problem : https://codeforces.com/contest/620/problem/E

#include "bits/stdc++.h"
using namespace std;

const int N = 4e5 + 5;

long long tree[N<<2], laz[N<<2];
int n, m, x, y, c[N];
vector<int>adj[N];

int in[N], out[N], timer;
void push(int node, int s, int e){
  if(!laz[node])return;
  tree[node] = laz[node];
  if(s!=e)
    laz[node<<1] = laz[node<<1 | 1] = laz[node];
  laz[node] = 0;
}
void upd(int node, int s, int e, int l, int r, int v){
  push(node,s,e);
  if(r<s||e<l||l>r)return;
  if(l<=s&&e<=r){
    laz[node] = 1ll << v;
    push(node,s,e);
    return;
  }
  int md = (s+e) >> 1;
  upd(node<<1,s,md,l,r,v);
  upd(node<<1|1,md+1,e,l,r,v);
  tree[node] = tree[node<<1] | tree[node<<1|1];
}
long long qry(int node, int s, int e, int l, int r){
  push(node,s,e);
  if(r<s||e<l||l>r)return 0;
  if(l<=s&&e<=r)return tree[node];
  int md = (s+e)>>1;
  return qry(node<<1,s,md,l,r) |
  qry(node<<1|1,md+1,e,l,r);
}
void dfs(int u, int p){
  in[u] = timer++;
  for(auto v : adj[u])if(v != p)
    dfs(v,u);
  out[u] = timer;
}

int main(){

  scanf("%d%d", &n, &m);

  for(int i = 0; i < n; i++)
    scanf("%d", c + i), --c[i];

  for(int i = 0; i < n - 1; i++){

    scanf("%d%d", &x, &y);
    --x, --y;
    adj[x].push_back(y);
    adj[y].push_back(x);

  }
  dfs(0,0);
  for(int i = 0; i < n; i++)upd(1,0,n-1,in[i],in[i], c[i]);
  int t, v, c;
  while(m--){

    scanf("%d", &t);

    if(t == 1){
      scanf("%d%d", &v, &c);--v;--c;
      upd(1,0,n-1,in[v],out[v]-1,c);
    }
    else{
      scanf("%d", & v);--v;
      long long mask = qry(1,0,n-1,in[v],out[v]-1);
      printf("%d\n",__builtin_popcountll(mask));
    }

  }
}
