#include <bits/stdc++.h>

using ll = long long;

typedef std::pair<int,int> pii;

constexpr int LEFT = 0;
constexpr int RIGHT = 1;
constexpr int N = 1000000;

struct state {
    int w;
    int h;
    int wh;
    state(int _w, int _h, int _wh) : w(_w), h(_h), wh(_wh) {}
};


bool spike_l[N];
bool spike_r[N];
std::stack<state> q;
int n;
int k;
bool visited[2][N + 1]; // To track visited states on both walls up to height n


signed main() {
    std::cin >> n >> k;

    std::string l_string;
    std::string r_string;
    std::cin >> l_string >> r_string;

    for (int i = 0; i < n; ++i) spike_l[i+1] = l_string[i] == 'X' ? 1 : 0;
    for (int i = 0; i < n; ++i) spike_r[i+1] = r_string[i] == 'X' ? 1 : 0;

    int sh = 1;
    int sw = 0; // 0 for L, 1 for R
    int swh = 0;
    visited[sw][sh] = true;

    // BFS, since every edge is unit weight
    q.push(state(sw, sh, swh));
    while (!q.empty()) {
        int cw = q.top().w, ch = q.top().h, cwh = q.top().wh; q.pop();

        if (ch <= cwh) continue; // if i am in de worter, continue

        if (visited[cw][ch]) continue;
        visited[cw][ch] = true;

        if (ch > n) {
            std::cout << "YES\n";
            return 0;
        }

        bool up_invalid = (spike_l[ch + 1] && cw == LEFT) || (spike_r[ch + 1] && cw == RIGHT);
        bool down_invalid = (spike_l[ch - 1] && cw == LEFT) || (spike_r[ch - 1] && cw == RIGHT) || ch == 1;
        bool hop_invalid = (spike_r[ch + k] && cw == LEFT) || (spike_l[ch + k] && cw == RIGHT);

        // check all of the next potential positions, before adding to queue, check valid
        if (!up_invalid) q.push(state(cw, ch+1, cwh + 1));
        if (!down_invalid) q.push(state(cw, ch-1, cwh + 1));
        if (!hop_invalid) q.push(state(cw == LEFT ? RIGHT : LEFT, ch+k, cwh + 1));
    }


    std::cout << "NO\n";
    return 0;
}