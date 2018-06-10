
#include <string.h>
#include <queue>
#include <iostream>
#include <cstdio>
#include <assert.h>

using namespace std;

template <typename K>
struct AVLNode {
	K key;
	int height;
	AVLNode*right;
	AVLNode*left;
	AVLNode*equals;
	AVLNode*parent;

	AVLNode(K given) : key(given),height(0),right(NULL),left(NULL),equals(NULL),parent(NULL) { }

	/**
	 * The AVL tree keeps an extra property of the node. It is the heght of the node.
	 * 
	 * - Height is defined as the longest path to the leaf. So the height of a leaf is 0.
	 * - Height of an internal node is max(height of children)
	 */
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

	AVLNode*rotateLeft() {
		assert(right != NULL);
		//cout << " rotating left " << key << endl;
		AVLNode*head = right;
		head->parent = this->parent;

		if(parent) {
			//cout << " adding link to parent " << parent->key << endl;
			if(parent->right == this)
				parent->right = head;
			else
				parent->left = head;
		}

		// transplant right
		right = head->left;
		if(right)
			right->parent = this;

		// transplant head->left
		head->left = this;
		this->parent = head;

		// fix height property
		fixHeight();

		return head;
	}

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

	AVLNode*insert(K aKey) {
		if(aKey < key) {
			if(left)
				left->insert(aKey);
			else {
				left = new AVLNode(aKey);
				left->parent = this;
				fixHeight();
			}
		} else if(key == aKey) {
			if(equals)
				return equals->insert(aKey);
			else
				equals = new AVLNode(aKey);
			return this;
		} else {
			if(right)
				right->insert(aKey);
			else {
				right = new AVLNode(aKey);
				right->parent = this;
				fixHeight();
			}
		}
		//cout << "inserted " << aKey << endl;
		return fixAVLProperty();
	}

	AVLNode*search(K given) {
		if(key == given)
			return this;
		if(given < key) {
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
	// TODO remove node

	void dump() { // prints tree in preorder
		cout << key << '(';
		if(left)
			left->dump();
		cout << ',';
		if(right)
			right->dump();
		cout << ')';
	}

	~AVLNode() {
		if(equals) delete equals;
		if(left) delete left;
		if(right) delete right;
	}

	void in_order(int (*cb)(K key)) { // traverses tree in in-order
		if(left)
			left->in_order(cb);
		cb(key);
		if(right)
			right->in_order(cb);
	}
};

template <typename K>
static int in_order_dump_cb(K key) {
	cout << key << ',';
	return 0;
}

static int read_input_and_build_tree_and_search(const int n, const int x) {
	AVLNode<int>*root = NULL;
	int i = n;
	while(i--) {
		int r = 0;
		cin >> r;
		if(!root)
			root = new AVLNode<int>(r);
		else {
			AVLNode<int>*new_root = root->insert(r);
			if(new_root)
				root = new_root;
		}
	}
	root->dump();
	cout << '\n';
	root->in_order(in_order_dump_cb);
	cout << '\n';
	if(root->search(x) != NULL) {
		cout << "found " << x << '\n';
	} else {
		cout << "not found " << x << '\n';
	}
	if(root)
		delete root;
	return 0;
}

int main(int argc, char*argv[]) {
	/* n is the number of nodes and k is the number of edges */
	int n,x; 
	cin >> n >> x;
	read_input_and_build_tree_and_search(n,x);
	return 0;
}

