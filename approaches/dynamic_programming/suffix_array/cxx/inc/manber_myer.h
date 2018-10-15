// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
manber_myer.h file is part of Algosnippet.
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

#ifndef ALGO_DYNAMIC_PROGRAMMING_MANBER_MYER_H
#define ALGO_DYNAMIC_PROGRAMMING_MANBER_MYER_H

#include <algorithm>
#include <functional>
#include <vector>

namespace algo_snippet {
    namespace dynamic_programming {

        // TODO omit -1 rank , use 0 instead
        class manber_myer {
        private:
            struct mm_suffix {
                int begin_rank;  // rank of the beginning half of the suffix
                int end_rank; // rank of the ending half of the suffix
                int idx;
                inline bool operator<(const mm_suffix&rhs) const {
                    // TODO do it without branching , we could use union and 64 bit int comparison
                    if(begin_rank == rhs.begin_rank) {
                        return end_rank < rhs.end_rank;
                    }
                    return begin_rank < rhs.begin_rank;
                }
            };
            struct suffix_less_than {
                inline bool operator()(const mm_suffix&lhs, const mm_suffix&rhs) {
                    return lhs < rhs;
                }
            };
        public:
            // Runtime: O(content.size())
            manber_myer(const std::string &content) : content(content),ordered_sfx(content.size()) {
                for(unsigned int i = 0; i < content.size(); i++) {
                    ordered_sfx[i].idx = i;
                    ordered_sfx[i].begin_rank = ordered_sfx[i].end_rank = 0; // no ranks yet
                }
            }
          
            // Runtime: O(content.size() * log (content.size())) on average
            void sort_suffixes() {
              
                // create rank table
                std::vector<int> rank_table(content.size());
                for(unsigned int i = 0; i < content.size(); i++) {
                    rank_table[i] = content[i] - 'a'; // Use the ascii as rank
                }
                suffix_less_than less_comp;
                sort(ordered_sfx.begin(), ordered_sfx.end(),less_comp);
              
                for(unsigned int step = 1,k = 1; k < content.size() ; k*=2, ++step) {
                  
                  
                    // build next level rank table from previous table
                    // bottom-up dynamic programming
                    for(unsigned int i = 0; i < ordered_sfx.size(); i++) {
                        mm_suffix& xfx = ordered_sfx[i];
                        xfx.begin_rank = rank_table[xfx.idx];
                        xfx.end_rank = ((xfx.idx+k) < content.size()) ? rank_table[xfx.idx+k] : -1;
                        // std::cout << "rank for " << content.substr(xfx.idx,k) << ':' << xfx.begin_rank << std::endl;
                    }
                    // do a sort here , we could do bucket sort which is asymptotically faster !
                    sort(ordered_sfx.begin(), ordered_sfx.end(), less_comp);

                    // update the rank
                    int currank = 0;
                    for(unsigned int i = 0; i < ordered_sfx.size(); i++) {
                        const mm_suffix& xfx = ordered_sfx[i];
                        if(i && less_comp(ordered_sfx[i-1],xfx)) {
                            currank++;
                        }
                        rank_table[xfx.idx] = currank;
                    }
                }
            }
            int get_sorted_suffix(int idx) const {
                return ordered_sfx[idx].idx;
            }
        private:
            const std::string &content;
            std::vector<mm_suffix> ordered_sfx;
        };
    }
}

#endif // ALGO_DYNAMIC_PROGRAMMING_MANBER_MYER_H

