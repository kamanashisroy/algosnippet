
#include <string.h>
#include <queue>
#include <iostream>
#include <cstdio>

using namespace std;

template <typename K>
struct TNode {
	K x;
	TNode*right;
	TNode*left;
	TNode*equals;

	TNode(K given) : x(given),right(NULL),left(NULL),equals(NULL) { }

	int insert(TNode*node) {
		if(node->x < x) {
			if(left)
				return left->insert(node);
			//cout << "inserting left " << node->x << '\n';
			left = node;
			return 0;
		}
		if(node->x == x) {
			if(equals)
				return equals->insert(node);
			equals = node;
			return 0;
		}
		if(right)
			return right->insert(node);
		//cout << "inserting right " << node->x << '\n';
		right = node;
		return 0;
	}

	TNode*search(K given) {
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

	~TNode() {
		if(equals) delete equals;
		if(left) delete left;
		if(right) delete right;
	}

};

static int read_input_and_build_tree_and_search(const int n, const int x) {
	TNode<int>*root = NULL;
	int i = n;
	while(i--) {
		int r = 0;
		cin >> r;
		TNode<int>*node = new TNode<int>(r);
		if(!root)
			root = node;
		else
			root->insert(node);
	}
	root->dump();
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

