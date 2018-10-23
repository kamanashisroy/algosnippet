
#include <queue>
#include <iostream>
#include <cstdio>
#include <math.h>

using namespace std;

#include "kmp_old.h"


int main(int argc, char*argv[]) {
	string sentence;
	string word;
	cin >> sentence >> word;
	int pos = 0;
	if((pos = search(sentence, word)) != -1) {
		cout << "found " << pos << '\n';
	} else {
		cout << "not found\n";
	}
	return 0;
}

