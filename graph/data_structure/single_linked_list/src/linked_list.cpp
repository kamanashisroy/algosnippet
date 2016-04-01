
#include <string.h>
#include <queue>
#include <iostream>
#include <sstream>
#include <cstdio>

using namespace std;

template <typename K>
struct SLList {
	K x;
	SLList*next;
	SLList(K given) : x(given), next(NULL) {}
	~SLList() {
		if(next) delete next;
	}
};

template <typename K>
struct SLListHead {
	SLList<K>*head;
	SLList<K>*tail;
	SLListHead() : head(NULL), tail(NULL) {}
	~SLListHead() {
		tail = NULL;
		if(head) delete(head);
	}
	void append(K given) {
		if(!tail || !head)
			head = tail = new SLList<K>(given);
		else {
			tail->next = new SLList<K>(given);
			tail = tail->next;
		}
	}
	void prepend(K given) {
		if(!tail || !head)
			head = tail = new SLList<K>(given);
		else {
			SLList<K>*new_head = new SLList<K>(given);
			new_head->next = head;
			head = new_head;
		}
	}
	template <typename T>
	void traverse(int (*cb)(T&data, K given), T&data) {
		SLList<K>*p = head;
		while(p) {
			cb(data, p->x);
			p = p->next;
		}
	}
};

static int dump_cb(stringstream&strm, int given) {
	strm << given << ' ';
	return 0;
}

static SLListHead<int> sum(SLListHead<int>&x, SLListHead<int>&y) {
	SLList<int>*p = x.head;
	SLList<int>*q = y.head;
	SLListHead<int> sum_list;
	int r = 0;
	while(p || q) {
		int sum = r;
		if(p) {
			sum += p->x;
			p = p->next;
		}
		if(q) {
			sum += q->x;
			q = q->next;
		}
		r = 0;
		if(sum > 9) {
			r = sum/10;
			sum = sum%10;
		}
		sum_list.prepend(sum);
	}
	return sum_list;
}

static int read_and_sum(const int n, const int m) {
	SLListHead<int>first;
	SLListHead<int>second;
	int i = n;
	while(i--) {
		int x;
		cin >> x;
		first.prepend(x);
	}
	i = m;
	while(i--) {
		int x;
		cin >> x;
		second.prepend(x);
	}
	// dump first
	stringstream first_strm;
	first.traverse(dump_cb, first_strm);
	cout << first_strm.str() << '\n';

	// dump second
	stringstream second_strm;
	second.traverse(dump_cb, second_strm);
	cout << second_strm.str() << '\n';


	SLListHead<int>sumlist = sum(first, second);
	stringstream sum_strm;
	sumlist.traverse(dump_cb, sum_strm);
	cout << sum_strm.str() << '\n';
	return 0;
}

int main(int argc, char*argv[]) {
	/* n is the number of elements in one linked list and m is the number of elements in second linked list */
	int n,m; 
	cin >> n >> m; 
	read_and_sum(n,m);
	return 0;
}

