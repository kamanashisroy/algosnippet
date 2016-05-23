
This is AVL tree implementation.

AVL tree is faster than Red-Black tree when the search is more than insertion/deletion.

#### height augmentation

The AVL tree keeps an extra property of the node. It is the heght of the node.

- Height is defined as the longest path to the leaf. So the height of a leaf is 0.
- Height of an internal node is max(height of children)

```C++
	void fixHeight() {
		height = 0;
		if(right && (right->height > (height-1))) {
			height = right->height+1;
		}
		if(left && (left->height > (height-1))) {
			height = left->height+1;
		}
		//cout << " height of " << key << " is " << height << endl;
		if(parent)
			parent->fixHeight();
	}
```


#### Rotation

The rotation always changes the height of the sub-tree except in zig-zag condition. In zig-zag we need to straighted up the right/left child before rotation.

Here is a right rotation example.

```C++
	AVLNode*rotateRight() {
		assert(left != NULL);
		//cout << " rotating right " << key << endl;
		AVLNode*head = left;
		head->parent = this->parent;
		if(parent) {
			if(parent->right == this)
				parent->right = head;
			else
				parent->left = head;
		}

		// transplant left
		left = head->right;
		if(left)
			left->parent = this;

		// transplant right
		head->right = this;
		this->parent = head;

		// fix height property
		fixHeight();
		return head;
	}
```

Note that after rotation the head is changed.

#### Handling zigzag.

To balance the height of AVL-tree we need to take care of zig-zag and make the tangle straight.

```C++
	if(!right->right && right->left) { // if it is a tangle
		right->rotateRight(); // make it straight.
	}
```

So the AVL-tree fixing is the following.

```C++
	AVLNode*fixAVLProperty() {
		int rheight = (right?right->height:-1);
		int lheight = (left?left->height:-1);
		int diff = lheight - rheight;
		AVLNode*head = this;

		//cout << " checking avl property for " << key << " the diff is " << diff << endl;
		/* check AVL condition */
		if(diff == 1 || diff == -1 || diff == 0)
			return head; // no worry

		if(diff > 0) { /* if left tree is too deep */
			if(!left->left && left->right) { // if the left child has no more left child and if there is right child
				left->rotateLeft(); // so the left child has only left child (no right child), kind of straight line
			}
			head = rotateRight(); // rotate it right to lower the left height
		} else { /* right tree is too deep */
			if(!right->right && right->left) { // if it is a tangle
				right->rotateRight(); // make it straight.
			}
			head = rotateLeft(); // now rotate left to lower the right height
		}
		return head;
	}
```

#### Insertion

Insertion is same as binary search tree except it needs additional steps of updating the hegiht property and tree balancing.

#### Deletion

TODO


