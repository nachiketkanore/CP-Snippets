const int M = 1e6 + 5, mod = 1e9 + 7;
int inv[M];

void pre() {

  inv[0] = inv[1] = 1;
  int m = mod;
  for (int i = 2; i < M; ++i)
    inv[i] = (m - (m / i) * inv[m % i] % m) % m;
}
