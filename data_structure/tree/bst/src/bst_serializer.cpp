#include "bst.h"

template <typename K>
void btnode<K>::serialize(stringstream&strm) {
	strm << x << '(';
	if(left)
		left->serialize(strm);
	strm << ',';
	if(right)
		right->serialize(strm);
	strm << ')';
}

template <typename K>
void btnode<K>::deserialize(stringstream&strm) {
	char ch;
	strm  >> x >> ch;
	assert(ch == '(');
	if(strm.peek() != ',') {
		left = new btnode<int>(0);
		left->deserialize(strm);
	}
	strm >> ch;
	assert(ch == ',');
	if(strm.peek() != ')') {
		right = new btnode<int>(0);
		right->deserialize(strm);
	}
	strm >> ch;
	assert(ch == ')');
}


