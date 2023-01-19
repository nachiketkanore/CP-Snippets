vector<int> z_algorithm(string pattern) {
  // Z[i] = for the suffix [i, n) of pattern, the longest prefix that is also a
  // prefix of pattern.
  int n = pattern.size();
  vector<int> Z(n, 0);
  Z[0] = n;
  int loc = 1;

  for (int i = 1; i < n; i++) {
    if (i < loc + Z[loc])
      Z[i] = min(Z[i - loc], loc + Z[loc] - i);

    while (i + Z[i] < n && pattern[Z[i]] == pattern[i + Z[i]])
      Z[i]++;

    if (i + Z[i] > loc + Z[loc])
      loc = i;
  }

  return Z;
}