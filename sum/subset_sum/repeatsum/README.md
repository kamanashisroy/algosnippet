
Rpeat-sum solution
===================

The problem is divided into subproblems,

```C++
	z = find_combination_subproblem(solns, localSum, m-1, coins);
```

Here coins contain all the integers. And `m` starts from `coins.length` to 0. 
The localSum starts from sum,sum-multiple*coins[m],sum-multiple*coins[m-1] ... to 0.
And solns is used for memoization of the precalculated values.


```C++

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


```
