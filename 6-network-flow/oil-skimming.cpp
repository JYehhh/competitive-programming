#include <bits/stdc++.h>

using ll = long long;

using namespace std;
constexpr int INF = 1e9;


/*
 * dinic 1
 */

struct FlowNetwork {
    int n;
    vector<vector<ll>> adjMat, adjList;
    // level[v] stores dist from s to v
    // uptochild[v] stores first non-useless child.
    vector<int> level, uptochild;

    FlowNetwork (int _n): n(_n) {
        // adjacency matrix is zero-initialised
        adjMat.resize(n);
        for (int i = 0; i < n; i++)
            adjMat[i].resize(n);
        adjList.resize(n);
        level.resize(n);
        uptochild.resize(n);
    }

    void add_edge (int u, int v, ll c) {
        // add to any existing edge without overwriting
        adjMat[u][v] += c;        
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void flow_edge (int u, int v, ll c) {
        adjMat[u][v] -= c;
        adjMat[v][u] += c;
    }

/*
 * dinic 2
 */

    // constructs the level graph and returns whether the sink is still reachable
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            uptochild[u] = 0; // reset uptochild
            for (int v : adjList[u])
                if (adjMat[u][v] > 0) {
                    if (level[v] != -1) // already seen
                        continue;
                    level[v] = level[u] + 1;
                    q.push(v);
                }
        }
        return level[t] != -1;
    }

/*
 * dinic 3
 */

    // finds an augmenting path with up to f flow.
    ll augment(int u, int t, ll f) {
        if (u == t) return f; // base case.
        // note the reference here! we increment uptochild[u], i.e. walk through u's neighbours
        // until we find a child that we can flow through
        for (int &i = uptochild[u]; i < adjList[u].size(); i++) {
            int v = adjList[u][i];
            if (adjMat[u][v] > 0) {
                // ignore edges not in the BFS tree.
                if (level[v] != level[u] + 1) continue;
                // revised flow is constrained also by this edge
                ll rf = augment(v,t,min(f, adjMat[u][v]));
                // found a child we can flow through!
                if (rf > 0) {
                    flow_edge(u,v,rf);
                    return rf;
                }
            }
        }
        level[u] = -1;
        return 0;
    }

/*
 * dinic 4
 */

    ll dinic(int s, int t) {
        ll res = 0;
        while (bfs(s,t))
            for (ll x = augment(s,t,INF); x; x = augment(s,t,INF))
                res += x;
        return res;
    }
};

constexpr int N = 700;
constexpr int K = 200;

int n, k;

int node(int i, int j) {
    return i * n + j;
}

int source() {
    return n*n+1;
}

int sink() {
    return n*n+2;
}

signed main() {
    std::cin >> k;
    for (int i = 0; i < k; ++i) {
        std::cin >> n;
        FlowNetwork net(n*n+3);
        // for each case
        
        int res;
        char grid[n][n];

        for (int j = 0; j < n; ++j)
            for (int l = 0; l < n; ++l) 
                std::cin >> grid[j][l];

        // now we have a grid with all of the characters
        for (int j = 0; j < n; ++j)
            for (int l = 0; l < n; ++l) {
                bool top_edge = j == 0;
                bool bot_edge = j == n - 1;
                bool left_edge = l == 0;
                bool right_edge = l == n - 1;
                if ((j + l) % 2 == 0) { // if we're at a starting point
                    net.add_edge(source(), node(j, l), 1);
                    if (grid[j][l] == '#') {
                        if (!top_edge) if (grid[j-1][l] == '#') net.add_edge(node(j, l), node(j-1, l), 1); // add in the scoop if the next is a #
                        if (!bot_edge) if (grid[j+1][l] == '#') net.add_edge(node(j, l), node(j+1, l), 1); // add in the scoop if the next is a #
                        if (!left_edge) if (grid[j][l-1] == '#') net.add_edge(node(j, l), node(j, l-1), 1); // add in the scoop if the next is a #
                        if (!right_edge) if (grid[j][l+1] == '#') net.add_edge(node(j, l), node(j, l+1), 1); // add in the scoop if the next is a #
                    }
                } else net.add_edge(node(j, l), sink(), 1);
            }

        std::cout << "Case " << i + 1 << ": " << net.dinic(source(), sink()) << std::endl;
    }
    
    return 0;
}