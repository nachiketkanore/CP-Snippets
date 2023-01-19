// https://codedrills.io/contests/amrita-icpc-practice-session-3/problems/unique-strings
// NTT problem: Counting number of unique possible strings using given
// frequencies of characters

#include <bits/stdc++.h>

#define int int64_t
#define pb push_back
#define sz(x) (int)(x.size())
#define ALL(x) (x).begin(), (x).end()
#define F0R(i, R) for (int i = (0); i < (R); ++i)
#define FOR(i, L, R) for (int i = (L); i <= (R); ++i)

using namespace std;

struct $ {
  $() {
    ios::sync_with_stdio(0);
    cin.tie(0);
  }
} $;

template <class T> bool cmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <class T> bool cmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

const int MOD = 1e9 + 7;

int mod_pow(int a, int b, int mod = MOD) {
  int ret = 1;
  a %= mod;
  while (b > 0) {
    if (b % 2)
      ret = ret * a % mod;
    b /= 2;
    a = a * a % mod;
  }
  return ret;
}

int mod_mul(int a, int b) { return a * b % MOD; }
int mod_sub(int a, int b) { return (a - b + MOD) % MOD; }
int mod_add(int a, int b) { return (a + b) % MOD; }
int mod_inv(int a) { return mod_pow(a, MOD - 2, MOD); }

// NTT template from neal
namespace NTT {
vector<int> roots = {0, 1};
vector<int> bit_reverse;
int max_size = -1;
int root;

bool is_power_of_two(int n) { return (n & (n - 1)) == 0; }

int round_up_power_two(int n) {
  assert(n > 0);

  while (n & (n - 1))
    n = (n | (n - 1)) + 1;

  return n;
}

// Given n (a power of two), finds k such that n == 1 << k.
int get_length(int n) {
  assert(is_power_of_two(n));
  return __builtin_ctz(n);
}

// Rearranges the indices to be sorted by lowest bit first, then second lowest,
// etc., rather than highest bit first. This makes even-odd div-conquer much
// easier.
void bit_reorder(int n, vector<int> &values) {
  if ((int)bit_reverse.size() != n) {
    bit_reverse.assign(n, 0);
    int length = get_length(n);

    for (int i = 0; i < n; i++)
      bit_reverse[i] = (bit_reverse[i >> 1] >> 1) + ((i & 1) << (length - 1));
  }

  for (int i = 0; i < n; i++)
    if (i < bit_reverse[i])
      swap(values[i], values[bit_reverse[i]]);
}

void find_root() {
  int order = MOD - 1;
  max_size = 1;

  while (order % 2 == 0) {
    order /= 2;
    max_size *= 2;
  }

  root = 2;

  // Find a max_size-th primitive root of MOD.
  while (!(mod_pow(root, max_size) == 1 && mod_pow(root, max_size / 2) != 1))
    root++;
}

void prepare_roots(int n) {
  if (max_size < 0)
    find_root();

  if ((int)roots.size() >= n)
    return;

  int length = get_length(roots.size());
  roots.resize(n);

  // The roots array is set up such that for a given power of two n >= 2,
  // roots[n / 2] through roots[n - 1] are the first half of the n-th primitive
  // roots of MOD.
  while (1 << length < n) {
    // z is a 2^(length + 1)-th primitive root of MOD.
    int z = mod_pow(root, max_size >> (length + 1));

    for (int i = 1 << (length - 1); i < 1 << length; i++) {
      roots[2 * i] = roots[i];
      roots[2 * i + 1] = mod_mul(roots[i], z);
    }

    length++;
  }
}

void fft_iterative(int N, vector<int> &values) {
  assert(is_power_of_two(N));
  prepare_roots(N);
  bit_reorder(N, values);
  assert(N <= max_size);

  for (int n = 1; n < N; n *= 2)
    for (int start = 0; start < N; start += 2 * n)
      for (int i = 0; i < n; i++) {
        int even = values[start + i];
        int odd = mod_mul(values[start + n + i], roots[n + i]);
        values[start + n + i] = mod_sub(even, odd);
        values[start + i] = mod_add(even, odd);
      }
}

const int FFT_CUTOFF = 450;

vector<int> mod_multiply(vector<int> left, vector<int> right,
                         bool trim = true) {
  int n = left.size();
  int m = right.size();

  for (int i = 0; i < n; i++)
    assert(0 <= left[i] && left[i] < MOD);

  for (int i = 0; i < m; i++)
    assert(0 <= right[i] && right[i] < MOD);

  // Brute force when either n or m is small enough.
  if (min(n, m) < FFT_CUTOFF) {
    const uint64_t ULL_BOUND =
        numeric_limits<uint64_t>::max() - (uint64_t)MOD * MOD;
    vector<uint64_t> result(n + m - 1);

    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++) {
        result[i + j] += (uint64_t)left[i] * right[j];

        if (result[i + j] > ULL_BOUND)
          result[i + j] %= MOD;
      }

    for (int i = 0; i < (int)result.size(); i++)
      if (result[i] >= (uint64_t)MOD)
        result[i] %= MOD;

    if (trim) {
      while (!result.empty() && result.back() == 0)
        result.pop_back();
    }

    return vector<int>(result.begin(), result.end());
  }

  int N = round_up_power_two(n + m - 1);
  left.resize(N);
  right.resize(N);

  bool equal = left == right;
  fft_iterative(N, left);

  if (equal)
    right = left;
  else
    fft_iterative(N, right);

  int inv_N = mod_inv(N);

  for (int i = 0; i < N; i++)
    left[i] = mod_mul(mod_mul(left[i], right[i]), inv_N);

  reverse(left.begin() + 1, left.end());
  fft_iterative(N, left);
  left.resize(n + m - 1);

  if (trim) {
    while (!left.empty() && left.back() == 0)
      left.pop_back();
  }

  return left;
}

vector<int> power(const vector<int> &v, int exponent) {
  assert(exponent >= 0);
  vector<int> result = {1};

  if (exponent == 0)
    return result;

  for (int k = 31 - __builtin_clz(exponent); k >= 0; k--) {
    result = mod_multiply(result, result);

    if (exponent & 1 << k)
      result = mod_multiply(result, v);
  }

  return result;
}
}; // namespace NTT

struct mi {
  using ll = long long;
  ll v;
  explicit operator ll() const { return v; }
  mi() { v = 0; }
  mi(ll _v) {
    v = (-MOD < _v && _v < MOD) ? _v : _v % MOD;
    if (v < 0)
      v += MOD;
  }
  friend bool operator==(const mi &a, const mi &b) { return a.v == b.v; }
  friend bool operator!=(const mi &a, const mi &b) { return !(a == b); }
  friend bool operator<(const mi &a, const mi &b) { return a.v < b.v; }
  mi &operator+=(const mi &m) {
    if ((v += m.v) >= MOD)
      v -= MOD;
    return *this;
  }
  mi &operator-=(const mi &m) {
    if ((v -= m.v) < 0)
      v += MOD;
    return *this;
  }
  mi &operator*=(const mi &m) {
    v = v * m.v % MOD;
    return *this;
  }
  mi &operator/=(const mi &m) { return (*this) *= inv(m); }

  friend mi pow(mi a, ll p) {
    mi ans = 1;
    assert(p >= 0);
    for (; p; p /= 2, a *= a)
      if (p & 1)
        ans *= a;
    return ans;
  }
  friend mi inv(const mi &a) {
    assert(a.v != 0);
    return pow(a, MOD - 2);
  }

  mi operator-() const { return mi(-v); }
  mi &operator++() { return *this += 1; }
  mi &operator--() { return *this -= 1; }
  mi operator++(int32_t) {
    mi temp;
    temp.v = v++;
    return temp;
  }
  mi operator--(int32_t) {
    mi temp;
    temp.v = v--;
    return temp;
  }
  friend mi operator+(mi a, const mi &b) { return a += b; }
  friend mi operator-(mi a, const mi &b) { return a -= b; }
  friend mi operator*(mi a, const mi &b) { return a *= b; }
  friend mi operator/(mi a, const mi &b) { return a /= b; }
  friend ostream &operator<<(ostream &os, const mi &m) {
    os << m.v;
    return os;
  }
  friend istream &operator>>(istream &is, mi &m) {
    ll x;
    is >> x;
    m.v = x;
    return is;
  }
};

const int N = 5005;
mi ifact[N + 1], fact[N + 1];

int32_t main() {

  fact[0] = 1;
  FOR(i, 1, N) fact[i] = i * fact[i - 1];
  FOR(i, 0, N) ifact[i] = mi(1) / fact[i];

  string s;
  cin >> s;
  vector<int> f(26);
  for (char ch : s)
    f[ch - 'a']++;

  vector<int> result = {1}; // 1.x^0 <-- initial result polynomial

  F0R(ch, 26) {
    if (!f[ch])
      continue;
    vector<int> poly(f[ch] + 1);
    FOR(cnt, 0, f[ch]) { poly[cnt] = ifact[cnt].v; }
    result = NTT::mod_multiply(result, poly);
  }

  mi ans = 0;
  FOR(len, 1, sz(s)) {
    if (len < sz(result)) {
      ans += fact[len] * result[len];
    }
  }

  cout << ans << '\n';
}
