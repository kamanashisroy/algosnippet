// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
quick_sort.h file is part of Algosnippet.
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

#ifndef ALGO_SORTING_QUICK_SORT_H
#define ALGO_SORTING_QUICK_SORT_H

#include <algorithm>
#include <iterator>
#include <vector>
#include <tuple>
//#include <array>

namespace algo_snippet {
    namespace sorting {
        template<typename ITTYPE>
        struct select_median_of_three {
            ITTYPE operator()(ITTYPE& ibegin, ITTYPE& iend) {
                // sanity check
                if(std::distance(ibegin,iend) < 3) {
                    // we cannot select median of 3
                    return ibegin;
                }

                // check our limit
                ITTYPE max_pivote = ibegin;
                ITTYPE min_pivote = ibegin;
                for(ITTYPE i = ibegin; i != (ibegin+3); i++) {
                    if(*i < *min_pivote) {
                        min_pivote = i;
                    } else if (*i > *max_pivote) {
                        max_pivote = i;
                    }
                }
                ITTYPE pvt = ibegin;
                for(ITTYPE i = ibegin; i != (ibegin+3); i++) {
                    if(*i < *max_pivote) {
                        if(*min_pivote < *i) {
                            pvt = i;
                        }
                    }
                }
                return pvt;
            }
            unsigned int size() const {
                return 3;
            }
        };
        template <typename ITTYPE, typename PIVOTE_SELECT>
        class quick_sort_three_way {
        public:
            quick_sort_three_way() {
            }

            void sort(const ITTYPE ibegin, const ITTYPE iend) {
                part_stack.push_back(std::make_pair(ibegin,iend));
                while(!part_stack.empty()) {
                    const auto& part = part_stack.back();
                    ITTYPE xbegin,xend;
                    std::tie(xbegin,xend) = part;
                    part_stack.pop_back();
#ifdef DEBUG_QUICK_SORT
                    std::cout << "part-quick bucket " << std::distance(ibegin,xbegin) << ',' << std::distance(ibegin,xend) << std::endl;
#endif // DEBUG_QUICK_SORT
                    part_quick(xbegin, xend);
#ifdef DEBUG_QUICK_SORT
                    for(ITTYPE i = ibegin; i != iend; i++) {
                        std::cout << *i << ',';
                    }
                    std::cout << std::endl;
#endif // DEBUG_QUICK_SORT
                }
                // Now that the elements are k-sorted (k=pvt_alg.size()),
                // insertion-sort can take advantage of it.
                //for(ITTYPE i = ibegin+1; i < iend; ++i ) {
                //    std::rotate(std::upper_bound(ibegin, i, *i), i, i+1);
                //}
            }
        private:
            std::vector<std::pair<ITTYPE/* ibegin */,ITTYPE /* ilen */> > part_stack;
            PIVOTE_SELECT pvt_alg;
            void part_quick(ITTYPE &ibegin, ITTYPE &iend) {
                const unsigned int ilen = std::distance(ibegin,iend);
                if(ilen <= pvt_alg.size()) {
                    // defer remaining sorting to insertion sort
                    for(ITTYPE i = ibegin+1; i < iend; ++i ) {
                        std::rotate(std::upper_bound(ibegin, i, *i), i, i+1);
                    }
                    return;
                }
                // otherwise select a pivote
                // select median of 3 as pivote
                ITTYPE pvt = pvt_alg(ibegin, iend);

                // for 3 way partition we take count-sort strategy
                unsigned int count[3]{0,0,0};
                // now count number of equal smaller and bigger keys
                for(ITTYPE i = ibegin; i != iend; ++i) {
                    if(*i < *pvt) {
                        count[0]++;
                    } else if(*i == *pvt) {
                        count[1]++;
                    } else {
                        count[2]++;
                    }
                }

                ITTYPE left = ibegin;
                ITTYPE right = ibegin+count[0]+count[1];
                ITTYPE middle = ibegin+count[0];

                // move pivote to middle
                if(*pvt != *middle) {
                    std::iter_swap(pvt, middle);
                    pvt = middle;
                }

#ifdef DEBUG_QUICK_SORT
                std::cout << *pvt << std::endl;
                for(ITTYPE i = ibegin; i != iend; ++i) {
                    std::cout << *i << ',';
                }
                std::cout << std::endl;
#endif // DEBUG_QUICK_SORT


                // make left partition
                for(ITTYPE i = left; i != (ibegin+count[0]);) {
                    if(*i < *pvt) {
                        i++; // already partitioned
                    } else if (*pvt < *i) {
                        for(;right != iend;right++) {
                            if(*pvt < *right) {
                                continue; // already in correct position
                            }
                            break;
                        }
                        assert(right != iend);
                        std::iter_swap(right,i);
                        right++;
                    } else { // in case *pvt == *i
                        for(;middle != (ibegin+count[0]+count[1]);middle++) {
                            if(*pvt == *middle) {
                                continue; // already in correct position
                            }
                            break;
                        }
                        assert(middle != (ibegin+count[0]+count[1]));
                        std::iter_swap(middle,i);
                        middle++;
                    }
                }


#ifdef DEBUG_QUICK_SORT
                for(ITTYPE i = ibegin; i != iend; i++) {
                    std::cout << *i << ',';
                }
                std::cout << std::endl;
#endif // DEBUG_QUICK_SORT

                // make the last partition
                for(ITTYPE i = right; i != iend;) {
                    // make last partition
                    if(*pvt < *i) {
                        // already in correct position
                        i++;
                        continue;
                    } else if (*i < *pvt) {
                        assert("Error unreachable statement!");
                    } else { // *pvt == *i
                        for(;middle != (ibegin+count[0]+count[1]);middle++) {
                            if(*pvt == *middle) {
                                continue; // already in correct position
                            }
                            break;
                        }
                        std::iter_swap(middle,i);
                        middle++;
                    }
                }


                // now add the partition into the stack
                if( count[0] > 1 ) {
                    part_stack.push_back(make_pair(ibegin,ibegin+count[0]));
                }
                if( count[2] > 1 ) {
                    part_stack.push_back(make_pair(ibegin+count[0]+count[1], iend));
                }
            }
        };
    }
}

#endif // ALGO_SORTING_QUICK_SORT_H

