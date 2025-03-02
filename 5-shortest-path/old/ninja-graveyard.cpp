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

    // for (int i = 1; i <= n; ++i) {
    //     std::cout << spike_l[i];
    // }
    // std::cout << "\n";

    // for (int i = 1; i <= n; ++i) {
    //     std::cout << spike_r[i];
    // }
    // std::cout << "\n";
    int sh = 1;
    int sw = 0; // 0 for L, 1 for R
    int swh = 0;

    // BFS, since every edge is unit weight
    q.push(state(sw, sh, swh));
    while (!q.empty()) {
        int cw = q.top().w, ch = q.top().h, cwh = q.top().wh; q.pop();
        // std::cout << "[STATE BEGIN] " << std::endl;
        // std::cout << "current_height: " << ch << std::endl;
        // std::cout << "current_wall: " << cw << std::endl;

        if (ch <= cwh) continue; // if i am in de worter, continue

        if (ch > n) {
            std::cout << "YES\n";
            return 0;
        }

        // bool up_invalid, down_invalid, hop_invalid;
        // if (cw == LEFT) {
        //     bool up_invalid = spike_l[ch + 1];
        //     bool down_invalid = spike_l[ch - 1] || ch == 1;
        //     bool hop_invalid = spike_r[ch + k] && cw == LEFT) || (spike_l[ch + k] && cw == RIGHT);
        // } else {
        //     bool up_invalid = (spike_l[ch + 1] && cw == LEFT) || (spike_r[ch + 1] && cw == RIGHT);
        //     bool down_invalid = (spike_l[ch - 1] && cw == LEFT) || (spike_r[ch - 1] && cw == RIGHT) || ch == 1;
        //     bool hop_invalid = (spike_r[ch + k] && cw == LEFT) || (spike_r[ch + k] && cw == RIGHT);
        // }
        bool up_invalid = (spike_l[ch + 1] && cw == LEFT) || (spike_r[ch + 1] && cw == RIGHT);
        bool down_invalid = (spike_l[ch - 1] && cw == LEFT) || (spike_r[ch - 1] && cw == RIGHT) || ch == 1;
        bool hop_invalid = (spike_r[ch + k] && cw == LEFT) || (spike_l[ch + k] && cw == RIGHT);

        
        // std::cout << "Up Invalid: " << up_invalid << std::endl;
        // std::cout << "Down Invalid: " << down_invalid << std::endl;
        // std::cout << "Hop Invalid: " << hop_invalid << std::endl;

        // check all of the next potential positions, before adding to queue, check valid
        if (!up_invalid) q.push(state(cw, ch+1, cwh + 1));
        if (!down_invalid) q.push(state(cw, ch-1, cwh + 1));
        if (!hop_invalid) q.push(state(cw == LEFT ? RIGHT : LEFT, ch+k, cwh + 1));
    }


    std::cout << "NO\n";
    return 0;

    // each position on the wall is a pii
        // wall number, and position on all

    // starts on the lower level of the left wall

    // each edge is a route that the little man can jump form position to position

    // don't need an array larger than n+k

    // after the ninja moves, some of the positions are no longer available

    // Restriction on going to spiked locations, and going to 

    // do a BFS, test all possible outgoing

    // we don't have to store the next components, we can just try them
}