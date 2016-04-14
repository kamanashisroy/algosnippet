
#include <queue>
#include <iostream>
#include <cstdio>
#include <math.h>

using namespace std;

#define ROLLING_BASE 101
typedef long long hash_t;

hash_t rolling_hash(string x) {
	hash_t hash = 0;
	int i = 0;
	for(i = 0; i < x.size(); i++) {
		hash += x[i]*pow(ROLLING_BASE,(x.size()-i-1));
	}
	//cout << x << " hashcode " << hash << '\n';
	return hash;
}

hash_t rolling_hash_inc(string x, int start, int len, hash_t old_hash) {
	//cout << "subtracting " << x[start] << '\n';
	hash_t val = x[start]*pow(ROLLING_BASE,len-1);
	//cout << " -- rolling " << old_hash << '-' << val << '\n';
	old_hash = old_hash - val;
	old_hash = old_hash*ROLLING_BASE;
	//cout << "adding " << x[start+len] << '\n';
	old_hash += x[start+len];
	//cout << "rolling " << old_hash << '\n';
	return old_hash;
}

int search(const string sentence, const string word) {
	/* sanity check */
	if(sentence.size() < word.size())
		return -1;
	hash_t hash = rolling_hash(word);
	hash_t rhash = rolling_hash(sentence.substr(0, word.size()));
	int i = 0;
	for(i = 0; (i+word.size()) <= sentence.size();i++,rhash = rolling_hash_inc(sentence, i-1, word.size(), rhash)) {
		if((rhash - hash) == 0 && word.compare(sentence.substr(i, word.size())) == 0)
			return i;

	}
	return -1;
}

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

