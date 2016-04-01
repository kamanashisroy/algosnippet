
#include <string.h>
#include <queue>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <assert.h>

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

	void in_order(int (*cb)(K x)) { // prints tree in preorder
		if(left)
			left->in_order(cb);
		cb(x);
		if(right)
			right->in_order(cb);
	}

	void serialize(stringstream&strm) {
		strm << x << '(';
		if(left)
			left->serialize(strm);
		strm << ',';
		if(right)
			right->serialize(strm);
		strm << ')';
	}

	void deserialize(stringstream&strm) {
		char ch;
		strm  >> x >> ch;
		assert(ch == '(');
		if(strm.peek() != ',') {
			left = new TNode<int>(0);
			left->deserialize(strm);
		}
		strm >> ch;
		assert(ch == ',');
		if(strm.peek() != ')') {
			right = new TNode<int>(0);
			right->deserialize(strm);
		}
		strm >> ch;
		assert(ch == ')');
	}

	~TNode() {
		if(equals) delete equals;
		if(left) delete left;
		if(right) delete right;
	}

};

template <typename K>
static int in_order_dump_cb(K x) {
	cout << x << ',';
	return 0;
}

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
	root->in_order(in_order_dump_cb);
	cout << '\n';
	stringstream strm;
	root->serialize(strm);
	cout << strm.str() << '\n';
	if(root->search(x) != NULL) {
		cout << "found " << x << '\n';
	} else {
		cout << "not found " << x << '\n';
	}
	if(root)
		delete root;
	root = new TNode<int>(0);
	root->deserialize(strm);
	root->in_order(in_order_dump_cb);
	cout << '\n';
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

