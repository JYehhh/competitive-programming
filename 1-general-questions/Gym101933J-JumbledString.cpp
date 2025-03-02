#include <bits/stdc++.h>

typedef long long ll;

ll a,b,c,d;
    // a == 00
    // b == 01
    // c == 10
    // d == 11

    // first, calculate the number of 0's needed and 1's needed
        // Total 0’s: ANSc2 = a
        // Total 1’s: ANSc2 = b
signed main() {
    std::cin >> a >> b >> c >> d;

    // add special case
    if (!a && !b && !c && !d) {
        std::cout << "0" << std::endl;
        return 0;
    }

    ll num_0;
    ll num_1;
    num_0 = (1 + sqrt(1 + 8 * a)) / 2; // ANSc2 = a
    if(num_0 * (num_0 - 1) / 2 != a) { // validate if rounding has occured
        std::cout << "impossible" << std::endl;
        return 0;
    }
    num_1 = (1 + sqrt(1 + 8 * d)) / 2; // ANSc2 = b
    if (num_1 * (num_1 - 1) / 2 != d) { // validate if rounding has occured
        std::cout << "impossible" << std::endl;
        return 0;
    }


    if (!a && !d) {
        if(b == 1&& !c) std::cout << "01" << std::endl;

        else if(c == 1 && !b) std::cout << "10" << std::endl;

        else std::cout << "impossible" << std::endl;
        return 0;
    }
    if (!b && !c) {
        if(!a) for(int i = 0; i < num_1; i++) std::cout << "1";

        else if(!d) for(int i = 0; i < num_0; i++) std::cout << "0";

        else std::cout << "impossible" << std::endl;
        return 0;
    }
    
    if (num_0 * num_1 != b + c) { // the number of 1 * 0 must equal the sum of 10 and 01
        std::cout << "impossible" << std::endl;
        return 0;
    }



    // allocate the 01, and the 10 will fall into order.
    // everytime you put a 0 down, you guarantee that all following 1's will
    // contribute to the count of 01's 

    // 000111

    // lets say you need 5 01's
    // 333, 322, 321
    // current_avail 1's = 3.

    // number of 0's you need to put before 1's is:
    // b / num_1 is the number of 0's u need to put before putting down any 1's
    // now that b / num_1 01's are covered, we need to make sure that the remainder is satisfied
    // then put down 1's until you num_1 reaches b % num_1
    // then put down the rest of your -'s
    // then pad with the rest of 1's

    // num_0 = 6
    // num_1 = 3
    // 12 01's
    // 6 10's

    // q = 12 / 3 = 4
    // w = 12 % 3 = 0

    // 00001110

    // put down q 0's, now q*num_1 01's are covered.
    // put down num_1 - w 1's
    // put down a 0 (if theres a remainder)
    // then put down all your 1's 
    // then put down all your 0's

    // 5 / 3 = 1
    // 5 % 3 = 2
    // 3 - 2
    // 0100


    // just need to place the 01's properly, the 10's will follow
    ll init_0 = b / num_1; // b / num_1 is the number of 0's u need to put before putting down any 1's
    ll rem = b % num_1;
    for (int i = 0; i < init_0; i++) std::cout << "0"; // put down those 0's
    for (int i = 0; i < num_1 - rem; i++) std::cout << "1";

    if (init_0 != num_0) std::cout << "0"; // if there is no remainder and we havent placed all, place last

    for (int i = 0; i < rem; i++) std::cout << "1"; // put all your 1's
    for (int i = 0; i < num_0 - init_0 - 1; i++) std::cout << "0"; // put all your 0's

    return 0;
}


    // special cases


    // 

    // second, calculate whether or not 
        // if b + c > w*b, not possible.
    // third, place items in order.
        // 


    // To make a string that has a occur 3 times
    // 00011

    // Total 0’s choose 2 = a
    // For every 1, sum all preceeding 0’s
    // For every 1, sum all proceeding 0’s
    // Total 1’s choose 2 = da