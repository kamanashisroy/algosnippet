
This is binary search tree(BST) implementation as node and pointer. Note BST search can also be done in sorted array(TODO link).

The insertion, search, find minimum, find maxium, find successor, find predecessor takes **O(h)** time in binary search tree. 

#### Traversing BST in inorder

In-order bst traversal gives a sorted ordered traversal. Note that traversing the BST in in-order is **more specific from dfs** (TODO say how).

In-order traversal is easy to implement recursively. Note that recursion is an abstraction that makes things simple(abstraction principle/do not duplicate yourself).

```C++
template <typename K>
void btnode<K>::in_order_recursive(int (*cb)(K x)) {
	if(left)
		left->in_order(cb);
	cb(x);
	if(right)
		right->in_order(cb);
}
```

But the iterative version is non-trivial. It is hard to understand and implement. This is because of the boiler-plate code.

```C++
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
		btnode<K>*q = p->right; // go right only when popping up/ backtracking
		while(q) {
			pool.push(q);
			q = q->left;
		}

	}
}
```

There is another non-recursive solution.

```C++
template <typename K>
void btnode<K>::in_order_without_stack(int (*cb)(K x)) {
	btnode<K>*p = this->find_minimum();
	while(p) {
		cb(p->x);
		p = p->find_successor();
	}
}
```

#### Reconstructing/Deserializing a binary tree from in-order dump

This is kind of recursive and trivial. The only intelligence it needs is checking `strm.peek() != ','` and `strm.peek() != ')'`.
```C++
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
```

#### Finding the minimum and maxium

```C++
template <typename K>
btnode<K>*btnode<K>::find_minimum() {
	btnode*p = this;
	while(p->left) {
		p = p->left;
	}
	return p;
}

// recursive way
template <typename K>
btnode<K>*btnode<K>::find_maximum() {
	if(right)
		return right->find_maximum();
	return this;
}
```

#### Finding the successor, predecessor

Finding the predecessor and successor is tricky for binary search tree. But this logic is useful to balance the tree.

- Predecessor is the maximum of the left child if exists and otherwise it is the nearest ancestor where it branched to right.
```C++
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
```
- Successor is the minimum of the right child if exists and otherwise it is the nearest ancestor where it branched to left.
```C++
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
```

#### Removal of node

Removal is tricky. If the node has both right and left children then find the successor(right) and *transplant* it. Otherwise find the right/left and replace it.

```C++

static template <typename K>
btnode<K>*transplant(btnode<K>*root, btnode<K>*node, btnode<K>*next) {
	btnode<K>*nparent = node->parent;
	next->parent = nparent;
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
	return root;
}

template <typename K>
btnode<K>*btnode<K>::remove(btnode<K>*node) {
	btnode<K>*nparent = node->parent;
	if(node->right) {
		btnode<K>*next = node->right;
		if(node->left) {
			next = node->find_successor();
			cout << "Removing successor "<< next->x << endl;
			this->remove(next);
			next->left = node->left;
			next->right = node->right;
			assert(next != next->right);
			assert(next != next->left);
		}
		return transplant(this, node, next);
	} else if(node->left) {
		btnode<K>*next = node->left;
		return transplant(this, node, next);
	}
	if(nparent->left == node) {
		nparent->left = NULL;
	} else {
		nparent->right = NULL;
	}
	return this;
}

```

