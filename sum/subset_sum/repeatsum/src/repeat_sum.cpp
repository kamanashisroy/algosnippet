#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <iostream>
#include <assert.h>
using namespace std;

int dump = 0;

/**
 * @brief it is counter sort
 * @param coins is an array of integer(unique) numbers
 * @param m is the number of integer in the coins
 * @param max is the maximum value of the integers.
 */
int sort(int*coins, const int m, const int max) {
        int available[max+1];
        int i = m;
        memset(available, 0, sizeof(available));
        while(i--) {
                available[coins[i]]++;
                assert(available[coins[i]] == 1);
        }
        i = max+1;
        int j = m-1;
        while(i--) {
                if(!available[i])
                        continue;
                coins[j--] = i;
        }
        return 0;
}

// @brief it is convenient to declare the type in typedef, so that it is easily modified by just changing it in one place
typedef unsigned long long k_t;
// @brief tipical C++ generics hidden by the typedef.
typedef map<k_t,int> soln_t;

/**
 * @brief it divides the combination problem into subproblems.
 * @param solns Is the precalculated results of the subproblems.
 * @param sum is the target sum for the subproblem
 * @param m is the index of integer(in coins array) that we are interested in this subproblem
 * @param coins is the integer array
 * @returns the number of combinations found that sum equals to the given sum parameter.
 */
k_t find_combination_subproblem(soln_t&solns, const int sum, const int m, int*coins) {
        k_t ct = 0; // accumulated return value
        if(sum == 0) // base case, when the sum is 0, there is no combination.
                return 0;
        if(m == -1) // sanity check
                return 0;
	// find the maximum number of times the integer coins[m] can appear in the sum
        int maxOccur = sum/coins[m];
        int j = 0;
        for(j = 0; j <= maxOccur; j++) { // for all the number of occurances
                int localSum = sum-(j*coins[m]); // reduce the number from the sum for the next subproblem
                if(dump)
                        cout << coins[m] << " occur " << j << " times, find next sum " << localSum << endl;

                if(localSum == 0 && j != 0) {
                        ct += 1;
                        continue;
                }
                if(m == 0) // this is the base case, no more subproblems(no more integers in the array)
                        continue;
                
                k_t z = 0;
                k_t key = (((k_t)localSum) << 8 ) | (m-1); // build a key (sum,index of coin array)
		// check if the solution is precalculated
                auto it = solns.find(key);
                if(it != solns.end()) {
                        z = it->second;
                } else {
			// try to calculate the solution of the subproblem
                        z = find_combination_subproblem(solns, localSum, m-1, coins);
			// save the solution for the future
                        solns.insert(make_pair(key, z));
                }
                if(dump)
                        cout << coins[m] << " occur " << j << " times, for sum " << localSum << " = " << z << endl;
                ct += z;
        }
        return ct;
}

/**
 * @brief It finds the number of combination that result the subset sum to be equal to the sum.
 * @params sum is the target sum of the integers
 * @params m is the number of integers
 * @returns the number of solutions to the subset sum
 */
k_t find_combination(const int sum, const int m) {
        int coins[m];
        int i = m;
        int max = 0;
	// read all the numbers
        while(i--) {
                cin >> coins[i];
                assert(coins[i]);
                if(max < coins[i])
                        max = coins[i];
        }
	// sort them beforehand, so that we can deduct out some of the calculations
        sort(coins, m, max);

        if(dump) {
                for(i = 0; i < m; i++) {
                        cout << coins[i] << ',';
                }
                cout << '\n';
        }
        soln_t solns;
        return find_combination_subproblem(solns, sum, m-1, coins);
}

int main() {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT */     
        int n,m;
        cin >> n >> m;
        cout << find_combination(n,m) << endl;
        return 0;
}

