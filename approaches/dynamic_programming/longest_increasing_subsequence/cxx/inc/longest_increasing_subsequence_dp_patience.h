// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
longest_increasing_subsequence_dp_patience.h file is part of Algosnippet.
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
        class longest_increasing_subsequence_patience {
        public:
            //! Dynamic programming with patience sort gives `O(n*n)` runtime
            static int calc(const int*arr,const int n) {
                int pile_height[n];
                int result = 0;
#ifdef DEBUG_LONGEST_INCREASING_SUBSEQUENCE
                int pred[n];
#endif

                //! card piles contain pile of cards, nth pile contains n cards.
                int top_card_list[n+1];
                for(int i = 0; i <= n; i++) {
                    top_card_list[i] = -1;
                }
                // base case
                pile_height[0] = 1;
                int pile_len = 1;
                top_card_list[1] = 0;
#ifdef DEBUG_LONGEST_INCREASING_SUBSEQUENCE
                pred[0] = -1;
#endif
                for(int i = 1; i < n; i++) {
#ifdef DEBUG_LONGEST_INCREASING_SUBSEQUENCE
                    pred[i] = -1;
#endif
                    pile_height[i] = 1;
                    const int j = pile_search(top_card_list, arr, pile_len, arr[i]);
#ifdef DEBUG_LONGEST_INCREASING_SUBSEQUENCE
                    std::cout << i << ',' << j << std::endl;
#endif
                    if(arr[i] > arr[j]) {
                        if(pile_height[i] < (pile_height[j]+1)) {
                            // relaxation
                            pile_height[i] = pile_height[j]+1;
                            result = std::max(result,pile_height[i]);
                            pile_len = std::max(pile_len,pile_height[i]);
#ifdef DEBUG_LONGEST_INCREASING_SUBSEQUENCE
                            pred[i] = j;
#endif
                        }
                    }
                    if(-1 == top_card_list[pile_height[i]] || arr[top_card_list[pile_height[i]]] > arr[i]) {
                        top_card_list[pile_height[i]] = i; // top card on the pile is now i
                    }
                }
#ifdef DEBUG_LONGEST_INCREASING_SUBSEQUENCE
                for(int i = 0; i < n; i++) {
                    std::cout << top_card_list[i] << '\t';
                }
                std::cout << std::endl;
                for(int i = 0; i < n; i++) {
                    std::cout << pile_height[i] << '\t';
                }
                std::cout << std::endl;
                for(int i = 0; i < n; i++) {
                    std::cout << pred[i] << '\t';
                }
                std::cout << std::endl;
#endif
                return result;
            }
            private:
            inline static int pile_search(const int*top_card_list, const int* arr, int pile_len, int strict_upper_limit) {
                int start = 1,bound=pile_len;
                while(start < bound) {
                    if(arr[top_card_list[bound]] < strict_upper_limit) {
                        return top_card_list[bound];
                    }
                    int mid = (start+bound)/2 + ((start+bound)&1);
                    if(arr[top_card_list[mid]] >= strict_upper_limit) {
                        // go lower
                        bound = mid-1;
                    } else {
                        start = mid;
                    }
                }
                return top_card_list[bound];
            }
        };
    }
}

#endif // ALGO_DYNAMIC_PROGRAMMING_LONGEST_INCREASING_SUBSEQUENCE_H

