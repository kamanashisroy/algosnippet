
#include <string.h>
#include <queue>
#include <iostream>
#include <cstdio>
#include <assert.h>

using namespace std;

template <typename K>
struct RBNode {
	K x;
	bool is_black;
	RBNode*right;
	RBNode*left;
	RBNode*equals;

	RBNode(K given) : x(given),is_black(true),right(NULL),left(NULL),equals(NULL) { }

	RBNode*fixup_uncle(RBNode*grand_child, bool is_same_side_as_uncle, RBNode*uncle) {
		if(uncle && !uncle->is_black) { // if parent and uncle is red
			// wikipedia case 3
			// color flip
			is_black = false;
			right->is_black = true;
			left->is_black = true;
			//grand_child->is_black = false;
		} else if(uncle && uncle->is_black) { // uncle is black
			if(is_same_side_as_uncle) {
				// wikipedia case 4
				// needs rotation
				if(uncle == left) {
					grand_child->right = right;
					right = grand_child;
					grand_child->right->left = NULL;
				} else {
					grand_child->left = left;
					left = grand_child;
					grand_child->left->right = NULL;
				}
			} else {
				// wikipedia case 5
				if(uncle == left) {
					// rotate parent and grand parent
					assert(right->left == NULL);
					right->left = this; // grand parent is now child of parent
					// color flip
					is_black = false; // this grand parent is red
					right->is_black = true; // parent is black
					RBNode*ret = right;
					right = NULL; 
					return ret; // return parent as grand parent
				} else {
					assert(left->right = NULL);
					left->right = this;
					is_black = false;
					left->is_black = true;
					RBNode*ret = left;
					left = NULL;
					return ret;
				}
			}
		}
		return NULL;
	}

	RBNode*insert(RBNode*node, RBNode*parent) {
		if(node->x < x) {
			if(left) {
				RBNode*nparent = left->insert(node, this);
				if(nparent != NULL) {
					if((nparent->right == right) || (nparent->left == right)) {
						right = nparent;
						return NULL;
					}
					if((nparent->right == left) || (nparent->left == left)) {
						left = nparent;
						return NULL;
					}
					return nparent;
				}
				return NULL;
			}
			//cout << "inserting left " << node->x << '\n';
			left = node;
			left->is_black = false; // new item is always red
			if(!is_black/* red */ && parent)
				return parent->fixup_uncle(left, parent->right == this/* then it is the same side as uncle */, parent->right == this?parent->left:parent->right);
			return NULL;
		}
		if(node->x == x) {
			if(equals)
				return equals->insert(node, NULL);
			equals = node;
			equals->is_black = is_black;
			return NULL;
		}
		if(right) {
			RBNode*nparent = right->insert(node, this);
			if(nparent != NULL) {
				if((nparent->right == right) || (nparent->left == right)) {
					right = nparent;
					return NULL;
				}
				if((nparent->right == left) || (nparent->left == left)) {
					left = nparent;
					return NULL;
				}
				return nparent;
			}
			return NULL;
		}
		//cout << "inserting right " << node->x << '\n';
		right = node;
		right->is_black = false; // new item is always red
		if(!is_black && parent)
			return parent->fixup_uncle(right, parent->left == this, parent->right == this?parent->left:parent->right);
		return NULL;
	}

	RBNode*search(K given) {
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
	// TODO remove node

	void dump() { // prints tree in preorder
		cout << '(' << x << ' ';
		if(left)
			left->dump();
		if(right)
			right->dump();
		cout << ')';
	}

	~RBNode() {
		if(equals) delete equals;
		if(left) delete left;
		if(right) delete right;
	}

	void in_order(int (*cb)(K x)) { // traverses tree in in-order
		if(left)
			left->in_order(cb);
		cb(x);
		if(right)
			right->in_order(cb);
	}
};

template <typename K>
static int in_order_dump_cb(K x) {
	cout << x << ',';
	return 0;
}

static int read_input_and_build_tree_and_search(const int n, const int x) {
	RBNode<int>*root = NULL;
	int i = n;
	while(i--) {
		int r = 0;
		cin >> r;
		RBNode<int>*node = new RBNode<int>(r);
		if(!root)
			root = node;
		else {
			RBNode<int>*new_root = root->insert(node, NULL);
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

