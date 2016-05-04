#include "bst.h"

template <typename K>
btnode<K>*btnode<K>::find_minimum() {
	btnode*p = this;
	while(p->left) {
		p = p->left;
	}
	return p;
}

template <typename K>
btnode<K>*btnode<K>::find_maximum() {
	btnode*p = this;
	while(p->right) {
		p = p->right;
	}
	return p;
}

template <typename K>
btnode<K>*btnode<K>::find_successor() {
	btnode*p = this;
	if(p->right)
		return p->right->find_minimum();
	else while(p->parent) {
		if(p == p->parent->left)
			return p->parent;
		p = p->parent;
	}
	return NULL;
}

template <typename K>
btnode<K>*btnode<K>::find_predecessor() {
	btnode*p = this;
	if(p->left)
		return p->left->find_maximum();
	else while(p->parent) {
		cout << " traversing " << p->x << ", parent is " << p->parent->x << endl;
		if(p == p->parent->right)
			return p->parent;
		p = p->parent;
	}
	return NULL;
}


