#include <bits/stdc++.h>

using ll = long long;

using namespace std;

struct edge {
    ll u;
    ll v;
    ll d;
    bool is_train;
    
    edge(int _u, int _v, int _d, bool _is_train) : u(_u), v(_v), d(_d), is_train(_is_train) {}

    bool operator<(const edge &other) const {
        if (d == other.d) {
            return is_train > other.is_train; // Prefer road over train for same distance
        }
        return d > other.d; // For min-heap, prioritise smaller distance
    }
};

const int N = 100100;
vector<edge> roads[N];
vector<edge> trains[N];

ll dist[N];
ll previous[N];
bool seen[N];
priority_queue<edge, vector<edge>> pq;

ll n, m, k;


void dijkstra (int s) {
    fill(seen,seen+N,false);
    pq.push(edge(0, s, 0, false)); // distance to s itself is zero, 0 bitset
    while (!pq.empty()) {
        edge cur = pq.top(); pq.pop();
        ll p = cur.u, v = cur.v, d = cur.d, is_train = cur.is_train;
        // cout << "Processing " << p << " to " << v << " with distance " << d << ". Is Train: " << is_train << endl;
        
        if (seen[v]) continue; 

        dist[v] = d;
        seen[v] = true;
        // std::cout << "HIIIII P IS: " << p << std::endl;
        previous[v] = is_train ? -1 : p;

        for (edge nxt : roads[v]) {
            ll u = nxt.v, weight = nxt.d;
            // std::cout << "Adding Road from " << v << " to " << u << " with weight " << d + weight << endl;
            if (!seen[u]) pq.push(edge(v, u, d + weight, false)); 
        }

        for (edge nxt : trains[v]) {
            ll u = nxt.v, weight = nxt.d;
            // std::cout << "Adding Train from " << v << " to " << u << " with weight " << d + weight << endl;
            if (!seen[u]) pq.push(edge(v, u, d + weight, true)); 
        }
    }
}

signed main () {
    cin >> n >> m >> k;

    for (int i = 0; i < m; ++i) {
        ll u, v, x;
        cin >> u >> v >> x;
        roads[u].push_back(edge(u, v, x, false));
        roads[v].push_back(edge(v, u, x, false));
    }

    for (int i = 0; i < k; ++i) {
        ll s, y;
        cin >> s >> y;
        trains[1].push_back(edge(1, s, y, true));
        trains[s].push_back(edge(s, 1, y, true));
    }
    
    dijkstra(1);

    // iterate through the 
    int count_prev = 0;
    
    for (int i = 1; i <= n; ++i) {
        if (previous[i] == -1) count_prev++;
        // std::cout << previous[i] << " ";
    }

    cout << k - count_prev << endl;
    // cout << k - __builtin_popcount(final_bitset) << endl;

    return 0;
}