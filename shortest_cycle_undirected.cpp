// Shortest cycle detection of undirected simple graphs based on 01-BFS
// Assumption: only two types of edges are permitted: weight = 0 or W ( > 0)
// Complexity: O(E)
struct ShortestCycle01
{
    int V, E;
    int INVALID = -1;
    std::vector<std::vector<std::pair<int, int>>> to;  // (nxt, weight)
    ShortestCycle01() = default;
    ShortestCycle01(int V) : V(V), E(0), to(V) {}
    void add_edge(int s, int t, int len) {
        assert(0 <= s and s < V);
        assert(0 <= t and t < V);
        to[s].emplace_back(t, len);
        to[t].emplace_back(s, len);
        E++;
    }
 
    std::vector<int> dist;
    std::vector<int> prev;
    int Solve(int v) {
        assert(0 <= v and v < V);
        dist.assign(V, std::numeric_limits<int>::max());
        dist[v] = 0;
        prev.assign(V, -1);
        std::deque<std::pair<int, int>> bfsq;
        std::vector<std::pair<std::pair<int, int>, int>> add_edge;
        bfsq.emplace_back(v, -1);
        while (!bfsq.empty()) {
            int now = bfsq.front().first, prv = bfsq.front().second;
            bfsq.pop_front();
            for (auto nxt : to[now]) if (nxt.first != prv) {
                if (dist[nxt.first] == std::numeric_limits<int>::max()) {
                    dist[nxt.first] = dist[now] + nxt.second;
                    prev[nxt.first] = now;
                    if (nxt.second) bfsq.emplace_back(nxt.first, now);
                    else bfsq.emplace_front(nxt.first, now);
                }
                else add_edge.emplace_back(std::make_pair(now, nxt.first), nxt.second);
            }
        }
        int minimum_cycle = std::numeric_limits<int>::max();
        for (auto edge : add_edge) {
            int a = edge.first.first, b = edge.first.second;
            int L = dist[a] + dist[b] + edge.second;
            if (L < minimum_cycle) minimum_cycle = L;
        }
        return minimum_cycle;
    }
};
