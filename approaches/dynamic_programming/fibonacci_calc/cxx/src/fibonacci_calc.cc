// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
fibonacci_calc.cc file is part of Algosnippet.
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
#include "fibonacci_calc.h"

#ifdef DEBUG_FIBONACCI
#include <iostream>
#include <cassert>
using namespace std;
using namespace algo_snippet;

int main(int argc, char*argv[]) {
    assert(1 == fibonacci_calc(0));
    assert(1 == fibonacci_calc(1));
    assert(2 == fibonacci_calc(2));
    assert(3 == fibonacci_calc(3));
    assert(5 == fibonacci_calc(4));
    assert(8 == fibonacci_calc(5));
    assert(13 == fibonacci_calc(6));
    assert(21 == fibonacci_calc(7));
    cout << "successful " << endl;
    return 0;
}

#endif // DEBUG_FIBONACCI

