// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
manber_myer_dp.cc file is part of Algosnippet.
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

#ifdef DEBUG_MANBER_MYER
#include <iostream>
#include <cassert>
#include "manber_myer.h"
using namespace std;
using namespace algo_snippet::dynamic_programming;

void test_it(string&& input) {
    manber_myer alg(input);
    alg.sort_suffixes();

    for(unsigned int i = 0; i < input.size(); i++) {
        cout << alg.get_sorted_suffix(i) << ',';
    }
    cout << endl;
}

int main(int argc, char*argv[]) {
    test_it("mississippi");
    test_it("banana");
    cout << "successful " << endl;
    return 0;
}

#endif // DEBUG_MANBER_MYER

