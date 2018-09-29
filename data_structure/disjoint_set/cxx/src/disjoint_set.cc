// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
disjoint_set.cc file is part of Algosnippet.
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
#include <vector>


namespace algo_snippet {
    //! \tparam kint is a integer type, candidates are unsigned int, unsigned short, size_t
    template<typename kint>
    class disjoint_set {
    public:
        disjoint_set(kint n_universe) : parent(n_universe),rank(n_universe),n_subset(n_universe) {
            for(kint i=0; i<n_universe; i++) {
                parent[i] = i;
                rank[i] = 0;
            }
        }
        void make(kint x) {
            parent[x] = x;
        }
        void join(kint x, kint y){
            x = find(x);
            y = find(y);
            if(x == y) {
                return;
            }

            n_subset--;
            // check the rank and join
            if(rank[x] == rank[y]) {
                parent[y] = x;
                rank[x] += 1;
            } else if(rank[x] > rank[y]) {
                parent[y] = x;
            } else {
                parent[x] = y;
            }
        }
        kint find(kint x) {
            while(parent[x] != x) {
                const kint oldx = x;
                x = parent[x];
                parent[oldx] = parent[x]; // path halving
            }
            return x;
        }
        inline kint get_subset_count() const {
            return n_subset;
        }
    private:
        std::vector<kint> parent;
        std::vector<kint> rank;
        kint n_subset;
    };
} 

#define DEBUG
#ifdef DEBUG

#include <cassert>
#include <iostream>

using namespace algo_snippet;

int main(int argc, char*argv[]) {
    disjoint_set<uint8_t> dset(100);
    dset.make(1);
    dset.make(2);
    dset.join(1,2);
    dset.make(3);
    dset.make(4);
    dset.join(3,4);
    assert(dset.find(4) != dset.find(1));
    dset.join(2,3);
    assert(dset.find(4) == dset.find(1));
    std::cout << "Disjoint set test successful\n" << std::endl;
    return 0;
}

#endif // end DEBUG
