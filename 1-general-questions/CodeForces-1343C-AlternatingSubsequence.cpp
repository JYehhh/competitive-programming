#include <bits/stdc++.h>

typedef long long ll;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

int t;

signed main() {
    std::cin >> t;

    for (int i = 0; i < t; ++i) {
        int n;
        std::cin >> n;

        ll inp[n + 100];
        for (int j = 0; j < n; ++j) {
            std::cin >> inp[j];
        }


        // check if the first element is - or +
        int curr_sign = sgn(inp[0]);
        ll curr_max = inp[0];
        ll res_sum = 0;
        int res_size = 1;

        for (int j = 1; j < n; ++j) {
            if (sgn(inp[j]) != curr_sign) { // if the sign flipped
                res_sum += curr_max;
                res_size++;
                curr_max = inp[j];
                curr_sign = sgn(inp[j]);
            } else {
                curr_max = std::max(curr_max, inp[j]);
            }
        }
        res_sum += curr_max;
        std::cout << res_sum << std::endl;

    }
}
