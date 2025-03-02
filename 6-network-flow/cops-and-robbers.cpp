#include <bits/stdc++.h>

using ll = long long;

using namespace std;
constexpr int INF = 1e9;
typedef std::pair<int,int> pii;

constexpr int N = 50;

int n, m, c;
char grid[N][N];
int visited[N][N];
// int has_ie[N][N];
ll cost[N];

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


int in(int r, int c) {
    return r * n + c;
}

int out(int r, int c) {
    return (m * n) + r * n + c;
}

int source() {
    return 2*n*m+1;
}

int sink() {
    return 2*n*m+2;
}

void populate_net(FlowNetwork &net, int r, int c) {
    // add edge to all neighbours;
    // check if up down left right are edges:
    if (visited[r][c]) return;
    visited[r][c] = 1;

    bool up_edge = (r == 0);
    bool down_edge = (r == m - 1);
    bool left_edge = (c == 0);
    bool right_edge = (c == n - 1);

    // if we're at an edge, connect to the sink with infinity...
    if (up_edge || down_edge || left_edge || right_edge) {
        net.add_edge(out(r, c), sink(), INF);
        return;
    }

    ll cost_up = grid[r-1][c] == '.' ? INF : cost[grid[r-1][c] - 'a'];
    ll cost_down = grid[r+1][c] == '.' ? INF : cost[grid[r+1][c] - 'a'];
    ll cost_left = grid[r][c-1] == '.' ? INF : cost[grid[r][c-1] - 'a'];
    ll cost_right = grid[r][c+1] == '.' ? INF : cost[grid[r][c+1] - 'a'];


    // if (!has_ie[r-1][c]) net.add_edge(r*n + c, (r-1)*n + c, cost_up); has_ie[r-1][c] = 1;
    // if (!has_ie[r+1][c]) net.add_edge(r*n + c, (r+1)*n + c, cost_down); has_ie[r+1][c] = 1;
    // if (!has_ie[r][c-1]) net.add_edge(r*n + c, r*n + c-1, cost_left); has_ie[r][c-1] = 1;
    // if (!has_ie[r][c+1]) net.add_edge(r*n + c, r*n + c+1, cost_right); has_ie[r][c+1] = 1;

    net.add_edge(out(r, c), in(r-1, c), cost_up);
    net.add_edge(out(r, c), in(r+1, c), cost_down);
    net.add_edge(out(r, c), in(r, c-1), cost_left);
    net.add_edge(out(r, c), in(r, c+1), cost_right);

    populate_net(net, r-1, c);
    populate_net(net, r+1, c);
    populate_net(net, r, c-1);
    populate_net(net, r, c+1);
}



// n and m are dimensions of grid.
// c is the number of terrains

signed main() {
    // start from 
    std::cin >> n >> m >> c;
    pii bp;
    for (int i = 0; i < m; ++i) 
        for (int j = 0; j < n; ++j) {
            std::cin >> grid[i][j];
            if (grid[i][j] == 'B') bp = std::make_pair(i, j); // store the position of the bank
                
        }

    for (int i = 0; i < c; ++i) std::cin >> cost[i];

    // the graph we're going to create is:
    FlowNetwork net(2*n*m+3);
    for (int i = 0; i < m; ++i) 
        for (int j = 0; j < n; ++j)
            net.add_edge(in(i, j), out(i, j), grid[i][j] == '.' ? INF : cost[grid[i][j] - 'a']);

    // std::cout << bp.first << " " << bp.second << endl;

    // connect bank to source with infinity...
    net.add_edge(source(), in(bp.first, bp.second), INF);
    net.add_edge(in(bp.first, bp.second), out(bp.first, bp.second), INF);
    populate_net(net, bp.first, bp.second);

    ll min_cut = net.dinic(source(), sink());
    if (min_cut == INF) cout << "-1\n";
    else cout << min_cut << "\n";



}