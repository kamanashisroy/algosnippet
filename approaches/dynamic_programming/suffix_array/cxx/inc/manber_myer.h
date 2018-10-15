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
            struct manber_suffix {
              int begin_rank;  // rank of the beginning half of the suffix
              int end_rank; // rank of the ending half of the suffix
              int idx;
              bool operator<(const manber_suffix&rhs) const {
                  // TODO do it without branching , we could use union and 64 bit int comparison
                  if(begin_rank == rhs.begin_rank) {
                      return end_rank < rhs.end_rank;
                  }
                  return begin_rank < rhs.begin_rank;
              }
            };
        public:
            // Runtime: O(content.size())
            manber_myer(const std::string &content) : content(content),sfx(content.size()) {
                for(unsigned int i = 0; i < content.size(); i++) {
                    sfx[i].idx = i;
                    sfx[i].begin_rank = content[i] - 'a'; // Use the ascii as rank
                    // XXX what is the right rank ??
                    sfx[i].end_rank = ((i+1) < content.size() ? (content[i+1] - 'a') : -1);
                }
            }
          
            // Runtime: O(content.size() * log (content.size())) on average
            void sort_suffixes() {
              
                // XXX is that better to sort the reference(like the lookup table) to reduce amount of data-copy ?
              
                // lookup table for suffix-data
                std::vector<std::reference_wrapper<struct manber_suffix> > sfx_map;
                sfx_map.reserve(content.size());
                std::copy(sfx.begin(),sfx.end(),std::back_inserter(sfx_map));
              
                // create rank table
                std::vector<int> rank_table(content.size());
                for(unsigned int i = 0; i < content.size(); i++) {
                    rank_table[i] = sfx[i].begin_rank;
                }
                sort(sfx.begin(),sfx.end());
              
                for(unsigned int step = 1,k = 1; k < content.size() ; k*=2, ++step) {
                    int currank = 0;
                  
                    // build next level rank table from previous table
                    // bottom-up dynamic programming
                    for(unsigned int i = 0; i < content.size(); i++) {
                        if(i && sfx[i-1] < sfx[i]) {
                            currank++;
                        }
                        sfx[i].begin_rank = currank;
                        sfx[i].end_rank = ((i+k) < content.size()) ? rank_table[sfx_map[i+k].get().idx] : -1;
                    }
                    // do a sort here , we could do bucket sort which is asymptotically faster !
                    sort(sfx.begin(),sfx.end());
                    // update the rank
                    for(unsigned int i = 0; i < content.size(); i++) {
                        rank_table[i] = sfx_map[i].get().begin_rank;
                    }
                }
            }
            int get_sorted_suffix(int idx) const {
                return sfx[idx].idx;
            }
        private:
            const std::string &content;
            std::vector<manber_suffix> sfx;
        };
    }
}

#endif // ALGO_DYNAMIC_PROGRAMMING_MANBER_MYER_H

