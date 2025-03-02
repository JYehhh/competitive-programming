#include <bits/stdc++.h>

using ll = long long;

typedef std::pair<int,int> pii;

constexpr int N = 1000000;
int n;
int m;

std::vector<int> edges[N]; // storing the edges 
int T = 0; // to count preorder
int preorder[N]; // initialised to -1 = preorder of every element
int reach[N]; // reach[u] is the smallest preorder index
              // of any vertex reachable from u
std::vector<pii> bridges;
std::vector<pii> directed_edges;


void dfs(int u, int from = -1) {
    if (from != -1) directed_edges.emplace_back(from, u);
    preorder[u] = T++;
    reach[u] = preorder[u];

    for (int v : edges[u]) if (v != from) {
        if (preorder[v] == -1) { // if it hasn't been visited
            dfs(v, u);
            // if v can't reach anything earlier than itself
            // then u--v is a bridge
            if (reach[v] == preorder[v]) bridges.emplace_back(u,v);
        }
        if (preorder[v] < preorder[u]) directed_edges.emplace_back(u, v); // Back edge (upward)
        // anything reachable from v is reachable from u
        reach[u] = std::min(reach[u], reach[v]);
    }
}


signed main() {
    std::cin >> n;
    std::cin >> m;
    for (int i = 0; i <= n; ++i) preorder[i] = -1;

    // read in the edges into a vector
    for (int i = 0; i < m; ++i) {
        int src, dst;
        std::cin >> src >> dst;
        edges[src].push_back(dst);
        edges[dst].push_back(src);
    }

    dfs(1); // edges are 1-indexed

    // now, bridges[] will contain all of the bridges
    if (!bridges.empty()) {
        std::cout << 0;
    } else {
        for (pii i : directed_edges) std::cout << i.first << " " << i.second << std::endl;
    }

    return 0;
}