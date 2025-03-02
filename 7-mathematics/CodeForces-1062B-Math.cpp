#include <bits/stdc++.h>

using ll = long long;
using ld = long double;

using namespace std;
constexpr int INF = 1e9;
constexpr ll MOD = 1e9 + 7;
typedef std::pair<int,int> pii;
constexpr int N = 1e6;

map<int, int> primefactorize(int x) {
  map<int, int> factors;
  for (int f = 2; f*f <= x; f++)
    while (x % f == 0) {
      factors[f]++;
      x /= f;
    }

  if (x != 1) factors[x]++;
  return factors;
}

int n;
map<int, int> f;

signed main() {
    std::cin >> n;
    f = primefactorize(n);
    
    std::vector<pii> vf(f.begin(), f.end());
    if (vf.empty()) {
        std::cout << "1 0\n";
        return 0;
    } 

    std::sort(vf.begin(), vf.end(), [](const pii& a, const pii& b) {
        return a.second > b.second;
    });

    // check if the highest power can be square rooted
    int highest_p = vf[0].second;

    // if the highest power isn't a perfect square
    bool need_mul = ceil(log2(highest_p)) != log2(highest_p);
    // if any of the powers are not eequal to the highest power
    for (pii v : vf) if (v.second != highest_p) need_mul = true;


    int op = ceil(log2(vf[0].second)) + need_mul;

    int min = 1;
    for (pii i : vf) min *= i.first;

    std::cout << min << " " << op << "\n";

    // std::cout << "\n"
    // prime factorise
    // if any of the prime factors are of odd degree, multiply 
    // square until all prime factors are the same even number - lowest even number
    // square root until you can't anymore

    // the answer is just the product of all the prime factors, the way to get there is:
    // 1 + log2()

    // get the highest multiplicity power, round that up to the nearest power of 2
    // then square root until equals 1
    // or I could just log2, and then round it up




    // maybe it's just the product of all the prime factors?
}