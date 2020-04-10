#include<bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5, mod = 1e9 + 7;
int factMod[N];

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

int modInverse(int n, int p){
	return power(n, p-2, p);
}

void pre(int p = mod){
	factMod[0] = factMod[1] = 1;
	for(int i = 2; i < N; i++)
		factMod[i] = i * factMod[i-1] % p;

}

int calc(int n, int r, int p = mod){
	if(r == 0)
		return 1;

	int ans = (factMod[n]* modInverse(factMod[r], p) % p * modInverse(factMod[n-r], p) % p) % p; 
	return ans;
}

int main(){
	pre();
	int n = 10, r = 2, p = 13;
	cout << calc(n,r,p);
}