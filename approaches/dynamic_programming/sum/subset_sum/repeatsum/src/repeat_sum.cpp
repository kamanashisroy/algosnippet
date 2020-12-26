#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <iostream>
#include <cassert>
#include <limits>
using namespace std;


/**
 * @brief It finds the number of combination that result the subset sum to be equal to the sum.
 * @params target is the target sum of the integers
 * @params m is the number of integers
 * @returns the number of solutions to the subset sum
 */
template <typename TINT>
TINT find_combination(const TINT target, const TINT m) {
    TINT coins[m];
    TINT i = m;
    // read all the numbers
    while(i--) {
        cin >> coins[i];
        assert(coins[i]);
    }

    //for(i = 0; i < m; i++) {
    //    cout << coins[i] << ',';
    //}
    //cout << '\n';
    TINT memo[target+1];
    TINT path[target+1];
    memo[0] = 0;
    for(TINT i = 1; i <= target; i++) {
        memo[i] = std::numeric_limits<TINT>::max();
        for(TINT j = 0; j < m; j++) {
            if(i >= coins[j] && memo[i-coins[j]] != std::numeric_limits<TINT>::max()) {
                auto cnum = memo[i-coins[j]]+1;
                if(cnum < memo[i]) {
                    // relaxation
                    path[i] = coins[j];
                    memo[i] = cnum;
                }
            }
        }
    }

    cout << "Selected coins: ";
    // dump the path
    for(TINT i = target; i > 0; i = i-path[i]) {
        cout << path[i] << ',';
    }
    cout << endl;
    return memo[target];
}

int main() {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT */     
        int n,m;
        cin >> n >> m;
        cout << find_combination<int>(n,m) << endl;
        return 0;
}

