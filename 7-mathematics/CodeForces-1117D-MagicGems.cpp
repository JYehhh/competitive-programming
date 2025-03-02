#include <bits/stdc++.h>

using ll = long long;
using ld = long double;

using namespace std;
constexpr ll MOD = 1e9 + 7;
constexpr ll M = 100 + 1;

void norm(ll &a) {
    if (a >= MOD) a -= MOD;
    if (a < 0) a += MOD;
}

struct Matrix {
  int n;
  vector<vector<long long>> v;

    Matrix(int _n) : n(_n) {
        v.resize(n);
        for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            v[i].push_back(0);
    }

    Matrix operator*(const Matrix &o) const {
        Matrix res(n);
        for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++) {
                res.v[i][j] += (v[i][k]* o.v[k][j]) % MOD;
                res.v[i][j] %= MOD;
            }
            
        return res;
    }

    static Matrix getIdentity(int n) {
        Matrix res(n);
        for (int i = 0; i < n; i++)
            res.v[i][i] = 1;
        return res;
    }
  
    Matrix operator^(long long k) const {
        Matrix res = Matrix::getIdentity(n);
        Matrix a = *this;
        while (k) { // building up in powers of two
            if (k&1) res = res*a;
            a = a*a;
            k /= 2;
        }
        return res;
    }
};

ll n, m;

signed main() {
    std::cin >> n >> m;
    Matrix rec(M);

    // top row of transition matrix
    rec.v[0][0] = 1;
    rec.v[0][m-1] = 1;
    
    // other rows of transition matrix
    for (int i = 1; i < M; i++)
        rec.v[i][i-1] = 1; 
    
    rec = rec^n;
    cout << rec.v[0][0] << '\n';

    // transition matrix of size M
    // with the top row 1 0 ... 0 1

    // lets do base case as 1 0 0 0 0 0 0 
    // where it's ways to do 1, 0, -1, -2 etc...
    // that way when we power the transition matrix, we can just get the top right

    return 0;
}