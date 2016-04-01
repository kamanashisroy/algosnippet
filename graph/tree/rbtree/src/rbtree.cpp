
#include <string.h>
#include <queue>
#include <iostream>
#include <cstdio>

using namespace std;

template <typename K>
struct RBNode {
	K x;
	bool is_black;
	RBNode*right;
	RBNode*left;
	RBNode*equals;

	RBNode(K given) : x(given),is_black(true),right(NULL),left(NULL),equals(NULL) { }

	int fixup_uncle(RBNode*added, bool is_same_side_as_uncle, RBNode*uncle) {
		if(uncle && !uncle->is_black) { // if parent and uncle is red
			// wikipedia case 3
			// color flip
			is_black = false;
			right->is_black = true;
			left->is_black = true;
			added->is_black = false;
		} else if(uncle && uncle->is_black) { // uncle is black
			// wikipedia case 4
			if(is_same_side_as_uncle) {
				// needs rotation
				if(uncle == left) {
					added->right = right;
					right = added;
					added->right->left = NULL;
				} else {
					added->left = left;
					left = added;
					added->left->right = NULL;
				}
			}
		}
		return 0;
	}

	RBNode*insert(RBNode*node, RBNode*parent) {
		if(node->x < x) {
			if(left) {
				left->insert(node, this);
				// fix red red violation
				if(is_black && !left->is_black && left->left && !left->left->is_black) {
					// time to rotate
					if(parent) {
						if(parent->right == this)
							parent->right = left;
						else
							parent->left = left;
					}
					left->right = this;
					is_black = true;
					left = NULL;
					if(!parent)
						return left;
				}
				return NULL;
			}
			//cout << "inserting left " << node->x << '\n';
			left = node;
			left->is_black = false; // new item is always red
			if(!is_black && parent)parent->fixup_uncle(left, parent->right == this, parent->right == this?parent->left:parent->right);
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
			right->insert(node, this);
			// fix red red violation
			if(is_black && !right->is_black && right->right && !right->right->is_black) {
				// time to rotate
				if(parent) {
					if(parent->right == this)
						parent->right = right;
					else
						parent->left = right;
				}
				right->left = this;
				is_black = true;
				right = NULL;
				if(!parent)
					return right;
			}
			return NULL;
		}
		//cout << "inserting right " << node->x << '\n';
		right = node;
		right->is_black = false; // new item is always red
		if(!is_black && parent)parent->fixup_uncle(right, parent->left == this, parent->right == this?parent->left:parent->right);
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

