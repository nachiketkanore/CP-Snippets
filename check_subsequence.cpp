#define sz(x) (int)(x.size())

bool checkSubsequence(string &s, string &t) {

  if (sz(s) < sz(t))
    return false;

  int id = 0;
  char want = t[0];

  for (int i = 0; i < sz(s); i++) {
    if (s[i] == want) {
      want = t[++id];
      if (id >= sz(t))
        return true;
    }
  }

  if (id >= sz(t))
    return true;
  return false;
}
