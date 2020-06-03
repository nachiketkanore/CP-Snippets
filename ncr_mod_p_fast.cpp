long long modpow(long long a, long long b, long long m) {
	long long p = 1, q = a;
	for (int i = 0; i < 32; i++) {
		if ((b / (1LL << i)) % 2 == 1) { p *= q; p %= m; }
		q *= q; q %= m;
	}
	return p;
}
 
long long Div(long long a, long long b, long long m) {
	return (a * modpow(b, m - 2, m)) % m;
}
 
long long mod = 998244353;
long long fact[1 << 19], factinv[1 << 19];
 
void init() {
	fact[0] = 1;
	for (int i = 1; i <= 400000; i++) fact[i] = (1LL * i * fact[i - 1]) % mod;
	for (int i = 0; i <= 400000; i++) factinv[i] = Div(1, fact[i], mod);
}
 
long long ncr(long long n, long long r) {
	return (fact[n] * factinv[r] % mod) * factinv[n - r] % mod;
}
