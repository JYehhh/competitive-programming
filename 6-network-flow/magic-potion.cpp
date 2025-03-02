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


int n, m, k;

signed main() {
    cin >> n >> m >> k;
    FlowNetwork net(n*2+m+3);
    int potion = n*2+m, s = n*2+m+1, t = n*2+m+2;

    // connect source to soldiers
    for (int i = 0; i < n; ++i) {
        net.add_edge(s, i, 1);
    } // populate the 0th, all the way to the kth

    net.add_edge(s, potion, k);

    // connect potion to second set of soldiers 
    for (int i = 0; i < n; ++i) {
        net.add_edge(potion, n+i, 1);
    }

    // connect monsters to sink
    for (int i = 0; i < m; ++i) { // the first monster is stored at n*(k+1);
        net.add_edge(n*2+i, t, 1); // add edge from monster number to t.
    }

    // connect soldiers to monsters
    for (int i = 0; i < n; ++i) { int nk; // first soldier is at 0
        // for every soldier,
        // get number of monsters that they can kill
        cin >> nk;
        for (int j = 0; j < nk; ++j) { int mn;
            cin >> mn;
            mn = mn - 1;
            net.add_edge(i, n*2+mn, 1);
            net.add_edge(n+i, n*2+mn, 1);
        }
    }
    cout << net.dinic(s,t) << '\n';
    return 0;
}