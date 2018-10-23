// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
kmp.c file is part of Algosnippet.
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

#include "kmp.h"

#include <iostream>

using namespace std;
using namespace algo_snippet::string;

int main(int argc, char*argv[]) {
	string sentence;
	string word;
	cin >> sentence >> word;
    kmp alg(word);
	int pos = 0;
	if((pos = alg.search(sentence)) != -1) {
		cout << "found " << pos << '\n';
	} else {
		cout << "not found\n";
	}
	return 0;
}
