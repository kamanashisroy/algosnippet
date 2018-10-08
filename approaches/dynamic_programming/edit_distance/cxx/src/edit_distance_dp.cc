// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
edit_distance_dp.cc file is part of Algosnippet.
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
#include "edit_distance_dp.h"

#ifdef DEBUG_EDIT_DISTANCE
#include <iostream>
#include <cassert>
using namespace std;
using namespace algo_snippet::dynamic_programming;

int main(int argc, char*argv[]) {
    std::size_t dist = edit_distance::calc("forward", sizeof("forward")-1, "word", sizeof("word")-1);
    cout << "dist(forward,word) " << dist << endl;
    assert(4 == dist);
    dist = edit_distance::calc("kitten", sizeof("kitten")-1, "sitting", sizeof("sitting")-1);
    cout << "dist(kitten,sitting) " << dist << endl;
    assert(4 == dist);
    dist = edit_distance::calc("sitting", sizeof("sitting")-1, "kitten", sizeof("kitten")-1);
    cout << "dist(kitten,sitting) " << dist << endl;
    cout << "successful " << endl;
    return 0;
}

#endif // DEBUG_EDIT_DISTANCE

