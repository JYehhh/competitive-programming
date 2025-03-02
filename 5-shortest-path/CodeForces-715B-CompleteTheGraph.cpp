#include <bits/stdc++.h>

using ll = long long;
using namespace std;

ll n, m, L, s, t;


typedef pair<ll, ll> edge; // (distance, vertex)
const int N = 100100;
vector<edge> edges[N];
priority_queue<edge, vector<edge>, greater<edge>> pq1;
priority_queue<edge, vector<edge>, greater<edge>> pq2;

signed main() {
    std::cin >> n >> m >> L >> s >> t;
    std::vector<edge> res[N];
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        if (w != 0) res[u].emplace_back(w, v);
        edges[u].emplace_back(w, v);
        edges[v].emplace_back(w, u);
    }

    ll dfs1[N];
    bool seen1[N];

    fill(dfs1,dfs1+N,INT_MAX);
    fill(seen1,seen1+N,false);

    // DJIKSTRA FROM S, ignoring edges that have 0 weight.
    pq1.push(edge(0, s));
    while (!pq1.empty()) {
        edge cur = pq1.top(); pq1.pop();
        ll v = cur.second, d = cur.first;
        if (seen1[v]) continue;
        
        dfs1[v] = d;
        seen1[v] = true;

        for (edge nxt : edges[v]) {
            int u = nxt.second, weight = nxt.first;
            if (weight == 0) continue;
            if (!seen1[u])
                pq1.push(edge(d + weight, u));
        }
    }

    if (dfs1[t] < L) {
        std::cout << "No\n";
        return 0;
    }

    // DJIKSTRA FROM T, fill in edges that have 0 weight.
    ll dfs2[N];
    bool seen2[N];
    

    fill(dfs2,dfs2+N,INT_MAX);
    fill(seen2,seen2+N,false);
    
    pq2.push(edge(0, t));
    while (!pq2.empty()) {
        edge cur = pq2.top(); pq2.pop();
        ll v = cur.second, d = cur.first;
        if (seen2[v]) continue;
        
        dfs2[v] = d;
        seen2[v] = true;

        for (edge nxt : edges[v]) {
            ll u = nxt.second, weight = nxt.first;
            if (!seen2[u]) {
                if (weight != 0) pq2.push(edge(d + weight, u));
                else {
                    ll new_weight = std::max(ll(1), L - dfs1[u] - d);
                    pq2.push(edge(d + new_weight, u));
                    res[u].emplace_back(new_weight, v);
                }
            }
        }
    }

    if (dfs2[s] == L) {
        std::cout << "Yes\n";
        for (int i = 0; i < n; ++i) 
            for (edge e : res[i])
                std::cout << i << " " << e.second << " " << e.first << endl;

    }
    else std::cout << "No\n";

    return 0;
}

