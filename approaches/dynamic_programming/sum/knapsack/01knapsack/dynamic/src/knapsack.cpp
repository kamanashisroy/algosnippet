
#include <string.h>
#include <iostream>
#include <cstdio>
#include <map>
#include <vector>

using namespace std;

typedef pair<int,int> item_t;
typedef vector<item_t> item_v_t;
typedef pair<item_v_t::iterator,int> subprm_t;
typedef pair<item_v_t,int> soln_t;
typedef map<subprm_t,soln_t> db_t;

int debug = 0;
#define DOUT if(debug) cout

static soln_t maxSoln(soln_t&x, soln_t&y) {
	if(x.second > y.second)
		return x;
	return y;
}

static soln_t find_optimal_subproblem(item_v_t::iterator it, const item_v_t::iterator&end, const int max_weight, db_t&db) {
	item_v_t case1,case2;
	soln_t soln1(case1, 0);
	soln_t soln2(case2, 0);
	if(it >= end || max_weight <= 0) { // base case
		return soln1;
	}

	// find it in db
	auto soln = db.find(make_pair(it, max_weight));
	if(soln != db.end()) {
		DOUT << "precalculated" << endl;
		return soln->second;
	}

	item_t item = *it;
	it++;
	if(it == end) {
		if(item.second <= max_weight) {
			soln2.second = item.first;
			soln2.first.push_back(item);
			it--;
			db.insert(make_pair(make_pair(it,max_weight),soln2));
			return soln2;
		}
		it--;
		db.insert(make_pair(make_pair(it,max_weight), soln1));
		return soln1;
	}
	DOUT << "Looking for optimal subproblem " << max_weight << endl;
	
	soln1 = find_optimal_subproblem(it, end, max_weight, db);
	DOUT << "case 1 = " << soln1.second << endl;
	if(item.second < max_weight) {
		soln2 = find_optimal_subproblem(it, end, max_weight - item.second, db);
		soln2.second += item.first;
		soln2.first.push_back(item);
		DOUT << "case 2 = " << soln2.second << endl;
	}
	soln_t ret = maxSoln(soln1, soln2);
	it--;
	db.insert(make_pair(make_pair(it,max_weight), ret));
	return ret;
}

static item_v_t read_items(const int n) {
	int i = n;
	int price = 0, weight = 0;
	item_v_t items;
	while(i--) {
		cin >> price >> weight;
		items.push_back(make_pair(price, weight));
	}
	return items;
}

int main(int argc, char*argv[]) {
	/* n is the number of nodes and max_weight is the capacity of the sack */
	int n,max_weight; 
	cin >> n >> max_weight; 

	/* read all the pairs */
	item_v_t items = read_items(n);

	/* find the optimal subproblem */
	db_t db;
	soln_t soln = find_optimal_subproblem(items.begin(), items.end(), max_weight, db);

	/* show the output */
	cout << soln.second << endl;
	for(auto item : soln.first)
		cout << item.first << ' ' << item.second << endl;
	
	return 0;
}

