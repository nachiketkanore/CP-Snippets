const int N = 1e6 + 5, mod = 1e9 + 7;
int factMod[N];

void pre() {
  factMod[0] = factMod[1] = 1;
  for (int i = 2; i < N; i++)
    factMod[i] = i * factMod[i - 1] % mod;
}