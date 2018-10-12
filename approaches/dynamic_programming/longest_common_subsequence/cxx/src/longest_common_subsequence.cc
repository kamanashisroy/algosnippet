// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
longest_common_subsequence.cc file is part of Algosnippet.
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
#include "longest_common_subsequence.h"

#ifdef DEBUG_LONGEST_COMMON_SUBSEQUENCE
#include <iostream>
#include <cassert>
using namespace std;
using namespace algo_snippet::dynamic_programming;

void test_alg() {
    string x{"banana"};
    string y{"atana"};
    longest_common_subsequence alg(x.c_str(),x.size(),y.c_str(),y.size());
    int result = alg.calc();
    alg.print(cout);
    assert(4 == result);
}

int main(int argc, char*argv[]) {
    test_alg();
    cout << "successful " << endl;
    return 0;
}

#endif // DEBUG_LONGEST_COMMON_SUBSEQUENCE

