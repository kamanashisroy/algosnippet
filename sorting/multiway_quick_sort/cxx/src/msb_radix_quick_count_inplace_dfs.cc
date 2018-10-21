// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
msb_radix_quick_count_inplace_dfs.cc file is part of Algosnippet.
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

#ifdef DEBUG_RADIX_SORT
#include <iostream>
#include <cassert>
#include "msb_radix_quick_count_inplace_dfs.h"
using namespace std;
using namespace algo_snippet::sorting;

void test_it() {
    msb_radix_quick_count_inplace_dfs alg;

    vector<string> content {"mississiippi", "banana", "manber", "myer", "boat", "aab", "aa", "a", "aaa", "aaaa"};
    vector<reference_wrapper<string> > sorted;

    sorted.reserve(content.size());
    copy(content.begin(),content.end(),back_inserter(sorted));

    alg.sort_string(sorted);
    cout << "Sorted string:" << endl;
    for(const string& x : sorted) {
        cout << x << ',';
    }
    cout << endl;
}

int main(int argc, char*argv[]) {
    test_it();
    cout << "successful " << endl;
    return 0;
}

#endif // DEBUG_RADIX_SORT

