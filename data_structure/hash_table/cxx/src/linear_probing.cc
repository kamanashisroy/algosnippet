// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
linear_probing.cc file is part of Algosnippet.
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

#include <cassert>
#include <vector>
#include "linear_probing.h"

using namespace algo_snippet::dict;
using namespace std;
 

#ifdef DEBUG_HASHTABLE

#include <cstdlib>
#include <iostream>
#include <random>

int main(int argc, char*argv[]) {
    size_t table_order = 10;
    size_t table_size = 1<<table_order;
    if(argc > 1) {
        table_size = atoi(argv[1]);
    }
    hash_table_linear_probing<hash_t> mytable(table_order,0);
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.000000001, 1);

    {
        hash_t x = 1001;
        hash_t& xout = x;
        mytable.insert(x,x);
        assert(true == mytable.search(x,xout));
        assert(x == 1001);
        x = 1002;
        assert(false == mytable.search(x,xout));
        x = 1001;
        assert(true == mytable.remove(x,xout));
        assert(false == mytable.search(x,xout));
    }

    for(size_t i = 0; i < table_size; i++) {
        hash_t x = dist(gen)*(1<<(table_order+2));
        mytable.insert(x,x);
        x = dist(gen);
        hash_t& xout = x;
        mytable.search(x,xout);
        x = dist(gen);
        mytable.remove(x,x);
    }
    cout << "successful " << endl;
    return 0;
}

#endif

