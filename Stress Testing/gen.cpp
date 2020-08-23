#include "bits/stdc++.h"
using namespace std;

#define sz(x) (int)(x.size())
#define FOR(i,L,R) for(int i = L; i <= R; i++)
#define int long long

const int N = 2e5 + 2, inf = 1e18;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int getRand(int l, int r)
{
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int32_t main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr); cout.tie(nullptr);

  int n = getRand(1,100000);
  cout << n << '\n';
  FOR(i,1,n) {
    cout << getRand(1, 9) << ' ';
  }
  cout << '\n';
}
