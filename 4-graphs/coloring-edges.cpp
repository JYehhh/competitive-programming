#include <bits/stdc++.h>

using ll = long long;
typedef std::pair<int,int> pii;

constexpr int N = 10000;

int n, m;

std::vector<int> seen(N);
std::vector<int> active(N);
std::vector<int> colour(N);
std::vector<pii> edges[N]; // storing the edges
bool two_colours = false;

void colour_edges(int u) {
    if (seen[u]) return; // everytime we see a node, we colour all it's edges
    seen[u] = true;
    active[u] = true;
    for (pii e : edges[u]) { // go through all outgoing edges
        int v = e.second;
        // if the destination we're going to is active, need to colour this edge 2
        if (active[v]) {
            colour[e.first] = 2;
            two_colours = true;
        }
        else colour[e.first] = 1;
        colour_edges(v); // colour all the edges of it's neighbour
    }
    active[u] = false;
}

signed main() {
    std::cin >> n >> m;

    // read in edges
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        edges[u].emplace_back(i,v);
    }

    // iterate through the vertices, using all of them as starting points
    // if it's seen, skip it.
    for (int i = 1; i <= n; ++i) {
        // if the starting point has been seen, we've already coloured in all
        // it's outgoing edges in the dfs algorithm
        if (seen[i]) continue;
        colour_edges(i);
    }

    if (two_colours) std::cout << "2\n";
    else std::cout << "1\n";

    for (int i = 0; i < m; ++i) {
        std::cout << colour[i] << " ";
    }
    // run dfs cycle detection
    // colour all edges that create cycles the other colour (back edges that go to active)
    // cross edges that go to inactive edges should be coloured the og colour.

    return 0;
}