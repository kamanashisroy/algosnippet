// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
merge_sort.h file is part of Algosnippet.
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

#ifndef ALGO_SORTING_MERGE_SORT_H
#define ALGO_SORTING_MERGE_SORT_H

#include <algorithm>
#include <vector>

namespace algo_snippet {
    namespace sorting {
        template <typename T>
        class merge_sort {
        private:
            //! \returns number of swap operation
            template <typename ittype>
            size_t merge_helper(ittype lbegin, ittype lend, ittype rbegin, ittype rend, std::vector<T>&temparr) {
                
                // copy to cache
                temparr.clear();
                // only cache the left bucket of data
                std::copy(lbegin,lend,back_inserter(temparr));
                
                
                ittype in_lbegin = temparr.begin();
                ittype in_lend = temparr.begin()+std::distance(lbegin,lend);
                
                size_t result = 0;
                
                ittype in_rbegin = rbegin;
                ittype in_rend = rend;
                
                // Now do the merge
                ittype outbegin = lbegin;
                while(in_rbegin < in_rend && in_lbegin < in_lend) {
                    ittype pos = upper_bound(in_lbegin,in_lend,*in_rbegin);
                    if(pos == in_lend) {
                        break;
                    }
                    
                    // copy left part
                    std::copy(in_lbegin,pos,outbegin);
                    outbegin += std::distance(in_lbegin,pos);
                    // right elements crossed the distance of distance(pos,in_lend)
                    result += std::distance(pos,in_lend);
                    in_lbegin = pos;

                    // pace one element from the right
                    *outbegin = *in_rbegin;
                    ++outbegin;
                    ++in_rbegin;
                }
                if(in_lbegin < in_lend) {
                    // copy left-over !
                    std::copy(in_lbegin,in_lend,outbegin);
                    outbegin += std::distance(in_lbegin,in_lend);
                    in_lbegin = in_lend; // indicate that we are done with left
                }
                #if false
                if(in_rbegin < in_rend) {
                    // copy right-over ! not needed !!
                    std::copy(in_rbegin,in_rend,outbegin);
                    outbegin += std::distance(in_rbegin,in_rend);
                    in_rbegin = in_rend; // indicate that we are done with left
                }
                #endif
                #if false
                cout << "merged ";
                for(ittype x = lbegin; x != rend; ++x) {
                    cout << *x << ' ';
                }
                cout << endl;
                #endif
                // assert(outbegin == rend);
                return result;
            }
        public:
            //! \brief Do merge sort on a vector data
            template <typename ittype>
            size_t sort(ittype ibegin, ittype iend) {
                const size_t input_size = std::distance(ibegin,iend);
                // Do bottom-up merge sort
                size_t result = 0;
                // make a cache
                std::vector<T> temparr;
                temparr.reserve(input_size>>1);

                // bottom-up divide and conquor
                for(size_t k = 1; k < input_size; k <<= 1) {
                    for(size_t i = 0; (i+k) < input_size; i+=(k<<1)) {
                        result += merge_helper(ibegin+i // left begin
                              , ibegin+i+k  // left end
                              , ibegin+i+k // right begin
                              , ibegin+std::min(i+k+k,input_size) // right end
                              , temparr);
                    }
                }
                return result;
            }
        }; // class merge_sort
    } // namespace sorting
} // namespace algo_snippet

#endif // ALGO_SORTING_MERGE_SORT_H
