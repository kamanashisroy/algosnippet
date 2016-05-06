
#include <string.h>
#include <map>
#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

typedef unsigned long long k_t;
typedef map<k_t,vector<int> > soln_t;

k_t get_key(const int sum, const int index) {
	k_t key = sum << 8;
	key &= 0xFFFF00;
	key |= index;
	return key;
}

static vector<int> find_set(const int n, const int sum, int*arr, const int index, soln_t&table, bool*found) {
	vector<int> elems;
	if(sum == 0) { // base case, it is not reached unless the total sum == 0
		*found = true;
		return elems;
	}
	if(arr[index] == sum) {
		*found = true;
		elems.push_back(index);
		table.insert(make_pair(sum, elems)); // save for future use
		return elems;
	}
	if(index == (n-1)) {
		*found = false; // XXX should no solutions needs to be precalculated or memoized ?
		return elems; // no solution
	}
	k_t key = get_key(sum, index);
	// see if the already precalculated
	auto it = table.find(key);
	if(it != table.end()) { // precalculated
		*found = true;
		return it->second;
	} else { // not precalculated
		bool sub_found = false;
		vector<int> sub_elems = find_set(n, sum, arr, index+1, table, &sub_found);
		if(sub_found) {
			// save for future
			table.insert(make_pair(key, sub_elems)); // XXX Do I need this ? I think it is already done in recursion
			*found = true;
			return sub_elems;
		}
	}
	// add this element
	elems.push_back(index);
	// see if the already precalculated
	key = get_key(sum-arr[index], index);
	it = table.find(key);
	if(it != table.end()) { // precalculated
		*found = true;
		// TODO check if it used the any of the index from [0,index] if so then disregard the result.
		return it->second;
	} else { // not precalculated
		bool sub_found = false;
		vector<int> sub_elems = find_set(n, sum-arr[index], arr, index+1, table, &sub_found);
		if(sub_found) {
			// save for future
			elems.reserve(1+sub_elems.size());
			elems.insert(elems.end(), sub_elems.begin(), sub_elems.end());
			*found = true;
			table.insert(make_pair(key, elems));
			//cout << "subproblem solved(" << arr[index] << ',' << sum-arr[index] << ")\n";
			return elems;
		}
	}
	return elems;
}

static int find_subset_for_sum(const int n, const int sum) {
	int arr[n];
	int i = 0;
	// read the input
	i = n;
	while(i--) {
		cin >> arr[i];
	}

	// sum
	soln_t table;
	bool found = false;
	vector<int> elems = find_set(n, sum, arr, 0, table, &found);
	if(!found) {
		cout << "subset NOT found\n";
		return 0;
	}
	cout << "subset found\n";
	for(auto it : elems) {
		cout << arr[it] << ' ';
	}
	cout << '\n';
	return 0;
}

int main(int argc, char*argv[]) {
	/* n is the number of nodes and k is the number of edges */
	int n,sum; 
	cin >> n >> sum; 
	find_subset_for_sum(n,sum);
	return 0;
}

