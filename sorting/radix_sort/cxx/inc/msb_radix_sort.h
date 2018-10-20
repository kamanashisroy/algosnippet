// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
msb_radix_sort.h file is part of Algosnippet.
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

        class msb_radix_sort {
        public:
            msb_radix_sort() {
            }

            void sort_string(std::vector<std::reference_wrapper<std::string> >& content) {
                part_stack[0].push_back(std::make_pair(0,content.size()));
                for(unsigned int step = 1, k = 0; !part_stack[(step+1)&1].empty();++step,++k) {
                    part_radix(content, step, k);
                }
            }
        private:
            std::array<std::vector<std::pair<unsigned int,unsigned int> >,2> part_stack;
            std::array<std::vector<std::reference_wrapper<std::string> >, (256*2) > bucket;

            void part_radix(std::vector<std::reference_wrapper<std::string> >& content, unsigned int step, unsigned int k) {

                // run bucket sort for each partition
                for(const auto& ipart : part_stack[(step+1)&1]) {

                    const unsigned int ibegin = ipart.first, ilen = ipart.second;
                    #ifdef DEBUG_RADIX_SORT2
                    std::cout << "sorting" << std::endl;
                    for(unsigned int i = ibegin; i < (ibegin+ilen); i++) {
                        std::cout << content[i].get() << ',';
                    }
                    std::cout << std::endl;
                    #endif

                    // Do bucketing
                    for(unsigned int i = ibegin; i < (ibegin+ilen); i++) {
                        std::string& x = content[i];

                        // this length correction sorts string in ascending length order
                        unsigned int bid = 0;
                        if(k < content.size()) {
                            bid = x[k];
                        }
                        bid <<= 1; // double
                        bid += (content.size() > k)?1:0;
                        bucket[bid].push_back(x);
                    }

                    // now sort the buckets
                    unsigned int j = ibegin;
                    for(auto& xbucket : bucket) {
                        unsigned int part_start = j;
                        for(const auto& x : xbucket) {
                            content[j++] = x;
                            if(x.get().size() < (k+1)) { // already in sorted position
                                // avoid sorting x
                                if((j-part_start) > 1) {
#ifdef DEBUG_RADIX_SORT2
                                    std::cout << "Adding radix parts (" << part_start << ',' << (j-part_start) << ')' << std::endl;
#endif
                                    part_stack[step&1].push_back(std::make_pair(part_start,j-part_start));
                                }
                                // go for next partition by avoiding this one
                                part_start = j;
                            }
                        }
                        if((j-part_start) > 1) {
#ifdef DEBUG_RADIX_SORT2
                            std::cout << "Adding radix parts (" << part_start << ',' << (j-part_start) << ')' << std::endl;
#endif
                            part_stack[step&1].push_back(std::make_pair(part_start,j-part_start));
                        }
                        xbucket.clear();
                    }
                }
                part_stack[(step+1)&1].clear();

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

