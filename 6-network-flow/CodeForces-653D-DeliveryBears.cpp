#include <bits/stdc++.h>

using ll = long long;
using ld = long double;

using namespace std;
constexpr int INF = 1e9;
typedef std::pair<int,int> pii;


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

constexpr int N = 100;

int n, m, x;
std::vector<pii> edges[N];
constexpr int MAX_WEIGHT = 1e6;
constexpr ld EPSILON = 1e-12;

signed main() {
    std::cin >> n >> m >> x;

    // setup the original
    FlowNetwork og(n+1); // this flow network is 1-indexed

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        edges[u].emplace_back(v, w);
        // og.add_edge(u, v, w*1e6);
    }

    // if you can flow 

    // binary search the max weight such that all bears can flow through.
    ld lo = 0;
    ld hi = MAX_WEIGHT;
    ld weight = -1;

    while (hi - lo > EPSILON) { // HI - LO greater than some epsilon
        ld mid = (lo + hi) / 2;
        FlowNetwork cur(n+1);

        // reconstruct graph with new edge weights...

        for (int i = 1; i <= n; ++i) 
            for (pii e : edges[i]) {
                // std::cout << "Edge changed to: " << std::floor(e.second/mid);
                cur.add_edge(i, e.first, static_cast<ll>(e.second/mid));
            }
        bool can_send_all = cur.dinic(1, n) >= x;
        
        // now, we're trying to check if the flow is greater than 

        // flow the weight across, if total flow  = number of bears * weight
        if (can_send_all) { // just never can do
            weight = mid;
            lo = mid;
        } else {
            hi = mid;
        }
    }

    std::cout << std::fixed << std::setprecision(8) <<  weight * ll(x);

    // when you test a weight, recreate the graph, do each node, divided by the weight of the bear.
    // see if max flow = number of bears - if not, move it...
    
    return 0;
}