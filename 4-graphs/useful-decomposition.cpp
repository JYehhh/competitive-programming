#include <bits/stdc++.h>

using ll = long long;
typedef std::pair<int,int> pii;

constexpr int N = 1000000;

int n;
std::vector<int> e[N];
std::vector<int> degree(N);
std::vector<int> endpoints;

signed main () {
    // Splitting the edges of the tree in simple paths.
    // Each path has at least one common vertex.
    // Each edge of the tree should be in exactly one path.
    std::cin >> n;
    int ng2 = 0;

    // compute nodes with degree 3
    for (int i = 0; i < n - 1; ++i) {
        int src, dst;
        std::cin >> src >> dst;
        degree[src]++;
        degree[dst]++;
    }

    // if there are no nodes with degree 3
    int d3c = 0;
    int ri = 0;
    for (int i = 1; i <= n; ++i) { // iterate through all the nodes
        if (degree[i] > 2) {
            d3c++; // increment the count of d3c
            ri = i;
        }
        if (d3c > 1) {
            std::cout << "No";
            return 0;
        }
        if (degree[i] == 1) endpoints.push_back(i);
    }

    
    if (d3c == 1) {
        std::cout << "Yes" << std::endl << endpoints.size() << std::endl;
        for (int end : endpoints) std::cout << ri << " " << end << std::endl;
    } else {
        std::cout << "Yes" << std::endl << 1 << std::endl;
        std::cout << endpoints[0] << " " << endpoints[1];
    }

    return 0;
}