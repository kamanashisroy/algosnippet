// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
merge_sort.cc file is part of Algosnippet.
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

#ifdef TEST_MERGE_SORT
#include <iostream>
#include <cassert>
#include "merge_sort.h"
using namespace std;
using namespace algo_snippet::sorting;

void test_it() {

    vector<int> content {2,4,465,6,67,3,3,56,7,8,4,56};

    cout << "Sorting string:" << endl;
    for(const auto& x : content) {
        cout << x << ',';
    }
    cout << endl;

    merge_sort<int> alg;
    alg.sort(content.begin(), content.end());
    cout << "Sorted string:" << endl;
    for(const auto& x : content) {
        cout << x << ',';
    }
    cout << endl;
}

int main(int argc, char*argv[]) {
    test_it();
    cout << "successful " << endl;
    return 0;
}

#endif // TEST_MERGE_SORT


