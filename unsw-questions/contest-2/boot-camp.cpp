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

constexpr int N = 18;

const int MOD = 1e9 + 7;

ll dp[1<<N][N];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // initialise to 0
    memset(dp, 0, sizeof(dp));

    for (int i = 0; i < n; ++i) {
        dp[1 << i][i] = 1;
    }

    for (int s = 0; s < (1<<n); s++) { // for all subsets of n elements in increasing order
        // iterate through everyone that could be last in the current arrangement
        for (int l = 0; l < n; ++l) {
            if (!(s & (1 << l))) continue;
                for (int p = 0; p < n; ++p) { // all people that could come b4
                    if (p == l) continue; // if p and l are the
                    if (!(s & (1 << p))) continue; // if p not in set
                    dp[s][l] = (dp[s][l] + dp[s ^ (1 << l)][p]) % MOD;
                }
        }
    }

    // state dp[i][j]: how many ways to choose n people where the most recent chosen is j
    // base case - the front of the line - how many ways to order people
    // recurrence dp[i][j] = sum(dp[i-1][k]), where j is all the elements 
        // and where j doesn't preceed i in the original line
    // need to also mask so store who has been chosen as well

    
    int res = 0;
    int fs = (1 << n) - 1; // everyone chosen
    for (int l = 0; l < n; ++l) {
        res = (res + dp[fs][l]) % MOD;
    }

    cout << res << "\n";
}