// Problem : https://open.kattis.com/problems/joinstrings

#include <bits/stdc++.h>
#define sz(x) (int)(x.size())
using namespace std;

// const int inf = 1e12;
const int N = 1e5 + 5;
int n, first[N], last[N], in[N];
std::vector<int> g[N];
string s[N];

void dfs(int u){
	cout << s[u];
	for(int v : g[u])
		dfs(v);
}

int32_t main(){ 

	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> s[i];
		last[i] = i, 
		first[i] = i;
	}

	for(int i = 1; i < n; i++){
		int a, b;
		cin >> a >> b;
		int u = last[a], v = first[b];
		g[u].push_back(v);
		in[v]++;
		last[a] = last[b];

	}

	for(int i = 1; i <= n; i++){
		if(in[i] == 0){
			dfs(i);
			break;
		}
	}

}