
#include <queue>
#include <iostream>
#include <cstdio>
#include <math.h>

using namespace std;


vector<int> make_table(string word) {
	int i = 0;
	vector<int>tbl(word.size());
	if(word.size() > 0)
		tbl[0] = -1;
	if(word.size() > 1)
		tbl[1] = 0;
	// Theta(|word|)
	for(i = 1; i < word.size(); i++) {
		int matchlen = tbl[i-1];
		cout << matchlen << ':' << word[i];
		if(matchlen >= 0 && word[i] == word[matchlen])
			tbl[i] = matchlen+1;
		else
			tbl[i] = 0;
		cout << tbl[i] << '\n';
	}
	return tbl;
}

int search(const string sentence, const string word) {
	/* sanity check */
	if(sentence.size() < word.size())
		return -1;
	vector<int>tbl = make_table(word);
	int i = 0;
	int m = 0;
	// Theta(|sentence|)
	for(m = 0; (i+m) < sentence.size();) {
		if(word[i] == sentence[m+i]) {
			i++;
			if(i == word.size())
				return m;
		} else {
			if(tbl[i] == -1) {
				m += i+1;
				i = 0;
			} else {
				m += i-tbl[i];
				i = tbl[i];
			}
		}
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

