// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
msb_radix_quick_count_inplace_dfs.h file is part of Algosnippet.
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

#ifndef ALGO_SORTING_RADIX_SORT_H
#define ALGO_SORTING_RADIX_SORT_H

#include <algorithm>
#include <functional>
#include <vector>
#include <array>

namespace algo_snippet {
    namespace sorting {

        class msb_radix_quick_count_inplace_dfs {
        public:
            msb_radix_quick_count_inplace_dfs() {
            }

            void sort_string(std::vector<std::reference_wrapper<std::string> >& content) {
                is_placed.resize(content.size(),0);
                part_stack.push_back(std::make_tuple(0,0,content.size()));
                while(!part_stack.empty()) {
                    const auto& part = part_stack.back();
                    unsigned int k,ibegin,ilen;
                    std::tie(k,ibegin,ilen) = part;
                    part_stack.pop_back();
                    part_radix(content, k, ibegin, ilen);
                }
            }
        private:
            std::vector<std::tuple<unsigned int/* k */,unsigned int/* ibegin */,unsigned int /* ilen */> > part_stack;
            std::array<unsigned int, (256*2) > count_memo;
            std::vector<int> is_placed;

            inline unsigned int to_bucket(const std::string& x, unsigned int k) const {
                // this length correction sorts string in ascending length order
                unsigned int bid = 0;
                if(k < x.size()) {
                    bid = x[k];
                }
                bid <<= 1; // double
                bid += (x.size() > (k+1))?1:0;
                return bid;
            }

            void part_radix(std::vector<std::reference_wrapper<std::string> >& content, unsigned int k, unsigned int ibegin, unsigned int ilen) {

                const unsigned int iend = ibegin+ilen;
                #ifdef DEBUG_RADIX_SORT2
                std::cout << "sorting" << '(' << ibegin << ',' << (ilen) << ')' << std::endl;
                for(unsigned int i = ibegin; i < (ibegin+ilen); i++) {
                    std::cout << content[i].get() << ',';
                }
                std::cout << std::endl;
                #endif

                count_memo.fill(0);
                // Do bucket-counting
                for(unsigned int i = ibegin; i < iend; i++) {
                    std::string& x = content[i];
                    count_memo[to_bucket(x,k)]++;
                }

                for(unsigned int i = 1; i < count_memo.size(); i++) {
                    count_memo[i] += count_memo[i-1];
                    if(0 == (i&0x1)) {
                        // when the x.size() <= k
                        continue;
                    }
                    // make a partition for future sort
                    if((count_memo[i]-count_memo[i-1]) > 1) {
#ifdef DEBUG_RADIX_SORT2
                        std::cout << "Adding radix parts (" << ibegin+count_memo[i-1] << ',' << (count_memo[i]-count_memo[i-1]) << ')' << std::endl;
#endif
                        part_stack.push_back(std::make_tuple(k+1, ibegin+count_memo[i-1],count_memo[i]-count_memo[i-1]));
                    }
                }
#ifdef DEBUG_RADIX_SORT3
                for(unsigned int i = 0; i < count_memo.size(); i++) {
                    std::cout << "Memo [" << i << "]" << count_memo[i] << std::endl;
                }
#endif
                // is_placed is used for in-place count sort
                std::fill(is_placed.begin()+ibegin,is_placed.begin()+iend,0);
                unsigned int num_placed = 0;
                // now sort the buckets
                while(num_placed < ilen) {
                    // loop from start, this count sort is NOT stable
                    // TODO do stable-inplace count-sort
                    for(unsigned int i = ibegin; i < iend; i++) {
                        if(is_placed[i]) {
                            continue; // already placed
                        }
                        std::string& x = content[i];
                        unsigned int bid = to_bucket(x,k);
                        
#ifdef DEBUG_RADIX_SORT2
                        std::cout << "swapping [" << bid << "]" << count_memo[bid] << std::endl;
#endif
                        assert(count_memo[bid] > 0);
                        assert((ibegin+count_memo[bid]-1) < content.size());
                        // put content[i] at right place
                        std::swap(content[i],content[ibegin+count_memo[bid]-1]);
                        is_placed[ibegin+count_memo[bid]-1] = 1;
                        num_placed++;
                        count_memo[bid]--;
                    }
                }

                #ifdef DEBUG_RADIX_SORT2
                for(const std::string& x : content) {
                    std::cout << x << ',';
                }
                std::cout << std::endl;
                #endif
            }
        };
    }
}

#endif // ALGO_SORTING_RADIX_SORT_H

