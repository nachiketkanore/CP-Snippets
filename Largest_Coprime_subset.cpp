//Problem : https://www.hackerearth.com/practice/algorithms/dynamic-programming/bit-masking/practice-problems/algorithm/sherlock-and-coprime-subset/

#include "bits/stdc++.h"
#define int long long
#define sz(x) (int)(x.size())
using namespace std;

const int N = 55, M = 52, inf = 1e18, mod = 1e9 + 7;

int n, a[N], idx[N], numMask[N], dp[N][1 << 16];
std::vector<int> primes; 

int go(int id, int mask){
    if(id > n)
        return 0;

    int &ans = dp[id][mask];
    if(~ans)
        return ans;

    int c1 = 0;
    if((numMask[a[id]] & mask) == 0){
        int newMask = mask | numMask[a[id]];
        c1 = 1 + go(id + 1, newMask);
    }
    int c2 = go(id + 1, mask);

    return ans = max(c1, c2);
}

void solve(){
    memset(dp, -1, sizeof(dp));
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    cout << go(1,0) << '\n';
}

bool prime(int n){
    if(n < 2)
        return false;
    for(int i = 2; i * i <= n; i++)
        if(n % i == 0)
            return false;
    return true;
}
 
void pre(){
    for(int i = 2; i < M; i++) if(prime(i)) {
        idx[i] = primes.size();
        primes.push_back(i);
    }
 
    for(int i = 2; i < M; i++) {
        int val = i;
        for(int j = 2; j <= val; j++) {
            int has = false;
            while(val % j == 0) {
                val /= j;
                has = true;
            }
            if(has)
                numMask[i] |= (1 << idx[j]);
        }
    }
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);  

    pre();

    int t;
    cin >> t;
    while(t--)
        solve();
}
