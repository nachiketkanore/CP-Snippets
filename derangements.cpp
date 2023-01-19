
const int N = 5e5 + 10;
int der[N + 5];

void countDer() {

  // Base cases
  der[0] = 1;
  der[1] = 0;
  der[2] = 1;

  for (int i = 3; i <= N; ++i)
    der[i] = (i - 1) * (der[i - 1] + der[i - 2]);
}
