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

template <typename K>
btnode<K>*btnode<K>::remove(btnode<K>*node) {
	btnode<K>*nparent = node->parent;
	if(node->right) {
		btnode<K>*next = node->find_successor();
		cout << "Removing successor "<< next->x << endl;
		this->remove(next);
		next->parent = nparent;
		next->left = node->left;
		next->right = node->right;
		assert(next != next->right);
		assert(next != next->left);
		assert(next != next->parent);
		if(nparent == NULL) {
			return next;
		}
		if(nparent->right == node) {
			nparent->right = next;
		} else {
			nparent->left = next;
		}
		cout << "deletion complete" << endl;
		return this;
	} else if(node->left) {
		btnode<K>*next = node->find_predecessor();
		cout << "removing predecessor " << next->x << endl;
		this->remove(next);
		next->parent = nparent;
		next->right = node->right;
		next->left = node->left;
		assert(next != next->right);
		assert(next != next->left);
		assert(next != next->parent);
		if(nparent == NULL) {
			return next;
		}
		if(nparent->left == node) {
			nparent->left = next;
		} else {
			nparent->right = next;
		}
		cout << "deletion complete" << endl;
		return this;
	}
	if(nparent->left == node) {
		nparent->left = NULL;
	} else {
		nparent->right = NULL;
	}
	return this;
}



