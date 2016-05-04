#include "bst.h"
#include "bst.cpp"
#include "bst_insert.cpp"
#include "bst_serializer.cpp"
#include "bst_search.cpp"
#include "bst_find.cpp"
#include "bst_traversal.cpp"

template <typename K>
static int in_order_dump_cb(K x) {
	cout << x << ',';
	return 0;
}

static int read_input_and_build_tree_and_search(const int n, const int x) {
	btnode<int>*root = NULL;
	int i = n;
	while(i--) {
		int r = 0;
		cin >> r;
		btnode<int>*node = new btnode<int>(r);
		if(!root)
			root = node;
		else
			root->insert(node);
	}
	root->in_order(in_order_dump_cb);
	cout << endl;
	root->in_order_recursive(in_order_dump_cb);
	cout << endl;
	stringstream strm;
	root->serialize(strm);
	cout << strm.str() << endl;
	cout << "Minimum value is " << root->find_minimum()->x << ", maximum is " << root->find_maximum()->x << endl;
	cout << "Finding " << x << endl;
	btnode<int>*result = NULL;
	if((result = root->search(x)) != NULL) {
		cout << "found " << x << endl;
	} else {
		cout << "not found " << x << endl;
	}
	result = NULL;
	if((result = root->search_iterative(x)) != NULL) {
		cout << "found iteratively " << x << endl;
		btnode<int>*sucr = result->find_successor();
		cout << "Successor of " << x << " is " << (sucr?sucr->x:-1) << endl;
		btnode<int>*pred = result->find_predecessor();
		cout << "Predecessor of " << x << " is " << (pred?pred->x:-1) << endl;
	} else {
		cout << "not found " << x << endl;
	}
	result = NULL;
	if(root)
		delete root;
	root = new btnode<int>(0);
	root->deserialize(strm);
	root->in_order(in_order_dump_cb);
	cout << endl;
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

