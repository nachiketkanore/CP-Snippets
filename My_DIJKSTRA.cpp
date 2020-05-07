#include <bits/stdc++.h>
#define int long long
#define sz(x) (int)(x.size())
using namespace std;

const int N = 1e4 + 5, mod = 1e9 + 7, inf = 1e9;

int n, m;
vector<pair<int,int>> g[N];

void dijkstra(int s, vector<int> & d) {

    d[s] = 0;
    using pii = pair<int, int>;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, s});
    while (!q.empty()) {
        int v = q.top().second;
        int d_v = q.top().first;
        q.pop();
        if (d_v != d[v])
            continue;

        for (auto edge : g[v]) {
            int to = edge.first;
            int len = edge.second;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                q.push({d[to], to});
            }
        }
    }
}

int32_t main(){

    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        //g[v].push_back({u, w});
    }

    std::vector<int> ans(n + 2, inf);
    dijkstra(1, ans);
    for(int i = 2; i <= n; i++)
        cout << ans[i] << ' ';
}
