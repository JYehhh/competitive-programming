#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct edge {
    int u;
    int v;
    ll d;
    
    edge(int _u, int _v, int _d) : u(_u), v(_v), d(_d) {}

    bool operator>(const edge &other) const {
        // if (cb == other.cb) {
        //     return cb > other.cb; 
        // }
        return d > other.d; // For min-heap, prioritise smaller distance
    }
};


typedef pair<int,int> pii;
const int N = 10000;
int n, m;

vector<edge> edges[N]; // pairs of (weight, v)
bool in_tree[N];
// use greater as the comparator instead of the default less so the priority queue is a min-heap instead of a max-heap
// the vector<int> parameter is the container the queue is stored in, an implementation detail you will not need to change
priority_queue<edge, vector<edge>, greater<edge>> pq;
vector<edge> mst_edges; 

int mst() {
    int total_weight = 0;
    in_tree[1] = true; // (2)
    for (const auto &e : edges[1]) {
        pq.push(e);
    }
    // for (auto edge : edges[1]) pq.emplace(edge.first, edge.second);
    while (!pq.empty()) { // (3)
        auto e = pq.top(); pq.pop();
        // if this edge goes to somewhere already in the tree, it's useless (we've already done something better)
        if (in_tree[e.v]) continue;
        in_tree[e.v] = true;
        total_weight += e.d;

        mst_edges.push_back(e);

        for (auto next_edge : edges[e.v]) {
            pq.push(next_edge);
        }
    }
  return total_weight;
}

signed main() {
    std::cin >> n >> m;

    pii hs;
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        std::cin >> u >> v >> w;

        if (i == 0) hs = make_pair(u, v);

        edges[u].emplace_back(u, v, w);
        edges[v].emplace_back(v, u, w);
    }
    
    bool hs_in_mst = false;
    for (const auto e : mst_edges) {
        if ((e.u == hs.first && e.v == hs.second) || (e.u == hs.second && e.v == hs.first)) {
            hs_in_mst = true;
            break;
        }
    }

    if (hs_in_mst) std::cout << "0";
    else std::cout << "100";


}