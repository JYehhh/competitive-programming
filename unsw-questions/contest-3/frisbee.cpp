#include <bits/stdc++.h>

using ll = long long;
typedef std::pair<int,int> pii;

constexpr int N = 300000;

std::vector<int> edges[N];
std::vector<int> visited(N);

// std::unordered_map<int, std::unordered_map<int, bool>> visited;
int n;


// lets just do subtask 1



// bool dfs_spanning_path(int u, std::vector<int> v) {
//     // if visited skip
//     if (v[u]) return 0;
//     visited[u] = 1;
//     // if everything is visited at this point, then we return
//     for (int i = 1; i <= n; ++i) return true;

//     for (int e : edges[u]) dfs_spanning_path
// }

signed main() {
    std::cin >> n;

    for (int i = 1; i <= n; ++i) { // creating edges;
        int p1, p2;
        std::cin >> p1 >> p2;
        edges[i].emplace_back(p1);
        edges[i].emplace_back(p2);
    }
    // dfs but you're allowed to touch yourself again as long as 
    // you have a pending outgoing node.
    std::stack<pii> s;
    s.emplace(1, 1);

    while (!s.empty()) {
        pii cur = s.top(); s.pop();
        int cur_node = cur.first, num_visited = cur.second;

        std::cout << "Processing edge to: " << cur_node << " having visited: " << num_visited << std::endl;
        // std::cout << "Processing edge to: " << cur_node << "having visited: " << num_visited;
        if (num_visited == n) {
            std::cout << "Yes\n";
            return 0;
        }
        

        // if we've visited this node before with same amount of num visited
        // skip it
        // if (visited[cur_node] == num_visited) continue;
        if (num_visited <= visited[cur_node]) continue;

        visited[cur_node] = num_visited;

        for (int v : edges[cur_node]) {
            if (v != cur_node) s.emplace(v, num_visited + 1);
        } 
    }

    std::cout << "No" << std::endl;


    // bool reachable = false;
    // for (int i = 1; i <= n; ++i) {
    //     if (visited[i][n]) {
    //         reachable = true;
    //         break;
    //     }
    // }
    // std::cout << (reachable ? "Yes" : "No") << std::endl;
    // for (int i = 1; i <= n; ++i) {
    //     if (!visited[i]) {
    //         std::cout << "No\n";
    //         return 0;
    //     }
    // }

    // std::cout << "Yes\n";
    // return 0;


}