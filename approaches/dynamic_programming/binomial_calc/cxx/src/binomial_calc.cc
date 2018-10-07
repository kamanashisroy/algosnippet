// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
binomial_calc.cc file is part of Algosnippet.
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
#include "binomial_calc.h"

#ifdef DEBUG_BINOMIAL
#include <iostream>
#include <cassert>
using namespace std;
using namespace algo_snippet;

/*
  Pascals_Triangle
  1
  1  1
  1  2  1
  1  3  3  1
  1  4  6  4  1
  1  5  10 10 5 1
 */

 

int main(int argc, char*argv[]) {
    assert(1 == binomial_calc(1,1));
    assert(2 == binomial_calc(2,1));
    assert(3 == binomial_calc(3,1));
    assert(4 == binomial_calc(4,1));
    assert(5 == binomial_calc(5,1));

    assert(1 == binomial_calc(2,2));
    assert(3 == binomial_calc(3,2));
    assert(6 == binomial_calc(4,2));
    assert(10 == binomial_calc(5,2));
 
    assert(1 == binomial_calc(3,3));
    assert(4 == binomial_calc(4,3));
    assert(10 == binomial_calc(5,3));

    assert(1 == binomial_calc(4,4));
    assert(5 == binomial_calc(5,4));

    cout << "successful " << endl;
    return 0;
}

#endif // DEBUG_BINOMIAL

