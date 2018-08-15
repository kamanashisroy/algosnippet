#include "bst.h"

template <typename K>
btnode<K>::btnode(K given) : x(given),right(NULL),left(NULL),parent(NULL),equals(NULL) { }

template <typename K>
btnode<K>::~btnode() {
	if(equals) delete equals;
	if(left) delete left;
	if(right) delete right;
	//if(parent) delete parent;
}

template <typename K>
bool btnode<K>::check() {

	//cout << " Checking " << x << endl;
	if(right && (right->x <= x || right->parent != this || !right->check())) {
		return false;
	}
	if(left && (left->x >= x || left->parent != this || !left->check())) {
		return false;
	}
	return true;
}

