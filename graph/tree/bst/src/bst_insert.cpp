#include "bst.h"

template <typename K>
int btnode<K>::insert(btnode<K>*node) {
	if(node->x < x) {
		if(left)
			return left->insert(node);
		//cout << "inserting left " << node->x << '\n';
		left = node;
		node->parent = this;
		return 0;
	}
	if(node->x == x) {
		if(equals)
			return equals->insert(node);
		equals = node;
		node->parent = equals;
		return 0;
	}
	if(right)
		return right->insert(node);
	//cout << "inserting right " << node->x << '\n';
	right = node;
	node->parent = this;
	return 0;
}


