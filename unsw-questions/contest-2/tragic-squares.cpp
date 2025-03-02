#include <bits/stdc++.h>

using namespace std;
#pragma region
#define ll long long
#define ull unsigned long long
#define print(x) cout << x << '\n';
#define all(x) x.begin(), x.end()
#define r(i,x,y) for(int i=(x);i<(y);i++)
#define int long long
#define vec vector
#define vi vec<int>
#define pb push_back

#define deb(...) deb_impl(#__VA_ARGS__, __VA_ARGS__)
template<typename T>
void deb_impl(const char* names, T&& arg) {
    std::cout << names << " = " << arg << std::endl;
}

template<typename T, typename... Args>
void deb_impl(const char* names, T&& arg, Args&&... args) {
    const char* comma = strchr(names, ',');
    std::cout.write(names, comma - names) << " = " << arg << ", ";
    deb_impl(comma + 1, std::forward<Args>(args)...);
}

 
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
    return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<
                                    !is_same<T_container, string>::value,
                                    typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v) {
    os << '{';
    string sep;
    for (const T &x : v)
        os << sep << x, sep = ", ";
    return os << '}';
}
void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail> void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}
#ifdef LOCAL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

#pragma endregion
//////////////////////////////////////////////////
 
void solve() {

}
 
//////////////////////////////////////////////////

constexpr int N = 1000;

ll g[N][N];

// min and max prefix sum
ll row_min[N][N];
ll row_max[N][N];
ll min_val[N][N];
ll max_val[N][N];

int count_betw(const std::vector<int>& arr, int i, int j) {
    auto it1 = std::lower_bound(arr.begin(), arr.end(), i);
    auto it2 = std::upper_bound(arr.begin(), arr.end(), j);

    return it2 - it1;
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int r, c, k;

    cin >> r >> c >> k;

    std::vector<ll> sorted_g = {};
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cin >> g[i][j];
            sorted_g.push_back(g[i][j]);
        }
    }

    // compute the min and max of each tragic square using sliding window.
    // need to do a 2d sliding window - sliding window over all rows first, then do the same over all columns.
    for (int i = 0; i < r; ++i) {
        deque<int> min_dq, max_dq;
        for (int j = 0; j < c; ++j) {
            // dq - the front of the queue will always hold the index of the smallest element
            while (!min_dq.empty() && g[i][min_dq.back()] >= g[i][j]) min_dq.pop_back(); // remove elements from dq until new element is smallW
            min_dq.push_back(j);
            if (j >= k && min_dq.front() == j - k) min_dq.pop_front();
            if (j >= k - 1) row_min[i][j - k + 1] = g[i][min_dq.front()]; // record the front of the dequeue 

            while (!max_dq.empty() && g[i][max_dq.back()] <= g[i][j]) max_dq.pop_back();
            max_dq.push_back(j);
            if (j >= k && max_dq.front() == j - k) max_dq.pop_front();
            if (j >= k - 1) row_max[i][j - k + 1] = g[i][max_dq.front()];
        }
    }


    for (int j = 0; j <= c - k; ++j) {
        deque<int> min_dq, max_dq;
        for (int i = 0; i < r; ++i) { // now iterate through the ROWS
            while (!min_dq.empty() && row_min[min_dq.back()][j] >= row_min[i][j]) min_dq.pop_back();
            min_dq.push_back(i);
            if (i >= k && min_dq.front() == i - k) min_dq.pop_front();
            if (i >= k - 1) min_val[i - k + 1][j] = row_min[min_dq.front()][j]; 

            while (!max_dq.empty() && row_max[max_dq.back()][j] <= row_max[i][j]) max_dq.pop_back();
            max_dq.push_back(i);
            if (i >= k && max_dq.front() == i - k) max_dq.pop_front();
            if (i >= k - 1) max_val[i - k + 1][j] = row_max[max_dq.front()][j];
        }
    }

    // printing to febug
    // for (int i = 0; i <= r - k; ++i) {
    //     for (int j = 0; j <= c - k; ++j) {
    //         cout << min_val[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    sort(sorted_g.begin(), sorted_g.end());

    // cout << count_betw(sorted_g, 10, 14);


    // iterate through all potential tragic squares (top left corners)
    for (int i = 0; i <= r - k; ++i) {
        for (int j = 0; j <= c - k; ++j) { // check if num elemets between min and max = size of square
            if (count_betw(sorted_g, min_val[i][j], max_val[i][j]) == k * k) {
                cout << "YES\n";
                cout << i + 1 << " " << j + 1;
                return 0;
            }
        }
    }

    cout << "NO";
        
        // 
    return 0;
}