#include <bits/stdc++.h>

using ll = long long;

const int N = 100100;
// the number of additional nodes created can be as high as the next power of two up from N (2^17 = 131,072)
ll sum_tree[1<<18];
ll max_tree[1<<18];
bool inc_tree[1<<18];
bool dec_tree[1<<18]; // stores bools
ll left_tree[1<<18];
ll right_tree[1<<18];
int n; // actual length of underlying array

// query the sum over [qL, qR) (0-based)
// i is the index in the tree, rooted at 1 so children are 2i and 2i+1
// instead of explicitly storing each node's range of responsibility [cL,cR), we calculate it on the way down
// the root node is responsible for [0, n)
ll sum_query(int qL, int qR, int i = 1, int cL = 0, int cR = n) {
    // the query range exactly matches this node's range of responsibility
    if (cL == qL && cR == qR)
    return sum_tree[i];
    // we might need to query one or both of the children
    int mid = (cL + cR) / 2;
    ll ans = 0;
    // query the part within the left child [cL, mid), if any
    if (qL < mid) ans += sum_query(qL, std::min(qR, mid), i * 2, cL, mid);
    // query the part within the right child [mid, cR), if any
    if (qR > mid) ans += sum_query(std::max(qL, mid), qR, i * 2 + 1, mid, cR);
    return ans;
}

ll max_query(int qL, int qR, int i = 1, int cL = 0, int cR = n) {
    if (cL == qL && cR == qR)
    return max_tree[i];

    int mid = (cL + cR) / 2;
    ll ans = 0;

    if (qL < mid) ans = std::max(ans, max_query(qL, std::min(qR, mid), i * 2, cL, mid));
    if (qR > mid) ans = std::max(ans, max_query(std::max(qL, mid), qR, i * 2 + 1, mid, cR));
    return ans;
}

bool inc_query(int qL, int qR, int i = 1, int cL = 0, int cR = n) {
    if (cL == qL && cR == qR)
    return inc_tree[i];

    int mid = (cL + cR) / 2;
    bool ans = true;

    if (qL < mid && qR > mid) ans = ans && (left_tree[i*2+1] >= right_tree[i*2]);
    if (qL < mid) ans = ans && inc_query(qL, std::min(qR, mid), i * 2, cL, mid); 
    if (qR > mid) ans = ans && inc_query(std::max(qL, mid), qR, i * 2 + 1, mid, cR);

    return ans;
}

bool dec_query(int qL, int qR, int i = 1, int cL = 0, int cR = n) {
    if (cL == qL && cR == qR)
    return dec_tree[i];

    int mid = (cL + cR) / 2;
    bool ans = true;

    if (qL < mid && qR > mid) ans = ans && (left_tree[i*2+1] <= right_tree[i*2]);
    if (qL < mid) ans = ans && dec_query(qL, std::min(qR, mid), i * 2, cL, mid); 
    if (qR > mid) ans = ans && dec_query(std::max(qL, mid), qR, i * 2 + 1, mid, cR);

    return ans;
}

// p is the index in the array (0-based)
// v is the value that the p-th element will be updated to
// i is the index in the tree, rooted at 1 so children are 2i and 2i+1
// instead of explicitly storing each node's range of responsibility [cL,cR), we calculate it on the way down
// the root node is responsible for [0, n)
void update(int p, ll v, int i = 1, int cL = 0, int cR = n) {
    if (cR - cL == 1) {
        // this node is a leaf, so apply the update
        sum_tree[i] = v;
        max_tree[i] = v;
        left_tree[i] = v;
        right_tree[i] = v;
        inc_tree[i] = true;
        dec_tree[i] = true;

        return;
    }
    // figure out which child is responsible for the index (p) being updated
    int mid = (cL + cR) / 2;
    if (p < mid)
        update(p, v, i * 2, cL, mid);
    else
        update(p, v, i * 2 + 1, mid, cR);
    // once we have updated the correct child, recalculate our stored value.
    sum_tree[i] = sum_tree[i*2] + sum_tree[i*2+1];
    max_tree[i] = std::max(max_tree[i*2], max_tree[i*2+1]);
    right_tree[i] = right_tree[i*2+1];
    left_tree[i] = left_tree[i*2];
    inc_tree[i] = (inc_tree[i*2] && inc_tree[i*2+1]) && (left_tree[i*2+1] >= right_tree[i*2]);
    dec_tree[i] = (dec_tree[i*2] && dec_tree[i*2+1]) && (left_tree[i*2+1] <= right_tree[i*2]);
}


int main() {
    ll m;

    std::cin >> n >> m;

    for (auto i = 0; i < n; ++i) {
        int v;
        std::cin >> v;
        update(i, v);
    }

    std::ostringstream output;

    for (auto i = 0; i < m; ++i) {
        char ci;
        std::cin >> ci;

        if (ci == 'U') {
            ll x, d;
            std::cin >> x >> d;
            update(x - 1, d);
        } else if (ci == 'M') {
            ll x, y;
            std::cin >> x >> y;
            output << max_query(x - 1, y) << "\n";
        } else if (ci == 'S') {
            ll x, y;
            std::cin >> x >> y;
            output << sum_query(x - 1, y) << "\n";
        } else if (ci == 'I') {
            ll x, y;
            std::cin >> x >> y;
            output << inc_query(x - 1, y) << "\n";
        } else if (ci == 'D') {
            ll x, y;
            std::cin >> x >> y;
            output << dec_query(x - 1, y) << "\n";
        }
    }

    std::cout << output.str();
    return 0;
}