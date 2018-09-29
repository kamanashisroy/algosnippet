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
#include <vector>


namespace algo_snippet {

    //! \brief dary heap has 2^order number of possible child of each node.
    //!
    //!     1) In that way the comparison has less cache-miss in cases
    //!        where the child nodes can all fit in the same cache.
    //!     2) It has less swap because the tree height is less than binary heap.

    inline std::size_t dary_heap_parent(std::size_t i,std::size_t order) {
        assert(i != 0);
        return ((i-1) >> order);
    }
    inline std::size_t dary_heap_child(std::size_t i,std::size_t order) {
        return (i << order)+1;
    }

    template<const std::size_t order, typename KT>
    void dary_heap_bubble_down(std::vector<KT>& x, std::size_t ibubble, const std::size_t isize) {
        static_assert(order != 0);
        if(x.size() <= 1) { // sanity check
            return; // no bubbling
        }

        // size limit
        assert(isize <= x.size());
        for(std::size_t ibegin = dary_heap_child(ibubble, order); ibegin < isize; ibegin = dary_heap_child(ibubble, order)) {
            // bubble down
            const std::size_t iend = ibegin+(1<<order);
            std::size_t imin = ibegin;
            for(std::size_t ii = ibegin+1; (ii < isize) && (ii < iend); ii++) {
                if(x[imin] <= x[ii]) {
                    continue;
                }
                imin = ii;
            }
            if(x[ibubble] <= x[imin]) {
                // heap property holds
                break;
            } else {
                std::swap(x[imin],x[ibubble]);
                ibubble = imin;
            }
        } // end bubble-down
    }

    //! \brief builds heap of (1<<order)-ary heap in Theta(n) time
    template<const std::size_t order, typename KT>
    void dary_heap_build(std::vector<KT>& x) {
        static_assert(order != 0);
        if(x.size() <= 1) { // sanity check
            return; // no bubbling
        }
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
            dary_heap_bubble_down<order,KT>(x, i, x.size());

        } // end for all
    }

    template<const std::size_t order, typename KT>
    void dary_heap_pop(std::vector<KT>& x) {
        static_assert(order != 0);
        if(x.size() <= 1) { // sanity check
            return; // no bubbling
        }

        // swap with last
        std::swap(x[0],x.back());

        // bubble down
        dary_heap_bubble_down<order,KT>(x, 0, x.size()-1/* skip bubbling the back() aka old root aka the min value */);
    }
}

#define DEBUG

#ifdef DEBUG

#include <iostream>
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

template<const std::size_t order>
int test_heap(std::vector<int>& hp) {
    // (2^order)-ary heap
    dary_heap_build<order,int>(hp);
    std::cout << "Order " << order << "=" << hp << std::endl;

    std::size_t hpsize = hp.size();
    for(std::size_t i = 0; i < hpsize; i++) {
        dary_heap_pop<order,int>(hp);
        std::cout << "Order " << order << " popped=" << hp.back() << std::endl;
        assert(hp.back() == (int)(i+1));
        std::cout << "Order " << order << "=" << hp << std::endl;
        hp.pop_back();
    }

    std::cout << "Successful" << std::endl;
    return 0;
}

int main(int argc, char*argv[]) {
    std::vector<int> hp1 = {10,9,8,7,6,5,4,3,2,1};
    test_heap<2>(hp1);
    std::vector<int> hp2 = {1,2,3,4,5,6,7,8,9,10};
    test_heap<4>(hp2);
    return 0;

#endif
}

