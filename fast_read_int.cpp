inline int ReadInt() {
  char c;
  while (c = getchar(), c < '0' || c > '9')
    ;
  int x = c - '0';
  while (c = getchar(), c >= '0' && c <= '9')
    x = x * 10 + c - '0';
  return x;
}
