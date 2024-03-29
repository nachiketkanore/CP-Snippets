// Problem : https://codeforces.com/contest/1036/problem/C

#include <bits/stdc++.h>
#define int long long
#define sz(x) (int)(x.size())
using namespace std;

const int N = 20, mod = 1e9 + 7, inf = 1e18;

string A, B;
int n, dp[N][2][2][5];

int go(int pos, bool bigA, bool smallB, int cnt) {
  if (cnt > 3)
    return 0;
  if (pos >= n)
    return 1;

  int &ans = dp[pos][bigA][smallB][cnt];
  if (~ans)
    return ans;
  ans = 0;
  for (int i = 0; i < 10; i++) {
    if (!bigA && i < A[pos] - '0')
      continue;
    if (!smallB && i > B[pos] - '0')
      continue;

    ans += go(pos + 1, bigA || (i > A[pos] - '0'), smallB || (i < B[pos] - '0'),
              cnt + (i != 0));
  }
  return ans;
}

int32_t main() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  int t;
  cin >> t;
  while (t--) {
    memset(dp, -1, sizeof(dp));
    cin >> A >> B;
    reverse(A.begin(), A.end());
    while (sz(A) < sz(B))
      A.push_back('0');
    reverse(A.begin(), A.end());
    n = sz(B);
    int ans = 0;

    for (int i = 0; i < 10; i++) {
      if (i < A[0] - '0')
        continue;
      if (i > B[0] - '0')
        continue;

      ans += go(1, i > A[0] - '0', i < B[0] - '0', i != 0);
    }
    cout << ans << '\n';
  }
}
