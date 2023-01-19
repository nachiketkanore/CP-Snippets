int power(int a, int b) {
  int ret = 1;
  while (b > 0) {
    if (b % 2 == 1)
      ret = ret * a;
    b /= 2;
    a = a * a;
  }
  return ret;
}