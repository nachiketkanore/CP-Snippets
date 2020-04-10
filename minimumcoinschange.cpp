#include <bits/stdc++.h>
using namespace std;

const int N = 1e6+5, inf = 1e15;
int dp[N + 10];

int solve(int n){
	
	if(n < 0) return inf;
	
	int &ans = dp[n];
	if(ans != inf)
		return ans;
	
	return ans = 1 + min({solve(n - 1), solve(n - 2), solve(n - 5),
				solve(n - 10), solve(n - 20), solve(n - 50),
				solve(n - 100), solve(n - 200), solve(n - 500),
				solve(n - 2000)});
}

int main() {
	
	for(int i = 0; i < N; i++)
		dp[i] = inf;
	dp[0] = 0;
	
	int tc;	cin >> tc;
	while(tc--){
		int n;	cin >> n;
		cout << n << ' ' << solve(n) << '\n';
	}
	
	return 0;
}
