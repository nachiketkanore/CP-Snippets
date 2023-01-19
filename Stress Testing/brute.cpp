#include "bits/stdc++.h"
using namespace std;

#define sz(x) (int)(x.size())
#define FOR(i, L, R) for (int i = L; i <= R; i++)
#define int long long

const int N = 2e5 + 2, inf = 1e18;

int go(int rem) {
  if (rem == 0)
    return 0;
  int ans = 0;
  cin >> ans;
  return ans + go(rem - 1);
}

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;
  cout << go(n);
}
