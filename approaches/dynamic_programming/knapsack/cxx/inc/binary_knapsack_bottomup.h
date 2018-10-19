// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
binary_knapsack_bottomup.h file is part of Algosnippet.
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
#include <cstring> // defines memset
#endif

namespace algo_snippet {
    namespace dynamic_programming {
        template <typename GOODTYPE, typename BADTYPE, typename INTTYPE>
        class binary_knapsack_bottomup {
        public:
            // Runtime is O(badness_limit*n)
            binary_knapsack_bottomup(const std::vector<GOODTYPE>& goodness, const std::vector<BADTYPE>& badness, BADTYPE badness_limit)
                : goodness(goodness)
                  , badness(badness)
                  , badness_limit(badness_limit)
                  , n(std::min(goodness.size(),badness.size())){
                // assert(goodness.size() == badness.size());
            }

            int calc() {
                if(goodness.size() != badness.size()) {
                    return -1;
                }
                result = 0;
                
                // keep track of maximum goodness, it takes O(n*n) memory
                memo.resize(n+1);
                memo[0].resize(badness_limit+1,0);

                for(INTTYPE i = 0; i < n; i++) {
                    const BADTYPE& xbad = badness[i];
                    const GOODTYPE& xgood = goodness[i];

                    memo[i+1].reserve(badness_limit+1);
                    std::copy(memo[i].begin(),memo[i].end(),std::back_inserter(memo[i+1]));

                    // avoid overflow
                    if(xbad >= badness_limit) {
                        continue;
                    }

                    // combine with others
                    for(BADTYPE j = 0; j <= (badness_limit - xbad); j++) {
                        if( (memo[i][j] + xgood) > memo[i+1][j+xbad] ) {
                            memo[i+1][j+xbad] = memo[i][j]+xgood;
                            result = std::max(result,memo[i+1][j+xbad]);
                        }
                    }

                }

                return 0;
            }

            #ifdef DEBUG_KNAPSACK
            void dump(std::ostream& dout) {

                // reconstruct path from the result and memo
                std::vector<INTTYPE> selection;
                char path[n+1][badness_limit+1];
                memset(path, ' ', sizeof(path));
                BADTYPE ypos = badness_limit;
                INTTYPE xpos = n;
                while(xpos > 0 && ypos > 0) {
                    if( ypos < badness[xpos-1] ) {
                        xpos--;
                        continue;
                    }
                    if((memo[xpos-1][ypos-badness[xpos-1]] + goodness[xpos-1]) == memo[xpos][ypos]) {
                        path[xpos][ypos] = '*';
                        ypos -= badness[xpos-1];
                        xpos--;
                        selection.push_back(xpos);
                    }
                }
                
                // dump
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
                std::cout << "Badness Lims:\t" << "Iter ";
                for(BADTYPE j = 0; j <= badness_limit; j++) {
                    std::cout << std::setw(4) << j << " ,";
                }
                std::cout << std::endl;
                for(INTTYPE i = 0; i <= n; i++) {
                    std::cout << "Max-Goodness:\t" << std::setw(4) << i << ',';
                    for(BADTYPE j = 0; j <= badness_limit; j++) {
                        std::cout << std::setw(4) << memo[i][j] << path[i][j] << ',';
                    }
                    std::cout << std::endl;
                }
                std::cout << "Selected items:";
                for(auto& i : selection) {
                    std::cout << "(idx=" << i << ",bad=" << badness[i] << ",good=" << goodness[i] << ')';
                }
                std::cout << std::endl;
            }
            #endif

            GOODTYPE get_result() const {
                return result;
            }
        private:
            const std::vector<GOODTYPE>& goodness;
            const std::vector<BADTYPE>& badness;
            const BADTYPE badness_limit;
            const INTTYPE n;
            GOODTYPE result;
            std::vector<std::vector<GOODTYPE>> memo;
        };
    }
}

#endif // ALGO_DYNAMIC_PROGRAMMING_KNAPSACK_H

