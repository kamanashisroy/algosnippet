// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
bloom_filter.cc file is part of Algosnippet.
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
#include <array>
#include "bloom_filter.h"

using namespace algo_snippet::dict;
using namespace std;
 

#ifdef DEBUG_BLOOM_FILTER

#include <cstdlib>
#include <iostream>
#include <random>

    
int main(int argc, char*argv[]) {
    bloom_filter<hash_t,8> filter;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.000000001, 1);

    for(size_t i = 0; i < 10; i++) {
        hash_t x = dist(gen);
        filter.insert(x);
        assert(filter.contains(x));
    }
    cout << "successful " << endl;
    return 0;
}

#endif

