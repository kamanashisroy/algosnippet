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
