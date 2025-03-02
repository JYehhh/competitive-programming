#include <bits/stdc++.h>

// TYPEDEFS
using ll = long long;
using ld = long double;
typedef std::pair<int,int> pii;

using namespace std;

// CONSTANTS
constexpr int INF = 1e9;
constexpr int N = 20;
constexpr int MAX_WEIGHT = 1e6;
constexpr ld EPSILON = 1e-12;

// VARIABLES
int n, t;
char sci[N][N];
char cap[N][N];
std::vector<int> edges[N*N];
std::vector<pii> sp;
std::vector<pii> cp;
pii np;

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

int g1_node(int i, int j) {
    return i * n + j;
}

pii reverse_g1_node(int node) {
    int i = node / n;
    int j = node % n;
    return {i, j};
}

int g2_node(int i, int j) {
    return n * n + i * n + j;
}

pii reverse_g2_node(int node) {
    int adjusted_node = node - n * n;
    int i = adjusted_node / n;
    int j = adjusted_node % n;
    return {i, j};
}

int source() {
    return 2*n*n+1;
}

int sink() {
    return 2*n*n+2;
}

void gadd_edge(int u, int v, bool nuke = false) {
    edges[u].push_back(v);
    if (!nuke) edges[v].push_back(u);
}
/*
void attempt_join(FlowNetwork &net, pii s, pii c){
    int end = g1_node(c.first, c.second);
    // NUKE TO END
    int nuke = g1_node(np.first, np.second);
    int dist2[N*N];
    bool seen2[N*N];
    int prev2[N*N];

    std::fill(dist2, dist2 + N*N, INT_MAX);
    std::fill(seen2, seen2 + N*N, false);
    std::fill(prev2, prev2 + N*N, -1);

    dist2[nuke] = 0;
    std::queue<int> q2;
    q2.push(nuke);

    while(!q2.empty()) {
        int cur = q2.front(); q2.pop();
        // std::cout << cur << endl;
        if (seen2[cur]) continue;
        seen2[cur] = 1;

        for (int v : edges[cur]) {
            if (!seen2[v] && dist2[cur] + 1 < dist2[v]) {
                q2.push(v);
                prev2[v] = cur;
                dist2[v] = dist2[cur] + 1;
            }
        }
    }

    // SOLDIER TO END
    bool path_found = false;

    int soldier = g1_node(s.first, s.second);
    int dist[N*N];
    bool seen[N*N];
    int prev[N*N];

    std::fill(dist, dist + N*N, INT_MAX);
    std::fill(seen, seen + N*N, false);
    std::fill(prev, prev + N*N, -1);

    dist[soldier] = 0;
    std::queue<int> q;
    q.push(soldier);

    while(!q.empty()) {
        int cur = q.front(); q.pop();
        // std::cout << cur << std::endl;
        // std::cout << cur << endl;
        if (seen[cur]) continue;
        seen[cur] = 1;

        for (int v : edges[cur]) {
            std::cout << v << std::endl;
            if (v == end) {
                prev[v] = cur;
                dist[v] = dist[cur] + 1;
                path_found = true;  // End search when capsule is reached
                continue;
            }
            if (!seen[v] && dist[cur] + 1 < dist[v] && dist2[v] != dist[cur] + 1) {
                q.push(v);
                prev[v] = cur;
                dist[v] = dist[cur] + 1;
            }
            
        }
    }
    // now just get the soldier path, and check if it's empty:
    std::vector<int> soldier_path = get_path(end, prev);  // Path for soldier


    // // Usage in your function:
    // std::vector<int> soldier_path = get_path(end, prev);  // Path for soldier
    // std::vector<int> nuke_path = get_path(end, prev2);    // Path for nuke

    int s_to_c = dist[end];
    int n_to_c = dist2[end];
    // bool pc = paths_converge(soldier_path, nuke_path);
    // bool pc = false;
    
    // for (int i = 0; i < soldier_path.size() - 1; ++i)
    //     if (dist[soldier_path[i]] == dist2[soldier_path[i]]) pc = true; 

    if (s_to_c <= n_to_c && s_to_c <= t && s_to_c != INT_MAX && !soldier_path.empty()) {
        // std::cout << "Edge from (" << s.first << ", " << s.second << ") to " << c.first << ", " << c.second << " with weight " << sci[s.first][s.second] - '0' << std::endl;
        net.add_edge(g1_node(s.first, s.second), g2_node(c.first, c.second), sci[s.first][s.second] - '0');
    }
        
}

*/

void attempt_join(FlowNetwork &net, pii s, pii c){
    int nuke = g1_node(np.first, np.second);
    int end = g1_node(c.first, c.second);
    int soldier = g1_node(s.first, s.second);

    int nl[N*N];
    bool nv[N*N];
    int cl = 0;
    std::queue<int> qn;
    std::fill(nl, nl + N*N, INT_MAX);
    std::fill(nv, nv + N*N, false);

    qn.push(nuke);
    while (!qn.empty()) {
        int s=qn.size();
        for (int i = 0; i < s; ++i) {
            int cur = qn.front(); qn.pop();

            if (nv[cur]) continue;
            nv[cur] = true;

            for (int u : edges[cur]) if (!nv[u]) qn.push(u);

            nl[cur] = cl;
            // std::cout << "updating nl" << endl;
        }
        cl++;
    }

    // bfs through soldiers
    bool p = false;
    int csl = 0;
    bool sv[N*N];
    std::queue<int> qs;

    std::fill(sv, sv + N*N, false);

    qs.push(soldier);
    while (!qs.empty()) {
        int s=qs.size();
        for (int i = 0; i < s; ++i) {
            int cur = qs.front(); qs.pop();
            // std::cout << "Position: " << cur << " with distance: " << csl << endl;
            // std::cout << "Cur Pos: " << cur << endl;
            
            if (cur == end && csl <= nl[cur]) {
                // std::cout << "Found Path!" << endl;
                p = true;
                break;
            }

            if (csl >= nl[cur]) continue;
            
            if (sv[cur]) continue;
            sv[cur] = true;

            for (int u : edges[cur]) if (!sv[u])
                qs.push(u);
        }

        if (p == true) break;
        csl++;
    }
    
    if (p && csl <= t) net.add_edge(g1_node(s.first, s.second), g2_node(c.first, c.second), sci[s.first][s.second] - '0');
}

int main() {
    std::cin >> n >> t;
    FlowNetwork net(2*n*n+3);
    
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            std::cin >> sci[i][j];                                      
            if (sci[i][j] >= '1' && sci[i][j] <= '9') {                 // when we have a soldier
                // std::cout << "Source edge from " << source() << " to " << g1_node(i, j)  << " with weight " << sci[i][j] - '0' << std::endl;
                net.add_edge(source(), g1_node(i, j), sci[i][j] - '0'); // add an edge from source to soldier
                sp.push_back(make_pair(i, j));                          // add it to the list of soldiers
            } 
            if (sci[i][j] >= '0' && sci[i][j] <= '9') {                 // when we are in a walkable spot
                if (i != 0) if (sci[i-1][j] >= '0' && sci[i-1][j] <= '9') 
                    gadd_edge(g1_node(i-1, j), g1_node(i, j));
                if (j != 0) if (sci[i][j-1] >= '0' && sci[i][j-1] <= '9') 
                    gadd_edge(g1_node(i, j-1), g1_node(i, j));
            }
            if (sci[i][j] == 'Z') {
                np = make_pair(i, j);                 // if we're at the reactor        
                if (i != 0) gadd_edge(g1_node(i, j), g1_node(i-1, j), true);
                if (j != 0) gadd_edge(g1_node(i, j), g1_node(i, j-1), true);
                if (i != n-1) gadd_edge(g1_node(i, j), g1_node(i+1, j), true);
                if (j != n-1) gadd_edge(g1_node(i, j), g1_node(i, j+1), true);
            }
        } 

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            std::cin >> cap[i][j];
            if (cap[i][j] >= '1' && cap[i][j] <= '9') {                 // if we're at a capsule 
                // std::cout << "Sink edge from " << g2_node(i, j) << " to " << sink()<< " with weight " << cap[i][j] - '0' << std::endl;
                net.add_edge(g2_node(i, j), sink(), cap[i][j] - '0');   // add an edge from capsule from capsule to sink
                cp.push_back(make_pair(i, j));
            }
        } 
    for (pii s : sp) for (pii c : cp) attempt_join(net, s, c); // NOT SURE ABOUT THIS, THERE IS A WEIRD CASE (coming from two directions...)

    std::cout << net.dinic(source(), sink()) << "\n";


    /*
    METHODOLOGY
    */

    // now we have the source connected to the soldiers, and the capsules connected to the sink.
    // we need to find out how to connect the soldiers to the capsules
    
    // calculate the shortest path from every soldier to every capsule.
    // calculate the shortest path from the nuke to every capsule.

    // iterate through the soldiers, for each:
        // iterate through the capsules:
            // if the distance to that capsule is greater than t, or greater than the nuke to the capsule
            // no edge,
            // otherwise, edge

    // flow the graph.


    /*
    * Bipartite Matching:
        * SOURCE TO LHS: How many soldiers in that cell
        * LHS: Tiles with Soldiers
        * LHS TO RHS: If shortest distance from that soldier to the capsule is less than shortest distance from nuke to that capsule.
        * RHS: Tiles with Capsules
        * RHS TO SINK: With number of capsules in that square

    * Calculate the shortest distance from all nodes with soldiers in it to every capsule
    */
}