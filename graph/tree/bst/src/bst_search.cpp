#include "bst.h"

template <typename K>::btnode<K>*btnode<K>::search(K given) {
	if(x == given)
		return this;
	if(given < x) {
		if(!left) {
			return NULL;
		}
		return left->search(given);
	}
	if(!right) {
		return NULL;
	}
	return right->search(given);
}

template <typename K>::btnode<K>*btnode<K>::search_iterative(K given) {
	btnode*p = this;
	while(p) {
		if(p->x == given)
			return p;
		if(given < p->x) {
			p = p->left;
		} else {
			p = p->right;
		}
	}
	return NULL;
}


