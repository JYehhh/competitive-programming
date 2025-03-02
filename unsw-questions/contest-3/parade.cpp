#include <bits/stdc++.h>

using ll = long long;
typedef std::pair<int,int> pii;

constexpr int N = 20000;
const int K = 10;

struct edge {
    ll v;
    ll d;
    int cb;
    
    edge(int _v, int _d, int _cb) : v(_v), d(_d), cb(_cb) {}

    bool operator>(const edge &other) const {
        // if (cb == other.cb) {
        //     return cb > other.cb; 
        // }
        return d > other.d; // For min-heap, prioritise smaller distance
    }
};

std::vector<int> elev(N);
std::vector<edge> edges[N];
ll dist[N][1 << K];
bool seen[N][1 << K];
std::priority_queue<edge, std::vector<edge>, std::greater<edge>> pq;

void dijkstra (int s) {
    memset(seen, 0, sizeof(seen));
    memset(dist, -1, sizeof(dist)); 
    dist[s][0] = 0; // Starting node with zero exhaustion
    pq.push(edge(s, 0, 0)); // distance to s itself is zero, 0 bitset
    while (!pq.empty()) {
        // choose (d, v) so that d is minimal
        // i.e. the closest unvisited vertex
        edge cur = pq.top();
        pq.pop();
        int v = cur.v, d = cur.d, ccb = cur.cb;
        if (seen[v][ccb]) continue; // Maybe check WHICH colours rather than the number of cols
        
        dist[v][ccb] = d;
        seen[v][ccb] = true;

        // relax all edges from v
        for (edge nxt : edges[v]) {
            int u = nxt.v, w = nxt.d, c = nxt.cb;
            if (!seen[u][c | ccb] || d + w < dist[u][c | ccb])
                pq.push(edge(u, d + w, c | ccb));
        }
    }
}
int n, m, k;

signed main() {
    std::cin >> n >> m >> k;

    for (int i = 1; i <= n; ++i) {
        std::cin >> elev[i];
    }

    for (int i = 0; i < m; ++i) {
        int u, v, c;
        std::cin >> u >> v >> c;
        edges[u].emplace_back(v, std::max(elev[v]-elev[u], 0), 1 << (c - 1));
        edges[v].emplace_back(u, std::max(elev[u]-elev[v], 0), 1 << (c - 1));
    }

    dijkstra(1);

    std::cout << dist[n][(1 << k) - 1];
}