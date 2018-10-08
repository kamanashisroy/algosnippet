// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
longest_increasing_subsequence_dp.cc file is part of Algosnippet.
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
#include "longest_increasing_subsequence_dp.h"

#ifdef DEBUG_LONGEST_INCREASING_SUBSEQUENCE
#include <iostream>
#include <cassert>
using namespace std;
using namespace algo_snippet::dynamic_programming;

int main(int argc, char*argv[]) {
    int input1[]{12,23,34,45,56,32,4};
    longest_increasing_subsequence::calc(input1, 7);
    cout << "successful " << endl;
    return 0;
}

#endif // DEBUG_LONGEST_INCREASING_SUBSEQUENCE

