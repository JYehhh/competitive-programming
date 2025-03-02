#include <bits/stdc++.h>

constexpr int N = 1100;

std::string s[N];


signed main() {
    int n;
    std::cin >> n;

    int j = 1;
    bool fishy = false;

    for (int i = 0; i < n; ++i) {
        std::cin >> s[i];
    }

    for (int i = 0; i < n; ++i, ++j) {
        if (s[i] != "mumble" && s[i] != std::to_string(j)) {
            fishy = true;
        }
    }

    if (fishy) {
        std::cout << "something is fishy";
    } else {
        std::cout << "makes sense";
    }

}