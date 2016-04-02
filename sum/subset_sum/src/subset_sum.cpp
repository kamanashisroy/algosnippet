
#include <string.h>
#include <queue>
#include <iostream>
#include <cstdio>

using namespace std;

static int find_set(const int n, const int sum, int*arr, const int index, int*marker) {
	if(sum == 0) // base case 
		return 0;
	if(arr[index] == sum) {
		// cout << "found " << sum << '\n';
		marker[index] = 1;
		return 0;
	}
	if(index == n)
		return -1; // no solution
	int marker_backup[n];
	memcpy(marker_backup, marker, sizeof(marker_backup));
	if(find_set(n, sum, arr, index+1, marker) == 0) { // found
		return 0;
	}
	memcpy(marker, marker_backup, sizeof(marker_backup));
	marker[index] = 1;
	// cout << index << ',' << marker[index] << " finding " << (sum-arr[index]) << '\n';
	return find_set(n, sum-arr[index], arr, index+1, marker);
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
	int marker[n];
	memset(marker, 0, sizeof(marker));
	int ret = find_set(n, sum, arr, 0, marker);
	if(ret) {
		cout << "subset NOT found\n";
		return 0;
	}
	cout << "subset found\n";
	i = n;
	while(i--) {
		if(marker[i]) {
			cout << arr[i] << ' ';
		}
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

