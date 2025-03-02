#include <bits/stdc++.h>

using ll = long long;

int n;

struct edge {
  ll u, v, w; // u -> v of weight w
  edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
};

constexpr int INF = 1e9;
constexpr int N = 1000;

ll dist[N][N];
std::vector<edge> edges;
std::vector<ll> deletions(N);
std::vector<ll> sums;

signed main () {
    // should be easy!
    // run floyd warshall algorithm to find all pairs shortest path
    
    // we don't want to run it every deletion, but if we run it in a way where the 
    // last few vertices are the ones that are deleted...
    // i.e. the last vertex is the the first deleted,
    // then we can just sum the last few DP runs

    // ACTUAL IMPLEMENTATION
    // run floyd warshall algorithm, when going through first relaxation, skip nodes that are deleted
    // run second relaxation over nodes that are deleted - store sums.

    std::cin >> n;
    deletions.resize(n);

    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            int weight; std::cin >> weight;
            edges.push_back(edge(u, v, weight));
            dist[u][v] = INF;
        }
    }

    for (int i = 0; i < n; ++i) std::cin >> deletions[i]; // store all the deletions
    // THESE ARE 1 INDEXED
    
    std::reverse(deletions.begin(), deletions.end());

    for (edge e : edges) dist[e.u][e.v] = e.w;

    for (int u = 0; u < n; ++u) dist[u][u] = 0;

    // we wanna start with 0 edges 
    std::unordered_set<int> in;
    for (int i = 0; i < n; ++i) {
        int curr = deletions[i] - 1; // adding in the last one deleted
        ll curr_sum = 0;
        // this is the index we're adding in

        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                int city_u = deletions[u] - 1;
                int city_v = deletions[v] - 1;

                dist[city_u][city_v] = std::min(dist[city_u][city_v], dist[city_u][curr] + dist[curr][city_v]);

                if (u <= i && v <= i) curr_sum += dist[city_u][city_v];
            }
        }

        sums.push_back(curr_sum);
    }

    for (auto it = sums.rbegin(); it != sums.rend(); ++it) std::cout << *it << " ";
            

    return 0;
}