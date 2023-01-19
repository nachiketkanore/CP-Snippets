
// NOT strictly increasing
int LIS() {
  multiset<int> seq;
  for (int i = 1; i <= n; i++) {
    seq.insert(a[i]);
    auto it = seq.upper_bound(a[i]);
    if (it != seq.end())
      seq.erase(it);
  }

  /*
  NOTE : Only strictly increasing subsequence
  cout << "The contents of LIS are : ";
  for(int i : seq)
          cout << i << ' ';

  */

  return sz(seq);
}
