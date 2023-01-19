inline void WriteInt(int x) {
  int p = 1;
  for (int temp = x / 10; temp > 0; temp /= 10)
    p *= 10;
  for (; p > 0; x %= p, p /= 10)
    putchar(x / p + '0');
}
