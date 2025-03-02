#include <cassert>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

const int MAXN = 500000 + 10;

multiset<long long> S;
int n, m, q;
int popul[MAXN], popul_before[MAXN], x[MAXN], y[MAXN], A[MAXN], B[MAXN], par[MAXN];
long long tot[MAXN], ans[MAXN];
bool del[MAXN];
string type[MAXN];

long long most_populated_region_size () {
    multiset<long long>::iterator it = S.end();
    --it;
    return *it;
}

int fs (int k) {
    if (k != par[k])
        par[k] = fs(par[k]);
    return par[k];
}

void link (int x, int y) {
    x = fs(x);
    y = fs(y);
    if (x == y) return ;
    S.erase(S.find(tot[x]));
    S.erase(S.find(tot[y]));
    tot[y] += tot[x];
    S.insert(tot[y]);
    par[x] = y;
}

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i = 1; i <= n; i++)
        cin >> popul[i];
    for(int i = 1; i <= m; i++)
        cin >> x[i] >> y[i];
    for(int i = 1; i <= q; i++) {
        cin >> type[i];
        if (type[i] == "D") {
            cin >> A[i];
            assert(!del[A[i]]);
            del[A[i]] = true;
        } else {
            cin >> A[i] >> B[i];
            popul_before[i] = popul[A[i]];
            popul[A[i]] = B[i];
        }
    }

    for(int i = 1; i <= n; i++) {
        par[i] = i;
        tot[i] = popul[i];
        S.insert(tot[i]);
    }

    for(int i = 1; i <= m; i++)
        if (!del[i]) link(x[i], y[i]);

    ans[q] = most_populated_region_size();

    for(int i = q; i >= 1; i--) {
        if (type[i] == "D")
            link(x[A[i]], y[A[i]]);
        else {
            int my_id = fs(A[i]);
            S.erase(S.find(tot[my_id]));
            tot[my_id] -= popul[A[i]];
            popul[A[i]] = popul_before[i];
            tot[my_id] += popul[A[i]];
            S.insert(tot[my_id]);
        }
        ans[i - 1] = most_populated_region_size();
    }

    for(int i = 1; i <= q; i++)
        cout << ans[i] << endl;
    return 0;
}