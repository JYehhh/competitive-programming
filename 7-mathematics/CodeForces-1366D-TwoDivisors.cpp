#include <bits/stdc++.h>

using ll = long long;
using ld = long double;
typedef std::pair<int,int> pii;

using namespace std;

constexpr int N = 1e7;

int n;
vector<pii> res;

// unordered_map<int, int> primefactorize(int x) {
//     unordered_map<int, int> factors;
//     for (int f = 2; f*f <= x; f++)
//         while (x % f == 0) {
//         factors[f]++;
//         x /= f;
//         }

//     if (x != 1) factors[x]++;
//     return factors;
// }

bool marked[N+1];
vector<int> prime_fac(N+1);

signed main() {
    std::cin >> n;
    
    // modified the sieve to just store one of the prime factors.
    for (int i = 2; i <= N; i++) {
        if (!marked[i]) { // if it hasn't been marked yet, it's prime
            prime_fac[i] = i;
            for (int j = 2*i; j <= N; j += i) {
                marked[j] = true;
                int tmp = j;
                while (tmp % i == 0) {
                    prime_fac[j] = i;
                    tmp /= i;
                }
            }
        }
    }


    for (int i = 0; i < n; ++i) {
        int cur; cin >> cur; 
        int cop = cur;

        int f = prime_fac[cur];

        int multiplicity = 0;
        int d1 = 1, d2 = 1;
        while (cur % f == 0) {  // Extract the power of the smallest prime factor.
            cur /= f;
            d1 *= f;
        }

        d2 = cop / d1;  
        if (d1 > 1 && d2 > 1) 
            res.emplace_back(d1, d2);
        else
            res.emplace_back(-1, -1); 
            


        // if (f.empty()) {
        //     // No prime factors (e.g., 0 or 1).
        //     res.emplace_back(-1, -1);
        //     continue;
        // }

        // // Compute d1 and d2:
        // int d1 = 1, d2 = 1;
        // int first_prime = f[0]; // Get the first prime factor.

        // // Count multiplicity of the first prime factor:
        // int multiplicity = 0;
        // for (int x : f) 
        //     if (x == first_prime) multiplicity++;

        // // Compute d1 = first_prime^multiplicity:
        // d1 = pow(first_prime, multiplicity);

        // // Compute d2 by multiplying all factors of cur except those in d1:
        // d2 = cur / d1;

        // if (d2 == 1) {
        //     res.emplace_back(-1, -1);
        // } else {
        //     res.emplace_back(d1, d2);
        // }

        // unordered_map<int, int> f = primefactorize(cur);

        // if (f.size() <= 1) {
        //     res.emplace_back(-1, -1);
        //     continue;
        // } // this should cover the 0 and 1 case.

        // auto j = f.begin();

        // int d1 = 1; int d2 = 1;
        // d1 *= pow(j->first, j->second);
        // d2 = cur / d1;
        // // ++j;

        // // for (;j != f.end(); ++j) d2 *= pow(j->first, j->second);

        // res.emplace_back(d1, d2);
    } 

    for (int i = 0; i < n; ++i) cout << res[i].first << " ";
    cout << "\n";
    for (int i = 0; i < n; ++i) cout << res[i].second << " ";

    return 0;
}



// so the theory is, if we have more than two distinct prime factors,
// taking the first prime factor with all of it's multiplicity, as the d1
// and then using the rest of the  (n/d1) as d2, we will get our two numbers

// proof by contradiction:
// suppose that gcd(d1 + d2, n) = b, and b != 1
    // because b divides n, it follows b | d1 and/or b | d2
    // but, since d1 and d2 are coprime, they can only divide one.
    // thus, b | d1 OR b | d2.

// now we also have that b divides d1 + d2. 
    // in order for that to be the case, b must divide both d1 and d2, 
    // and cannot just divide one of them as above.

// thus, contradiction.