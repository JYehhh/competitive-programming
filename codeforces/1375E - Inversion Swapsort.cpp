#include <bits/stdc++.h>

using namespace std;
using ll = long long;
typedef std::pair<int,int> pii;

constexpr int N = 1000 + 10;

int n, num;
std::vector<pii> a(N), swaps;

void get_numswaps() {
    num = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (a[i] > a[j]) num++;
        }
    }
}

signed main() {
    std::cin >> n;

    for (int i = 1; i <= n; ++i) {
        int val; std::cin >> val;
        a[i] = make_pair(val, i);
    }

    // compute number of swaps
    get_numswaps();

    // std::sort(a.begin() + 1, a.begin() + n + 1);

    // testing the funky sort
    // for (int i = 1; i <= n; ++i) {
    //     std::cout << a[i].first << " ";
    // }
    // std::cout << "\n";

    // run bubble sort, if we swap, record the indexes swapped.
    // if the list was already sorted, the indexes wouldn't have changed, 
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n-i; ++j){
            if (a[j].first > a[j+1].first) {
                swaps.emplace_back(a[j].second, a[j+1].second);
                std::swap(a[j], a[j + 1]);
            }
        }
    }

    std::cout << num << "\n";
    std::reverse(swaps.begin(), swaps.end());
    for (auto s : swaps) std::cout << s.first << " " << s.second << "\n";

    return 0;
}