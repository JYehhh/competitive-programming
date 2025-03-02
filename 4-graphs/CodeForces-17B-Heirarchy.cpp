#include <bits/stdc++.h>

using ll = long long;
typedef std::pair<int,int> pii;

constexpr int INF = 1e9;
constexpr int N = 1100;
constexpr int M = 10100;

int n;
int m;
int visited[N];
// adjacency list
std::vector<pii> e[N];
int employee[N];
std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;


signed main() {
    std::cin >> n;
    // int ri = 0;
    // employee[0] = -1;

    for (int i = 1; i <= n; ++i) {
        std::cin >> employee[i];
        // if (employee[i] > employee[ri]) ri = i; // what if they are
    }

    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        int src, dst, w;
        std::cin >> src >> dst >> w;
        // we need to check if theres already a 
        e[dst].emplace_back(src, w);
        // store incoming edges
    }

    int nn = 0;
    ll res = 0;

    for (int i = 1; i <= n; ++i) { // for every employee
        if (e[i].empty()) {
            nn++;
            continue;
        }
        int mw = INF;
        for (pii edge : e[i]) { // for every one of their incoming edges
            mw = std::min(mw, edge.second);
            // "incoming, weight"
        }
        res += mw;
    }

    if (nn > 1) {
        std::cout << -1;
    } else {
        std::cout << res;  
    }

    return 0;
}



    // // start at the root, add all outgoing nodes to pq 
    // for (pii re : e[ri]) {
    //     pq.push(re);
    // } 

    // int nv = 1;
    // visited[ri] = 1;
    // ll res = 0;

    // while(!pq.empty()) {
    //     pii ce = pq.top(); pq.pop();
    //     if (visited[ce.second]) continue; // if this edge has been visited, skip
        
    //     for (pii ne : e[ce.second]) pq.push(ne); // add all this neighbours edges to pw
    //     res += ce.first; // add the weight of the edge we took
    //     visited[ce.second] = 1; // set this neighbour as visited
    //     nv++; // increment number visited
    // }
    // std::cout << std::endl;

    // if (nv == n) {
    //     std::cout << res;  
    // } else {
    //     std::cout << -1;
    // }
    

// int num_components;
// int employee[N];



// int mst() {
//     int total_weight = 0;
//     in_tree[0] = true;
//     for (auto edge : edges[0]) pq.emplace(edge.first, edge.second);
//     while (!pq.empty()) {
//         auto edge = pq.top(); pq.pop();
//         if (in_tree[edge.second]) continue;
//         in_tree[edge.second] = true;
//         total_weight += edge.first;
//         for (auto edge : edges[edge.second]) pq.emplace(edge.first, edge.second);
//     }
//     return total_weight;
// }

// signed main() {
//     std::cin >> n;
//     num_components = n;
//     for (int i = 0; i < n; ++i) std::cin >> employee[i];

//     std::cin >> m;
//     for (int i = 0; i < m; ++i) {
//         int a, b, c;
//         std::cin >> a >> b >> c;
//         edges[i] = {a, b, c};
//     }

//     int res = 0;
    




//     std::sort(edges, edges + m);
//     int res = 0;
//     for (int i = 0; i < m; ++i) {
//         edge& e = edges[i];
//         if (root(e.u) != root(e.v)) {
//             res += e.w;
//             join(e.u, e.v);
//             num_components--;
//             // std::cout << "Edge Cost Taken: " << e.w << std::endl;
//         }
//     }
//     // std::cout << "res: " << res <<std::endl;

//     // std::cout << "parent array: ";
//     for (int i = 0; i < n; ++i) {
//         std::cout << parent[i] << " ";
//     }

//     std::cout << std::endl;

//     if (num_components > 1) {
//         std::cout << "NUM COMPONENTS: " << num_components << std::endl;
//         std::cout << -1;
//     } else {
//         std::cout << res;    
//     }
    

//     return 0;
// }