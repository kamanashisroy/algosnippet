
#include <string.h>
#include <queue>
#include <iostream>
#include <cstdio>

using namespace std;

static vector<int> find_set(const int n, const int max_weight, int*vals, int*weights, int cum_vals, int*max_val, const int index) {
	vector<int> elem;
	if(max_weight == 0) // base case 
		return elem;
	if(weights[index] == max_weight) {
		// cout << "found " << sum << '\n';
		if((cum_vals + vals[index]) < *max_val)
			return elem;
		*max_val = cum_vals + vals[index];
		elem.push_back(index);
		return elem;
	}
	if(index == (n-1))
		return elem; // no more
	int one = *max_val;
	vector<int> subset1 = find_set(n, max_weight, vals, weights, cum_vals, &one, index+1);
	int other = *max_val;
	vector<int> subset2 = find_set(n, max_weight - weights[index], vals, weights, cum_vals + vals[index], &other, index+1);
	if(one >= other) {
		*max_val = one;
		elem.insert(elem.end(), subset1.begin(), subset1.end());
		return elem;
	} else {
		*max_val = other;
		elem.push_back(index);
		elem.insert(elem.end(), subset1.begin(), subset1.end());
		return elem;
	}
}

static int find_subset_to_max_val(const int n, const int max_weight) {
	int vals[n];
	int weights[n];
	int i = 0;
	// read the values
	i = n;
	while(i--) {
		cin >> vals[i];
	}

	// read the weights
	i = n;
	while(i--) {
		cin >> weights[i];
	}

	// sum
	int max_val = 0;
	vector<int> elems = find_set(n, max_weight, vals, weights, 0, &max_val, 0);
	vector<int>::iterator it;
	int sum_val = 0;
	int sum_weight = 0;
	for(it = elems.begin(); it < elems.end(); it++) {
		cout << '(' <<  *it << '=' << vals[*it] << ',' << weights[*it] << ')' << ' ';
		sum_val += vals[*it];
		sum_weight += weights[*it];
	}
	cout << '=' << ' ' << sum_val << ',' << sum_weight << '\n';
	return 0;
}

int main(int argc, char*argv[]) {
	/* n is the number of nodes and k is the number of edges */
	int n,max_weight; 
	cin >> n >> max_weight; 
	find_subset_to_max_val(n,max_weight);
	return 0;
}

