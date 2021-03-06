
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

	void in_order(int (*cb)(K x)) { // traverses tree in in-order
		if(left)
			left->in_order(cb);
		cb(x);
		if(right)
			right->in_order(cb);
	}

	void serialize(ostream&strm) {
		strm << x << '(';
		if(left)
			left->serialize(strm);
		strm << ',';
		if(right)
			right->serialize(strm);
		strm << ')';
	}

	void deserialize(istream&strm) {
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

	bool is_equal(TNode*other) {
		if(x != other->x)
			return false;
		if(other->left != left && ((other->left == NULL) || (left == NULL))) {
			return false;
		}
		if(left != NULL && !left->is_equal(other->left))
			return false;

		if(other->right != right && ((other->right == NULL) || (right == NULL))) {
			return false;
		}
		if(right != NULL && !right->is_equal(other->right)) {
			return false;
		}
		return true;
	}

	bool contains_subtree(TNode*other) {
		return is_equal(other) || (left != NULL && left->contains_subtree(other)) || (right != NULL && right->contains_subtree(other));
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

static int read_tree_and_check_substring() {

	// read first
	TNode<int>*first = new TNode<int>(0);
	first->deserialize(cin);
	first->in_order(in_order_dump_cb);
	cout << '\n';

	// read second
	TNode<int>*second = new TNode<int>(0);
	second->deserialize(cin);
	second->in_order(in_order_dump_cb);
	cout << '\n';

	stringstream firststrm;
	stringstream secondstrm;
	// convert to string
	first->serialize(firststrm);
	second->serialize(secondstrm);

	// find if secondstrm is substring of firststrm
	if(firststrm.str().find(secondstrm.str()) != std::string::npos) {
		cout << "string way:second is subtree of first\n";
	} else {
		cout << "string way:second is NOT subtree of first\n";
	}

	if(first->contains_subtree(second)) {
		cout << "second is subtree of first\n";
	} else {
		cout << "second is NOT subtree of first\n";
	}

	if(first)
		delete first;
	if(second)
		delete second;
	return 0;
}

int main(int argc, char*argv[]) {
	read_tree_and_check_substring();
	return 0;
}

