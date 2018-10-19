// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
unbounded_knapsack_bottomup.h file is part of Algosnippet.
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
#include <iomanip>
#endif

namespace algo_snippet {
    namespace dynamic_programming {
        //! Unbounded knapsack allows unbounded number of each items in the sack.
        template <typename GOODTYPE, typename BADTYPE, typename INTTYPE>
        class unbounded_knapsack_bottomup {
        public:
            // Runtime is O(badness_limit*n)
            static GOODTYPE calc(std::vector<GOODTYPE>& goodness, std::vector<BADTYPE>& badness, BADTYPE badness_limit) {
                // assert(goodness.size() == badness.size());
                const INTTYPE n = std::min(goodness.size(),badness.size()); 

                GOODTYPE result = 0;
                
                // keep track of maximum goodness
                std::vector<GOODTYPE> memo(badness_limit+1,0);

                for(INTTYPE i = 0; i < n; i++) {
                    const BADTYPE& xbad = badness[i];
                    const GOODTYPE& xgood = goodness[i];

                    // avoid overflow
                    if(xbad >= badness_limit) {
                        continue;
                    }

                    BADTYPE kbad = xbad;
                    // Try different number of items(notice the difference with binary knapsack)
                    for(INTTYPE k = 1; kbad <= badness_limit;k++,kbad+=xbad) {
                        // combine with others
                        for(BADTYPE j = 0; j <= (badness_limit - xbad); j++) {
                            if((memo[j] + xgood) > memo[j+xbad] ) {
                                memo[j+xbad] = memo[j]+xgood;
                                result = std::max(result,memo[j+xbad]);
                            }
                        }
                    }

                }

                #ifdef DEBUG_KNAPSACK
                std::cout << "Badness Input:\t";
                for(auto& dbad : badness) {
                    std::cout << std::setw(4) << dbad << ',';
                }
                std::cout << std::endl;
                std::cout << "Goodness Input:\t";
                for(auto& dgood : goodness) {
                    std::cout << std::setw(4) << dgood << ',';
                }
                std::cout << std::endl;
                std::cout << "Badness Lims:\t";
                for(BADTYPE j = 0; j <= badness_limit; j++) {
                    std::cout << std::setw(4) << j << ',';
                }
                std::cout << std::endl;
                std::cout << "Max-Goodness:\t";
                for(BADTYPE j = 0; j <= badness_limit; j++) {
                    std::cout << std::setw(4) << memo[j] << ',';
                }
                std::cout << std::endl;
                #endif

                return result;
            }
        };
    }
}

#endif // ALGO_DYNAMIC_PROGRAMMING_KNAPSACK_H

