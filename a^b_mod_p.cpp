const int mod = 1e9 + 7;

int power(int a, int b, int p = mod){
	int ret = 1;
	a %= p;
	while(b > 0){
		if(b % 2 == 1)
			ret = ret * a % p;
		b /= 2;
		a = a * a % p;
	}
	return ret;
}