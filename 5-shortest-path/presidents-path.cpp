#include <bits/stdc++.h>

using ll = long long;
typedef std::pair<int,int> pii;

using namespace std;

constexpr int N = 1000;
constexpr int INF = 1e9;


// struct edge {
//     ll u;
//     ll v;
//     ll w;
//     edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
// };

int n, m;
int dist[N][N];
// std::vector<edge> edges;
int edges[N][N];
int penul_spe[N][N];
int roads[N][N];


signed main() {
    std::cin >> n >> m;
    // read in edges
    std::fill(&edges[0][0], &edges[0][0] + N * N, INF);
    for (int i = 0; i < m; ++i) {
        int u, v, w; std::cin >> u >> v >> w;
        edges[u][v] = w;
        edges[v][u] = w;
    }

    // the distance between everything is infinity
    for (int u = 1; u <= n; ++u)
        for (int v = 1; v <= n; ++v)
            dist[u][v] = edges[u][v] == INF ? INF : edges[u][v];

    // // update the distances for every directed edge
    // for (edge e : edges) 
    //     dist[e.u][e.v] = e.w;

    // every vertex can reach itself
    for (int u = 1; u <= n; ++u)
        dist[u][u] = 0;
    
    // when using itself as an intermediary, it should cost nothing

    // for (int u = 1; u <= n; u++) {
    //     for (int v = 1; v <= n; v++) {
    //         std::cout << dist[u][v] << " ";
    //     }
    //     std::cout << "\n";
    // }


    for (int i = 1; i <= n; i++) {
        for (int u = 1; u <= n; u++) {
            for (int v = 1; v <= n; v++) {
                // dist[u][v] is the length of the shortest path from u to v using only 0 to i as intermediate vertices
                // now that we're allowed to also use i, the only new path that could be shorter is u -> i -> v
                dist[u][v] = min(dist[u][v], dist[u][i] + dist[i][v]);
            }
        }
    }

    // for (int u = 1; u <= n; u++) {
    //     for (int v = 1; v <= n; v++) {
    //         std::cout << dist[u][v] << " ";
    //     }
    //     std::cout << "\n";
    // }
    // COMPUTE 1: calculate the number of penultimate edges on the shortest paths from every u to v
    for (int i = 1; i <= n; i++) {
        for (int u = 1; u <= n; u++) {
            for (int v = 1; v <= n; v++) {
                if (dist[u][v] == INF) continue;
                // if the intermediary is on a shortest path into v
                if (dist[u][v] == dist[u][i] + edges[i][v]) {
                    penul_spe[u][v] += 1; 
                }
            }
        }
    }

    // for (int u = 1; u <= n; u++) {
    //     for (int v = 1; v <= n; v++) {
    //         std::cout << penul_spe[u][v] << " ";
    //     }
    //     std::cout << "\n";
    // }

    // COMPUTE 2: 
    for (int u = 1; u <= n; u++) {
        for (int v = 1; v <= n; v++) {
            for (int i = 1; i <= n; i++) {
                // if the intermediary is on a shortest path into v
                // add the number of roads going into just that intermediary.
                if (dist[u][v] == dist[u][i] + dist[i][v]) {
                    roads[u][v] += penul_spe[u][i];
                }
            }
        }
    }
    

    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            std::cout << roads[i][j] << " ";
    
    return 0;
}