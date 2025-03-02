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
 
const int N = 200000;
ll r[N];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // sort the plates in descending order,
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> r[i];
    }
    
    sort(r, r + n, greater<ll>());

    ll le = 1e10; // keep track of the lowest endpoint
    ll cs = 0; // current start point
    ll res = 0;
    vector<ll> res_a = {};

    for (int i = 0; i < n; ++i, ++cs) {
        if (cs < le) { // has to be strictly less than, can't be greater than
            res += 1;
            le = min(le, cs + r[i]);
            res_a.push_back(r[i]);
        } else {
            break;
        }
    }

    cout << res << "\n";
    for (auto i : res_a) {
        cout << i << " ";
    }
    
    return 0;
}