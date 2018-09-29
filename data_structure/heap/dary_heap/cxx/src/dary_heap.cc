// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
dary_heap.cc file is part of Algosnippet.
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


#include <cstdlib>
#include <cassert>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <vector>


namespace algo_snippet {
    inline std::size_t dary_heap_parent(std::size_t i,std::size_t order) {
        return ((i+1) >> order)-1;
    }
    inline std::size_t dary_heap_child(std::size_t i,std::size_t order) {
        return (i << order)+1;
    }

    //! \brief builds heap of (1<<order)-ary heap in Theta(n) time
    template<const std::size_t order, typename KT>
    void make_dary_heap(std::vector<KT>& x) {
        static_assert(order != 0);
        // make bottom up heap Floyd's Theta(n) algorithm
        // starting from the leaf nodes
        for(std::size_t i = x.size()-1;i;--i) {

            // compare with the parent node
            const std::size_t pi = dary_heap_parent(i,order);
            if(x[pi] <= x[i]) { // check minheap property
                continue; // already a minheap
            }

            // fix the minheap property
            std::swap(x[pi],x[i]);

            // bubble down the minheap
            std::size_t ibubble = i;
            for(std::size_t ibegin = dary_heap_child(ibubble, order); ibegin < x.size(); ibegin = dary_heap_child(ibubble, order)) {
                // bubble down
                const std::size_t iend = ibegin+(1<<order);
                std::size_t imin = ibegin;
                for(std::size_t ii = ibegin+1; (ii < x.size()) && (ii < iend); ii++) {
                    if(x[imin] > x[ii]) {
                        imin = ii;
                    }
                }
                if(x[ibubble] <= x[imin]) {
                    // heap property holds
                    break;
                } else {
                    std::swap(x[imin],x[ibubble]);
                    ibubble = imin;
                }
            } // while
        } // for
    }
}

template<typename KT>
std::ostream& operator<<(std::ostream& ostrm, const std::vector<KT>&given) {
    ostrm << "[minheap:";
	for(const auto x : given) {
		ostrm << x << ',';
	}
    ostrm << ']';
    return ostrm;
}

using namespace algo_snippet;

int main(int argc, char*argv[]) {
    std::vector<int> hp = {10,9,8,7,6,5,4,3,2,1};
    make_dary_heap<1,int>(hp);
    std::cout << "Order 1=" << hp << std::endl;
    make_dary_heap<2,int>(hp);
    std::cout << "Order 2=" << hp << std::endl;
	std::cout << "Successful" << std::endl;
	return 0;
}

