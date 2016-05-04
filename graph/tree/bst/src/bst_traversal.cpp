#include "bst.h"
#include <stack>

template <typename K>
void btnode<K>::in_order(int (*cb)(K x)) {
	stack<btnode<K>*> pool;
	btnode<K>*p = this;
	while(p) {
		pool.push(p);
		p = p->left; // go left
	}
	while(pool.size()) {
		p = pool.top();
		pool.pop();
		cb(p->x);
		btnode<K>*q = p->right; // go right only when popping up
		while(q) {
			pool.push(q);
			q = q->left;
		}

	}
}

template <typename K>
void btnode<K>::in_order_recursive(int (*cb)(K x)) {
	if(left)
		left->in_order(cb);
	cb(x);
	if(right)
		right->in_order(cb);
}

