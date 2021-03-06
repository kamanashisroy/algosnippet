

vector<int> make_table(string word) {
	int i = 0;
	vector<int>tbl(word.size());
	if(word.size() > 0)
		tbl[0] = -1;
	if(word.size() > 1)
		tbl[1] = 0;
	// Theta(|word|)
	for(i = 1; i < (int)word.size(); i++) {
		int matchlen = tbl[i-1];
		//cout << " matchlen( " << word[i-1] << " ) = " << matchlen << endl;
		if(matchlen >= 0 && word[i] == word[matchlen])
			tbl[i] = matchlen+1;
		else
			tbl[i] = 0;
		cout << " matchlen( " << word[i] << " ) = " << tbl[i] << endl;
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
	for(m = 0; (i+m) < (int)sentence.size();) {
		if(word[i] == sentence[m+i]) {
			i++;
			if(i == (int)word.size())
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
