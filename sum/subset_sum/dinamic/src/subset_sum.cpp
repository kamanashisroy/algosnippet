
#include <string.h>
#include <map>
#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

static vector<int> find_set(const int n, const int sum, int*arr, const int index, map<int,vector<int> >&table, bool*found) {
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
	// see if the already precalculated
	map<int,vector<int> >::iterator it = table.find(sum);
	if(it != table.end()) { // precalculated
		*found = true;
		return it->second;
	} else { // not precalculated
		bool sub_found = false;
		vector<int> sub_elems = find_set(n, sum, arr, index+1, table, &sub_found);
		if(sub_found) {
			// save for future
			//table.insert(make_pair(sum, sub_elems)); // XXX Do I need this ? I think it is already done in recursion
			*found = true;
			return sub_elems;
		}
	}
	// add this element
	elems.push_back(index);
	// see if the already precalculated
	it = table.find(sum-arr[index]);
	if(it != table.end()) { // precalculated
		*found = true;
		return it->second;
	} else { // not precalculated
		bool sub_found = false;
		vector<int> sub_elems = find_set(n, sum-arr[index], arr, index+1, table, &sub_found);
		if(sub_found) {
			// save for future
			//table.insert(make_pair(sum-arr[index], sub_elems));
			elems.reserve(1+sub_elems.size());
			elems.insert(elems.end(), sub_elems.begin(), sub_elems.end());
			*found = true;
			table.insert(make_pair(sum, elems));
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
	map<int,vector<int> > table;
	bool found = false;
	vector<int> elems = find_set(n, sum, arr, 0, table, &found);
	if(!found) {
		cout << "subset NOT found\n";
		return 0;
	}
	cout << "subset found\n";
	vector<int>::iterator it;
	for(it=elems.begin();it<elems.end();it++) {
		cout << arr[*it] << ' ';
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

