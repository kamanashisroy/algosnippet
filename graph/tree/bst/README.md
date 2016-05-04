
This is binary search tree(BST) implementation as node and pointer. Note BST search can also be done in sorted array(TODO link).

The insertion, search, find minimum, find maxium, find successor, find predecessor takes **O(h)** time in binary search tree. 

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

template <typename K>
btnode<K>*btnode<K>::find_maximum() {
	btnode*p = this;
	while(p->right) {
		p = p->right;
	}
	return p;
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

