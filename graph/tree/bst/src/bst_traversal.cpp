#include "bst.h"

template <typename K>
void btnode<K>::in_order(int (*cb)(K x)) {
	if(left)
		left->in_order(cb);
	cb(x);
	if(right)
		right->in_order(cb);
}

