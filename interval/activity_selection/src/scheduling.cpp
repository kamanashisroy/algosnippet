
#include <string.h>
#include <queue>
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef pair<int,int> evt_t;
/**
 * @brief vector<pair<start,end> >
 */
typedef vector<pair<int,int> > evt_list_t;

evt_list_t read_pairs(const int n) {
	int i = n;
	int start = 0, end = 0;
	evt_list_t evts;
	while(i--) {
		cin >> start >> end;
		evts.push_back(make_pair(start,end));
	}
	return evts;
}

bool compare_evt(evt_t x, evt_t y) {
	return x.second < y.second;
}

evt_list_t find_maximum_n_of_disjoints(evt_list_t::iterator begin, evt_list_t::iterator end) {
	evt_list_t devts;
	
	int finish = 0;
	if(begin < end) {
		evt_t evt = *begin;
		devts.push_back(evt);
		finish = evt.second;
	}
	for(begin++;begin < end;begin++) {
		if(begin->first < finish) {
			continue;
		}
		evt_t evt = *begin;
		devts.push_back(evt);
		finish = evt.second;
	}
	return devts;
}

int main(int argc, char*argv[]) {
	/* n is the number of pairs */
	int n; 
	cin >> n; 

	/* read all the intervals/pairs */
	evt_list_t evts = read_pairs(n);

	/* sort all the events by finishing time */
	sort(evts.begin(), evts.end(), compare_evt);

	/* find maximum disjoints */
	evt_list_t devts = find_maximum_n_of_disjoints(evts.begin(), evts.end());

	/* print disjoint intervals */
	for(auto evt : devts) {
		cout << evt.first << " " << evt.second << endl; 
	}
	cout << "total " << devts.size() << " events" << endl;
	return 0;
}

