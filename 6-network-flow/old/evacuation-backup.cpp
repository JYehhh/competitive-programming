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

int g2_node(int i, int j) {
    return n * n + i * n + j;
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

int shortest_path(int u, int v, int i, int j) {
    int start = g1_node(u, v);
    int end = g1_node(i, j);
    int dist[N*N];
    bool seen[N*N];

    std::fill(dist, dist + N, INT_MAX);
    std::fill(seen, seen + N, false);

    dist[start] = 0;
    std::queue<int> q;
    q.push(start);

    while(!q.empty()) {
        int cur = q.front(); q.pop();
        // std::cout << cur << endl;
        if (seen[cur]) continue;
        seen[cur] = 1;

        for (int v : edges[cur]) {
            if (!seen[v]) {
                q.push(v);
                dist[v] = dist[cur] + 1;
            }
            
        }
    }

    return dist[end];
}

std::vector<int> get_path(int end, int* prev) {
    std::vector<int> path;
    for (int at = end; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());  // Reverse to get path from start to end
    return path;
}

bool paths_converge(std::vector<int> soldier_p, std::vector<int> nuke_p) {
    if (soldier_p.size() != nuke_p.size()) return false;
    if (soldier_p.empty()) return false;

    for (int i = 0; i < soldier_p.size() - 1; ++i) {
        // std::cout << "HI!!" << std::endl;
        if (soldier_p[i] == nuke_p[i]) return true;
    }


    // if (soldier_p[0] == 8) {
    //     std::cout << "Soldier Path: ";
    //     for (int i = 0; i < soldier_p.size() - 1; ++i) {
    //         std::cout << soldier_p[i] << " ";
    //     }
    //     std::cout << std::endl;
            

    //     std::cout << "Nuke Path: ";
    //     for (int i = 0; i < soldier_p.size() - 1; ++i) {
    //         std::cout << nuke_p[i] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    return false;
}

void attempt_join(FlowNetwork &net, pii s, pii c){
    // SOLDIER TO END
    int soldier = g1_node(s.first, s.second);
    int end = g1_node(c.first, c.second);
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
        // std::cout << cur << endl;
        if (seen[cur]) continue;
        seen[cur] = 1;

        for (int v : edges[cur]) {
            if (!seen[v]) {
                q.push(v);
                prev[v] = cur;
                dist[v] = dist[cur] + 1;
            }
            
        }
    }
    
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
            if (!seen2[v]) {
                q2.push(v);
                prev2[v] = cur;
                dist2[v] = dist2[cur] + 1;
            }
            
        }
    }

    // Usage in your function:
    std::vector<int> soldier_path = get_path(end, prev);  // Path for soldier
    std::vector<int> nuke_path = get_path(end, prev2);    // Path for nuke

    int s_to_c = dist[end];
    int n_to_c = dist2[end];
    bool pc = paths_converge(soldier_path, nuke_path);

    // std::cout << "HI" << std::endl;
    // int s_to_c = shortest_path(s.first, s.second, c.first, c.second);
    // int n_to_c = shortest_path(np.first, np.second, c.first, c.second);

    // std::cout << "Distance from Nuke to " << g2_node(c.first, c.second) << ": " << n_to_c << endl;
    // std::cout << "Soldier (" << s.first << ", " << s.second << ") distance to capsule: " << s_to_c << endl;
    // std::cout << "Nuke (" << np.first << ", " << np.second << ") distance to capsule: " << n_to_c << endl;
    // std::cout << "Soldier (" << g1_node(s.first, s.second) << ") distance to capsule ("<< g1_node(c.first, c.second) << "): " << s_to_c << endl;
    // std::cout << "Nuke (" << g1_node(np.first, np.second) << ") distance to capsule ("<< g1_node(c.first, c.second) << "): " << n_to_c << endl << endl;
    if (s_to_c <= n_to_c && s_to_c <= t && s_to_c != INT_MAX && !pc) {
        // std::cout << "Edge from " << g1_node(s.first, s.second) << " to " << g2_node(c.first, c.second) << " with weight " << 1 << std::endl;
        net.add_edge(g1_node(s.first, s.second), g2_node(c.first, c.second), 1);
    }
}

int main() {
    std::cin >> n >> t;
    FlowNetwork net(2*n*n+3);
    
    // 1 to n * n is the (potential) soldier nodes
    // n * n to 2 * n * n is the (potential) capsule nodes 

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            std::cin >> sci[i][j];                                      
            if (sci[i][j] >= '1' && sci[i][j] <= '9') {                 // when we have a soldier
                // std::cout << "Source edge from " << source() << " to " << g1_node(i, j)  << " with weight " << sci[i][j] - '0' << std::endl;
                net.add_edge(source(), g1_node(i, j), sci[i][j] - '0'); // add an edge from source to soldier
                sp.push_back(make_pair(i, j));                          // add it to the list of soldiers
            } 
            if (sci[i][j] >= '0' && sci[i][j] <= '9') {                 // when we are in a walkable spot
                // std::cout << "Walkable Spot: " << i << ", " << j << std::endl;
                if (i != 0) if (sci[i-1][j] >= '0' && sci[i-1][j] <= '9') {
                    gadd_edge(g1_node(i-1, j), g1_node(i, j));
                    // std::cout << "Adding edge from " << g1_node(i-1, j) << " to " << g1_node(i, j) << std::endl;
                }
                if (j != 0) if (sci[i][j-1] >= '0' && sci[i][j-1] <= '9') {
                    gadd_edge(g1_node(i, j-1), g1_node(i, j));
                    // std::cout << "Adding edge from " << g1_node(i, j-1) << " to " << g1_node(i, j) << std::endl;
                }
                // std::cout <<endl;
            }
            if (sci[i][j] == 'Z') {
                // std::cout << "NUKE CORDS: "<< i << " " << j << std::endl;
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

    // for (int i = 0; i < N*N; ++i) {
    //     if (edges[i].size() != 0) {
    //         for (int v :edges[i]) std::cout << "Edge from " << i << " to " << v << endl;
    //     }
    // }


        /*
        1000Z
        0Y0YY
        001YY
        need to check if the path contains any of the same edges
        */
            
            
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