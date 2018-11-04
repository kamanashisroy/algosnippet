// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
longest_increasing_subsequence_dp.h file is part of Algosnippet.
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

#ifndef ALGO_DYNAMIC_PROGRAMMING_LONGEST_INCREASING_SUBSEQUENCE_H
#define ALGO_DYNAMIC_PROGRAMMING_LONGEST_INCREASING_SUBSEQUENCE_H

#include <algorithm> //defines max

#ifdef DEBUG_LONGEST_INCREASING_SUBSEQUENCE
#include <iostream>
#endif

namespace algo_snippet {
    namespace dynamic_programming {
        class longest_increasing_subsequence {
        public:
            //! Dynamic programming gives `O(n*n)` runtime.
            static int calc(const int*arr, const int n) {
                int memo_len[n];
#ifdef DEBUG_LONGEST_INCREASING_SUBSEQUENCE
                int pred[n];
                
#endif
                int result = 0;
                
                // init
                memo_len[0] = 1;
#ifdef DEBUG_LONGEST_INCREASING_SUBSEQUENCE
                pred[0] = -1;
#endif
                for(int i = 1; i < n; i++) {
#ifdef DEBUG_LONGEST_INCREASING_SUBSEQUENCE
                    pred[i] = -1;
#endif
                    memo_len[i] = 1;
                    for(int j = 0; j < i; j++) {
                        if(arr[i] > arr[j]) { // build-up on previous optimization
                            if(memo_len[i] < (memo_len[j]+1)) {
                                // relaxation
                                memo_len[i] = memo_len[j]+1;
                                result = std::max(result,memo_len[i]);
#ifdef DEBUG_LONGEST_INCREASING_SUBSEQUENCE
                                pred[i] = j;
#endif
                            }
                        }
                    }
                }
#ifdef DEBUG_LONGEST_INCREASING_SUBSEQUENCE
                for(int i = 0; i < n; i++) {
                    std::cout << memo_len[i] << '\t';
                }
                std::cout << std::endl;
                for(int i = 0; i < n; i++) {
                    std::cout << pred[i] << '\t';
                }
                std::cout << std::endl;
#endif
                return result;
            }
        };
    }
}

#endif // ALGO_DYNAMIC_PROGRAMMING_LONGEST_INCREASING_SUBSEQUENCE_H

