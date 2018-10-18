// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
knapsack_bottomup.h file is part of Algosnippet.
Algosnippet is a collection of practice data-structures and algorithms
Copyright (C) 2018  Kamanashis Roy
Algosnippet is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
Algosnippet is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with Algosnippet.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef ALGO_DYNAMIC_PROGRAMMING_KNAPSACK_H
#define ALGO_DYNAMIC_PROGRAMMING_KNAPSACK_H

#include <algorithm> //defines max
#include <vector>
#include <cassert>

#ifdef DEBUG_KNAPSACK
#include <iostream>
#endif

namespace algo_snippet {
    namespace dynamic_programming {
        template <typename GOODTYPE, typename BADTYPE, typename INTTYPE>
        class knapsack_bottomup {
        public:
            // Runtime is O(badness_limit*n)
            static GOODTYPE calc(std::vector<GOODTYPE>& goodness, std::vector<BADTYPE>& badness, BADTYPE badness_limit) {
                // assert(goodness.size() == badness.size());
                const INTTYPE n = std::min(goodness.size(),badness.size()); 

                GOODTYPE result = 0;
                
                // keep track of maximum goodness
                std::vector<GOODTYPE> memo(badness_limit,0);

                for(INTTYPE i = 0; i < n; i++) {
                    const BADTYPE& xbad = badness[i];
                    const GOODTYPE& xgood = goodness[i];

                    // avoid overflow
                    if(xbad >= badness_limit) {
                        continue;
                    }

                    // case 1: combine with others
                    for(BADTYPE j = 0; j < (badness_limit - xbad); j++) {
                        if(0 != memo[j] && (memo[j] + xgood) > memo[j+xbad] ) {
                            memo[j+xbad] = memo[j]+xgood;
                            result = std::max(result,memo[j+xbad]);
                        }
                    }

                    // case 2: base case
                    // NOTE that base case MUST come after combine operation, because it cannot combine with itself
                    if(xgood > memo[xbad]) {
                        memo[xbad] = xgood;
                        result = std::max(result,xgood);
                    }

                }

                #ifdef DEBUG_KNAPSACK
                std::cout << "Badness Lims:\t";
                for(BADTYPE j = 0; j < badness_limit; j++) {
                    std::cout << j << ",\t";
                }
                std::cout << std::endl;
                std::cout << "Max-Goodness:\t";
                for(BADTYPE j = 0; j < badness_limit; j++) {
                    std::cout << memo[j] << ",\t";
                }
                std::cout << std::endl;
                #endif

                return result;
            }
        };
    }
}

#endif // ALGO_DYNAMIC_PROGRAMMING_KNAPSACK_H

