// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
bellman_ford_dp.cc file is part of Algosnippet.
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

#ifdef DEBUG_BELLMAN_FORD
#include <iostream>
#include <cassert>
#include "bellman_ford.h"
using namespace std;
using namespace algo_snippet::dynamic_programming;

void test_it(bool neg_cycle) {
    bellman_ford<int,int> alg(10);
    alg.add_edge(1,2,3);
    alg.add_edge(1,3,2);
    alg.add_edge(1,4,6);
    alg.add_edge(2,2,1);
    alg.add_edge(3,6,(neg_cycle?-20:4));
    alg.add_edge(2,6,(neg_cycle?-20:4));
    assert((!neg_cycle)==alg.calc(1));
    alg.dump(cout);
}

int main(int argc, char*argv[]) {
    //test_it(true);
    test_it(false);
    cout << "successful " << endl;
    return 0;
}

#endif // DEBUG_BELLMAN_FORD

