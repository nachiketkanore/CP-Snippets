const int N = 1e6 + 50; // Can go upto N = 1e7
int spf[N + 10];

void SPF() {

  spf[1] = 1;

  for (int i = 2; i <= N; i++)
    if (spf[i] == 0) {
      spf[i] = i;
      for (int j = 2 * i; j <= N; j += i)
        if (spf[j] == 0)
          spf[j] = i;
    }
}
