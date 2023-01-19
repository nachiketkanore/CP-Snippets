
const int N = 1e4 + 5, M = 1e6 + 5;
const int inf = 1e18;
const int mod = 1e9 + 7;
int a[N], n, spf[M], mx[M];
bool prime[M];

void pre() {
  fill(prime + 2, prime + M, true);
  for (int i = 2; i < M; i++) {
    if (prime[i]) {
      spf[i] = i;
      for (int j = 2 * i; j < M; j += i)
        spf[j] = i, prime[j] = false;
    }
  }
}

int32_t main() {

  pre();

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    int val = a[i];
    while (val > 1) {
      int p = spf[val], cnt = 0;
      while (val % p == 0)
        ++cnt, val /= p;
      mx[p] = max(mx[p], cnt);
    }
  }
  vector<pair<int, int>> LCM;
  for (int i = 2; i < M; i++)
    if (mx[i] > 0)
      LCM.push_back({i, mx[i]});

  // LCM is stored in the form of prime factorization of it in the vector : LCM
  for (auto it : LCM)
    cout << it.first << "^" << it.second << ' ';
  cout << '\n';
}
