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
    class disjoint_set {
    public:
        disjoint_set(size_t n_universe) : parent(n_universe),rank(n_universe) {
            for(size_t i=0; i<n_universe; i++) {
                parent[i] = i;
                rank[i] = 0;
            }
        }
        void make(size_t x) {
            parent[x] = x;
        }
        void join(size_t x, size_t y){
            x = find(x);
            y = find(y);
            if(x == y) {
                return;
            }

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
        size_t find(size_t x) {
            while(parent[x] != x) {
                const size_t oldx = x;
                x = parent[x];
                parent[oldx] = parent[x]; // path halving
            }
            return x;
        }
    private:
        std::vector<size_t> parent;
        std::vector<size_t> rank;
    };
} 

#define DEBUG
#ifdef DEBUG

#include <cassert>
#include <iostream>

using namespace algo_snippet;

int main(int argc, char*argv[]) {
    disjoint_set dset(100);
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
